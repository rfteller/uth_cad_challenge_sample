////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Sample codes for UTH CAD Challenge
//
//	      check_answer_for_lung_nodule.cpp : Judge lesion candidates as true positives or not
//                                            (same criterion as ANODE'09 study) 
//
//    [CAUTION] The sample codes are permitted to use only for research purposes.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_DEPRECATE

#include "check_answer_for_lung_nodule.h"
#include "..\MachineLearning\example_set.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

int check_answer_for_lung_nodule(
	const char* in_path,
	CircusCS_BASICDCMTAGVALUES* basic_tag_values,
	vector<vector<float>>& cand_properties,
	EXAMPLESET* dataset,
	char* log_file_name)
{
	char  answer_file_name[1024];
	char  lesion_info_file_name[1024];
	char  buffer[1024];
	char* tp;

	sprintf(answer_file_name,  "%s\\0_ans.raw", in_path);
	sprintf(lesion_info_file_name,  "%s\\0_lesion_info.txt", in_path);

	//----------------------------------------------------------------------------------------------
	// Load answer volume data
	//----------------------------------------------------------------------------------------------
	CircusCS_AppendLogFile(log_file_name, ">> Load answer volume data");

	VOL_RAWVOLUMEDATA* answer_volume = VOL_NewSingleChannelRawVolumeDataFromFile(
		answer_file_name,
		(VOL_INTSIZE3D*)basic_tag_values->matrixSize,
		VOL_VALUEUNIT_UINT8,
		VOL_VALUETYPE_SINGLE,
		0);
	
	if(answer_volume == NULL)
	{
		CircusCS_AppendLogFile(log_file_name, "Failed to load answer volume data: 0_ans.raw");
		return 0;
	}
	//----------------------------------------------------------------------------------------------

	//----------------------------------------------------------------------------------------------
	// Labeling
	//----------------------------------------------------------------------------------------------
	unsigned int answer_num = VOL_ConnectedComponentAnalysis(
								answer_volume,
								0,
								VOL_NEIGHBOURTYPE_26);
	
	VOL_COMPONENTDATA *answer_cc = VOL_NewComponentData(
									answer_volume,
									0,
									answer_num);
	//----------------------------------------------------------------------------------------------

	//----------------------------------------------------------------------------------------------
	// Load lesion info
	//----------------------------------------------------------------------------------------------
	vector<int> lesion_size(1);

	FILE* fp = fopen(lesion_info_file_name, "r");

	if(fp == NULL)
	{
		fprintf(stderr, "Failed to lesion information file (0_lesion_info.txt)\n");
		return -1;
	}

	// third line or later: folder for input case
	while(fgets(buffer, sizeof(buffer), fp) != NULL)
	{
		tp = strtok(buffer, ",");
		tp = strtok(NULL,   ",");

		lesion_size.push_back(atoi(tp));
	}
	
	fclose(fp);
	//----------------------------------------------------------------------------------------------

	//----------------------------------------------------------------------------------------------
	// Check answer
	//----------------------------------------------------------------------------------------------
	for(unsigned int n = 1; n <= answer_num; n++)
	{
		VOL_VECTOR3D	gravity;

		VOL_GetCenterOfGravityOfComponent(answer_cc, (unsigned long)n, &gravity);

		float distance_min     = 10000.0;
		int   distance_min_idx = 0;

		for(int i = 0; i < (int)dataset->examples.size(); i++)
		{
			float dx = (cand_properties[i][1]-gravity.x) * basic_tag_values->voxelSize_mm->width;
			float dy = (cand_properties[i][2]-gravity.y) * basic_tag_values->voxelSize_mm->height;
			float dz = (cand_properties[i][3]-gravity.z) * basic_tag_values->voxelSize_mm->depth;

			float distance = sqrt(dx * dx + dy * dy + dz * dz);

			if(distance < distance_min)
			{
				distance_min = distance;
				distance_min_idx = i;
			}
		}

		fprintf(stderr, "%d (%d mm) -> %d (%.2f mm)",
			n,
			lesion_size[n],
			distance_min_idx+1,
			distance_min);

		if(distance_min <= (float)lesion_size[n] * 0.75f)
		{
			dataset->examples[distance_min_idx]->label = 1;
			fprintf(stderr, " detected");
		}
		fprintf(stderr, "\n");
		
	}
	//----------------------------------------------------------------------------------------------

	VOL_DeleteRawVolumeData(answer_volume);

	return 1;
}


