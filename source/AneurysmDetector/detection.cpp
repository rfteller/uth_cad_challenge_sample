#define _CRT_SECURE_NO_DEPRECATE
#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>
#include <vector>
#include <string>
#include <map>

#include "VOL.h"
#include "VOLbinary.h"
#include "VOLfile.h"
#include "VOLfilter.h"
#include "LibCircusCS.h"

#include "common.h"
#include "detection.h"
#include "check_answer.h"
#include "vessel_segmentation.h"
#include "..\MachineLearning\example_set.h"
#include "..\MachineLearning\mahalanobis_distance.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////

VOL_INTBOX3D* brain_box  = NULL;
VOL_INTBOX3D* vessel_box = NULL;

////////////////////////////////////////////////////////////////////////////////////////////////

VOL_RAWVOLUMEDATA* vesselSegmentation(VOL_RAWVOLUMEDATA* volume, char* log_file_name)
{
	char buffer[1024];
	float brain_mean, brain_sigma;

	CircusCS_AppendLogFile(log_file_name, ">> get statictics of brain level");
	getStaticticsOfBrainLevel(volume, &brain_mean, &brain_sigma);
	sprintf(buffer, "Brain level: mean: %3.1f (stddev: %3.1f)", brain_mean, brain_sigma);
	CircusCS_AppendLogFile(log_file_name, buffer);

	CircusCS_AppendLogFile(log_file_name, ">> get brain box");
	brain_box = getBrainBox(volume, brain_mean, brain_sigma, log_file_name);

	CircusCS_AppendLogFile(log_file_name, ">> get vessel mask");
	
	VOL_RAWVOLUMEDATA* ret = getVesselMask(
		volume,
		brain_box,
		brain_mean,
		brain_sigma,
		log_file_name);

	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////

int aneurysm_detection_in_mra(const char* in_path, const char* out_path, int core_num, int mode)	
{
	char in_volume_file_name[1024];
	char in_dump_file_name[1024];
	char log_file_name[1024];
	char out_file_name[1024];
	char buffer[1024];

	sprintf(in_volume_file_name, "%s\\0.raw", in_path);
	sprintf(in_dump_file_name,   "%s\\0.txt", in_path);
	sprintf(log_file_name,       "%s\\%s",    out_path, LOG_FILE_NAME);

	//------------------------------------------------------------------------------------------
	// Get basic DICOM tag value
	//------------------------------------------------------------------------------------------
	CircusCS_AppendLogFile(log_file_name, "Load DICOM dump data");

	CircusCS_BASICDCMTAGVALUES* basic_tag_values = NULL;
	
	basic_tag_values = CircusCS_NewBasicDcmTagValues(in_dump_file_name);
	
	if(basic_tag_values == NULL)
	{
		sprintf(buffer, "Failed to load DICOM dump data: %s", in_dump_file_name);
		CircusCS_AppendLogFile(log_file_name, buffer);
		return -1;
	}
	//------------------------------------------------------------------------------------------

	//------------------------------------------------------------------------------------------
	// Load volume data
	//------------------------------------------------------------------------------------------
	CircusCS_AppendLogFile(log_file_name, "Load volume data");

	VOL_RAWVOLUMEDATA* volume = VOL_NewSingleChannelRawVolumeDataFromFile(
		in_volume_file_name,
		(VOL_INTSIZE3D*)basic_tag_values->matrixSize,
		VOL_VALUEUNIT_SINT16,
		VOL_VALUETYPE_SINGLE,
		0);
	
	if(volume == NULL)
	{
		CircusCS_AppendLogFile(log_file_name, "Failed to load volume data: 0.raw");
		return -1;
	}
	//------------------------------------------------------------------------------------------

	//------------------------------------------------------------------------------------------
	// Isotropic resampling
	//------------------------------------------------------------------------------------------
	CircusCS_AppendLogFile(log_file_name, "Isotropic resampling");
	
	float interpolation_ratio = basic_tag_values->voxelSize_mm->depth 
							  / basic_tag_values->voxelSize_mm->width;

	VOL_INTSIZE3D  iso_matrix_size;

	iso_matrix_size.width  = (int)((float)volume->matrixSize->width);
	iso_matrix_size.height = (int)((float)volume->matrixSize->height);
	iso_matrix_size.depth  = (int)((float)volume->matrixSize->depth * interpolation_ratio);

	VOL_ScaleRawVolumeData(volume, &iso_matrix_size, VOL_SCALING_METHOD_LINEAR);

	sprintf(buffer, "New size: %dx%dx%d",
		iso_matrix_size.width,
		iso_matrix_size.height,
		iso_matrix_size.depth);
	
	CircusCS_AppendLogFile(log_file_name, buffer);
	//------------------------------------------------------------------------------------------

	//------------------------------------------------------------------------------------------
	// Vessel segmentation and cropping
	//------------------------------------------------------------------------------------------
	CircusCS_AppendLogFile(log_file_name, "Vessel segmentation");

	VOL_RAWVOLUMEDATA* vessel_mask = vesselSegmentation(volume, log_file_name);

	if( vessel_mask == NULL )
	{
		CircusCS_AppendLogFile(log_file_name, "Failed to extract vessel region");
		CircusCS_DeleteBasicDcmTagValues(basic_tag_values);
		VOL_DeleteRawVolumeData(volume);
		return -1;
	}
	else  // Cropping
	{
		vessel_box = VOL_GetBoundingBoxOfBinaryVolume(vessel_mask, 0);
		
		VOL_ResizeRawVolumeData(volume,      vessel_box, VOL_RESIZE_BACKGROUNDTYPE_ZERO);
		VOL_ResizeRawVolumeData(vessel_mask, vessel_box, VOL_RESIZE_BACKGROUNDTYPE_ZERO);
	}
	//------------------------------------------------------------------------------------------

	//------------------------------------------------------------------------------------------
	//  Lesion candidate extraction based on principal curvature
	//------------------------------------------------------------------------------------------
	CircusCS_AppendLogFile(log_file_name, "Lesion candidate extraction");

	// Calculate principal curvature (k1, k2)
	VOL_RAWVOLUMEDATA* cv_volume =VOL_DuplicateRawVolumeData(volume);
	VOL_CurvatureFilter(cv_volume, 3.0f, VOL_CURVATURE_TYPE_TWO_PRINCIPALS);

	VOL_RAWVOLUMEDATA* cand_volume = VOL_NewSingleChannelRawVolumeData(
		vessel_box->size,
		VOL_VALUEUNIT_UINT8,
		VOL_VALUETYPE_SINGLE);

	{
		int            length     = VOL_GetNumberOfVoxels(volume);
		int			   offset     = volume->matrixSize->width * volume->matrixSize->height * 2;
		float*         k1_ptr     = (float*)cv_volume->data[0] + offset;
		float*         k2_ptr     = (float*)cv_volume->data[1] + offset;
		unsigned char* vessel_ptr = (unsigned char*)vessel_mask->data[0] + offset;
		unsigned char* cand_ptr   = (unsigned char*)cand_volume->data[0] + offset;

		// thresholding by principal curvature and vessel mask
		for(int i = offset; i < length - offset; i++)
		{
			*cand_ptr = (*vessel_ptr == 1 && *k1_ptr < 0.0f && *k1_ptr / *k2_ptr > 0.7f) ? 1 : 0;

			k1_ptr++;
			k2_ptr++;
			vessel_ptr++;
			cand_ptr++;
		}
	}
	//------------------------------------------------------------------------------------------

	//------------------------------------------------------------------------------------------
	// Labeling
	//------------------------------------------------------------------------------------------
	unsigned int num_candidates = VOL_ConnectedComponentAnalysis(cand_volume, 0, VOL_NEIGHBOURTYPE_26);
	
	VOL_COMPONENTDATA *aneurysm_cc = VOL_NewComponentData( cand_volume, 0, num_candidates );
	
	// Sort by voxel counts (DESC)
	VOL_SortComponentsByProperty( aneurysm_cc, VOL_CC_PROPERTY_ID_VOXELCOUNT );

	num_candidates = min(num_candidates, MAX_CANDIDATES);
	//------------------------------------------------------------------------------------------

	//------------------------------------------------------------------------------------------
	// Feature extraction (save temporary file)
	//------------------------------------------------------------------------------------------
	sprintf(buffer, "Feature extraction");
	CircusCS_AppendLogFile(log_file_name, buffer);
	
	vector<vector<float>> cand_properties(num_candidates, vector<float>(12));
	EXAMPLESET* dataset = new_example_set(num_candidates, NUM_FEATURES);

	for(unsigned int i=0; i<num_candidates; i++)
	{
		float           sliceLocation = 0.0f;
		VOL_VECTOR3D	gravity;

		VOL_GetCenterOfGravityOfComponent(aneurysm_cc, (unsigned long)i+1, &gravity);

		cand_properties[i][0]  = 1;										  // label
		cand_properties[i][1]  = gravity.x + (float)vessel_box->origin->x; // x-gravity
		cand_properties[i][2]  = gravity.y + (float)vessel_box->origin->y; // y-gravity
		cand_properties[i][3]  = gravity.z + (float)vessel_box->origin->z; // z-gravity
		cand_properties[i][3] /= interpolation_ratio;

		// Volume [mm3]
		cand_properties[i][4] = (float)aneurysm_cc->nVoxelsOfComponents[i+1]
			* basic_tag_values->voxelSize_mm->width
			* basic_tag_values->voxelSize_mm->width
			* basic_tag_values->voxelSize_mm->width;
	
		// initialize feature values (min / max / mean of k1, k1/k2)
		cand_properties[i][5] = cand_properties[i][8]  =  10000.0f;
		cand_properties[i][6] = cand_properties[i][9]  = -10000.0f;
		cand_properties[i][7] = cand_properties[i][10] =      0.0f;
	}
		
	// Calculate feature values
	{
		int            length   = VOL_GetNumberOfVoxels(volume);
		int			   offset   = volume->matrixSize->width * volume->matrixSize->height * 2;
		short*         src_ptr  = (short*)volume->data[0] + offset;
		float*         k1_ptr   = (float*)cv_volume->data[0] + offset;
		float*         k2_ptr   = (float*)cv_volume->data[1] + offset;
		unsigned int*  cand_ptr = (unsigned int*)cand_volume->data[0] + offset;

		// thresholding by principal curvature and vessel mask
		for(int i = offset; i < length - offset; i++)
		{
			unsigned int cand_val = *cand_ptr;

			if(0 < cand_val && cand_val <= num_candidates)
			{
				if(*src_ptr < cand_properties[cand_val-1][5]) cand_properties[cand_val-1][5] = *src_ptr;
				if(*src_ptr > cand_properties[cand_val-1][6]) cand_properties[cand_val-1][6] = *src_ptr;
				cand_properties[cand_val-1][7]  += *src_ptr;

				float k_ratio = *k1_ptr / *k2_ptr;

				if(k_ratio < cand_properties[cand_val-1][8]) cand_properties[cand_val-1][8] = k_ratio;
				if(k_ratio > cand_properties[cand_val-1][9]) cand_properties[cand_val-1][9] = k_ratio;
				cand_properties[cand_val-1][10] += k_ratio;
			}

			src_ptr++;
			k1_ptr++;
			k2_ptr++;
			cand_ptr++;
		}
	}

	for(unsigned int i=0; i<num_candidates; i++)
	{
		cand_properties[i][7]  /= (float)aneurysm_cc->nVoxelsOfComponents[i+1];
		cand_properties[i][10] /= (float)aneurysm_cc->nVoxelsOfComponents[i+1];

		for(int j=0; j<NUM_FEATURES; j++)
		{
			dataset->examples[i]->descriptor[j] = cand_properties[i][4+j];
		}
	}

	VOL_DeleteRawVolumeData(cv_volume);
	VOL_DeleteRawVolumeData(volume);
	VOL_DeleteRawVolumeData(cand_volume);
	VOL_DeleteRawVolumeData(vessel_mask);
	VOL_DeleteComponentData(aneurysm_cc);
	//------------------------------------------------------------------------------------------

	//------------------------------------------------------------------------------------------
	// FP reduction and save results
	//------------------------------------------------------------------------------------------
	if(mode == 2)
	{
		check_answer(in_path, basic_tag_values, cand_properties, dataset, log_file_name);
		
		sprintf(out_file_name, "%s\\%s", out_path, TMP_EXAMPLE_FILE_NAME);
		write_example_set(out_file_name, dataset);
	}	
	else
	{
		//--------------------------------------------------------------------------------------
		// Classification 
		//--------------------------------------------------------------------------------------
		sprintf(buffer, "Classification");
		CircusCS_AppendLogFile(log_file_name, buffer);

		MAHALANOBISDISTANCERATIOCLASSIFIER* mdr_classifier;
		mdr_classifier = read_mahalanobis_distance_ratio_classifier(CLASSIFIER_FILE_NAME);

		float* distance_ratio = mahalanobis_distance_ratio_array(dataset, mdr_classifier);

		// Sort by Mahalanobis distance (DESC)
		multimap<float, int, greater<float>> dist_map;

		for(unsigned int i=0; i<num_candidates; i++)
		{
			// Normalization [0.0, 1.0]
			distance_ratio[i] = (float)(atan(distance_ratio[i])/M_PI_2);

			dist_map.insert(pair<float, int>( distance_ratio[i] , i));
		}
		//--------------------------------------------------------------------------------------

		//--------------------------------------------------------------------------------------
		// Save detection results (File name is defined in RESULTS_FileName)
		//--------------------------------------------------------------------------------------
		sprintf(buffer, "Save detection results (%s)", RESULTS_FILE_NAME);
		CircusCS_AppendLogFile(log_file_name, buffer);
		{
			sprintf(out_file_name, "%s\\%s", out_path, RESULTS_FILE_NAME);
			FILE* fp = fopen(out_file_name, "w");

			int cnt = 1;

			for(multimap<float, int, greater<float>>::iterator itr = dist_map.begin();
				itr != dist_map.end(); ++itr)
			{
				unsigned int idx = (*itr).second;

				fprintf(fp, "%d,%d,%d,%d,%f,%f\n", 
					cnt++,
					(int)(cand_properties[idx][1] + 0.5f),
					(int)(cand_properties[idx][2] + 0.5f),
					(int)(cand_properties[idx][3] + 0.5f),
					cand_properties[idx][4],
					(*itr).first);
			}
			fclose(fp);

			sprintf(buffer, "Final candidates of aneurysm: %d", num_candidates);
			CircusCS_AppendLogFile(log_file_name, buffer);
		}
		//--------------------------------------------------------------------------------------
	}

	CircusCS_DeleteBasicDcmTagValues(basic_tag_values);
	delete_example_set(dataset);
	//------------------------------------------------------------------------------------------

	CircusCS_AppendLogFile(log_file_name, "Finished");

	return num_candidates;
}