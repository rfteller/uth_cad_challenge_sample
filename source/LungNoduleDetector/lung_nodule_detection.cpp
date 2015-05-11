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

#include "lung_nodule_common.h"
#include "lung_nodule_detection.h"
#include "lung_segmentation.h"
#include "check_answer_for_lung_nodule.h"
#include "..\MachineLearning\example_set.h"
#include "..\MachineLearning\mahalanobis_distance.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////

int lung_nodule_detection(const char* in_path, const char* out_path, int core_num, int mode)	
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
	// Lung segmentation
	//------------------------------------------------------------------------------------------
	CircusCS_AppendLogFile(log_file_name, "Lung segmentation");

	VOL_RAWVOLUMEDATA* lung_shape = VOL_DuplicateRawVolumeData(volume);
	lung_segmentation(lung_shape);
	//------------------------------------------------------------------------------------------

	//------------------------------------------------------------------------------------------
	// Isotropic resampling
	//------------------------------------------------------------------------------------------
	CircusCS_AppendLogFile(log_file_name, "Isotropic resampling");
	
	float interpolation_ratio = basic_tag_values->voxelSize_mm->depth 
							  / basic_tag_values->voxelSize_mm->width;

	VOL_INTSIZE3D  iso_matrix_size;
	VOL_SIZE3D     iso_voxel_size;

	iso_matrix_size.width  = (int)((float)volume->matrixSize->width);
	iso_matrix_size.height = (int)((float)volume->matrixSize->height);
	iso_matrix_size.depth  = (int)((float)volume->matrixSize->depth * interpolation_ratio);

	iso_voxel_size.width  = basic_tag_values->voxelSize_mm->depth;
	iso_voxel_size.height = iso_voxel_size.width;
	iso_voxel_size.depth  = iso_voxel_size.width;

	VOL_ScaleRawVolumeData(volume,     &iso_matrix_size, VOL_SCALING_METHOD_LINEAR);
	VOL_ScaleRawVolumeData(lung_shape, &iso_matrix_size, VOL_SCALING_METHOD_LINEAR);

	sprintf(buffer, "New size: %dx%dx%d",
		iso_matrix_size.width,
		iso_matrix_size.height,
		iso_matrix_size.depth);
	
	CircusCS_AppendLogFile(log_file_name, buffer);
	//------------------------------------------------------------------------------------------

	//------------------------------------------------------------------------------------------
	// Cropping
	//------------------------------------------------------------------------------------------
	VOL_INTBOX3D* lung_box = VOL_GetBoundingBoxOfBinaryVolume(lung_shape, 0);
		
	VOL_ResizeRawVolumeData(volume,     lung_box, VOL_RESIZE_BACKGROUNDTYPE_ZERO);
	VOL_ResizeRawVolumeData(lung_shape, lung_box, VOL_RESIZE_BACKGROUNDTYPE_ZERO);
	//------------------------------------------------------------------------------------------

	//------------------------------------------------------------------------------------------
	//  Lesion candidate extraction based on shape index
	//------------------------------------------------------------------------------------------
	CircusCS_AppendLogFile(log_file_name, "Lesion candidate extraction");

	// Calculate shape index
	VOL_RAWVOLUMEDATA* cv_volume =VOL_DuplicateRawVolumeData(volume);
	VOL_CurvatureFilter(cv_volume, 2.0f, VOL_CURVATURE_TYPE_SHAPE_INDEX_AND_CURVEDNESS);

	VOL_RAWVOLUMEDATA* cand_volume = VOL_NewSingleChannelRawVolumeData(
		lung_box->size,
		VOL_VALUEUNIT_UINT8,
		VOL_VALUETYPE_SINGLE);

	{
		int            length   = VOL_GetNumberOfVoxels(volume);
		int			   offset   = volume->matrixSize->width * volume->matrixSize->height * 2;
		short*         src_ptr  = (short*)volume->data[0] + offset;
		float*         si_ptr   = (float*)cv_volume->data[0] + offset;  // shape index
		unsigned char* lung_ptr = (unsigned char*)lung_shape->data[0] + offset;
		unsigned char* cand_ptr = (unsigned char*)cand_volume->data[0] + offset;

		// thresholding by principal curvature and vessel mask
		for(int i = offset; i < length - offset; i++)
		{
			*cand_ptr = (*lung_ptr == 1 && *src_ptr >= -700 && *si_ptr >= 0.9f) ? 1 : 0;

			src_ptr++;
			si_ptr++;
			lung_ptr++;
			cand_ptr++;
		}
	}
	//------------------------------------------------------------------------------------------

	//------------------------------------------------------------------------------------------
	// Labeling
	//------------------------------------------------------------------------------------------
	unsigned int num_candidates = VOL_ConnectedComponentAnalysis(
										cand_volume,
										0,
										VOL_NEIGHBOURTYPE_26);
	
	VOL_COMPONENTDATA *aneurysm_cc = VOL_NewComponentData(cand_volume, 0, num_candidates );
	
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

		cand_properties[i][0]  = 1;										 // label
		cand_properties[i][1]  = gravity.x + (float)lung_box->origin->x; // x-gravity
		cand_properties[i][2]  = gravity.y + (float)lung_box->origin->y; // y-gravity
		cand_properties[i][3]  = gravity.z + (float)lung_box->origin->z; // z-gravity
		cand_properties[i][3] /= interpolation_ratio;

		// Volume [mm3]
		cand_properties[i][4] = (float)aneurysm_cc->nVoxelsOfComponents[i+1]
			* basic_tag_values->voxelSize_mm->width
			* basic_tag_values->voxelSize_mm->width
			* basic_tag_values->voxelSize_mm->width;
	
		// initialize feature values (min / max / mean of voxel value and curvedness)
		cand_properties[i][5] = cand_properties[i][8]  =  10000.0f;
		cand_properties[i][6] = cand_properties[i][9]  = -10000.0f;
		cand_properties[i][7] = cand_properties[i][10] =      0.0f;
	}
		
	// Calculate feature values
	{
		int            length   = VOL_GetNumberOfVoxels(volume);
		int			   offset   = volume->matrixSize->width * volume->matrixSize->height * 2;
		short*         src_ptr  = (short*)volume->data[0] + offset;
		float*         cv_ptr   = (float*)cv_volume->data[1] + offset;
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

				if(*cv_ptr < cand_properties[cand_val-1][8]) cand_properties[cand_val-1][8] = *cv_ptr;
				if(*cv_ptr > cand_properties[cand_val-1][9]) cand_properties[cand_val-1][9] = *cv_ptr;
				cand_properties[cand_val-1][10] += *cv_ptr;
			}

			src_ptr++;
			cv_ptr++;
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
	VOL_DeleteRawVolumeData(lung_shape);
	VOL_DeleteComponentData(aneurysm_cc);
	//------------------------------------------------------------------------------------------

	//------------------------------------------------------------------------------------------
	// FP reduction and save results
	//------------------------------------------------------------------------------------------
	if(mode == 2)
	{
		check_answer_for_lung_nodule(
			in_path,
			basic_tag_values,
			cand_properties,
			dataset,
			log_file_name);
		
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