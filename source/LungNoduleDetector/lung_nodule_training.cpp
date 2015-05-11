#pragma warning(disable:4996)

#include <stdio.h>
#include <vector>
#include <string>
#include <direct.h>
#include <windows.h>
#include <shlwapi.h>

#include "lung_nodule_common.h"
#include "lung_nodule_training.h"

#include "..\MachineLearning\example_set.h"
#include "..\MachineLearning\mahalanobis_distance.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////

int lung_nodule_detector_training(char* configuration_file_name, int core_num)
{
	char tmp_path[1024], out_path[1024], in_path[1024];
	vector<string> in_path_list;
	vector<string> feature_data_file_list;

	//------------------------------------------------------------------------------------------
	// Load configuration file
	//------------------------------------------------------------------------------------------
	FILE* fp = fopen(configuration_file_name, "r");

	if(fp == NULL)
	{
		fprintf(stderr, "Failed to load configuration file (%s)\n", configuration_file_name);
		return -1;
	}

	// first line: temporary folder
	fgets(tmp_path, sizeof(tmp_path), fp);
	tmp_path[strlen(tmp_path)-1] = '\0';
	fprintf(stderr, "Temporary folder: %s\n", tmp_path);

	// second line: output folder
	fgets(out_path, sizeof(out_path), fp);
	out_path[strlen(out_path)-1] = '\0';
	fprintf(stderr, "Output folder: %s\n", out_path);

	// third line or later: folder for input case
	while(fgets(in_path, sizeof(in_path), fp) != NULL)
	{
		in_path[strlen(in_path)-1] = '\0';
		in_path_list.push_back(in_path);
	}
	
	fclose(fp);
	//------------------------------------------------------------------------------------------

	//------------------------------------------------------------------------------------------
	// Create feature data
	//------------------------------------------------------------------------------------------
	char src_data_file_name[1024];
	char dst_data_file_name[1024];
	char command_str[1024];
	
	sprintf(src_data_file_name, "%s\\%s", tmp_path, TMP_EXAMPLE_FILE_NAME);

	for(int n = 0; n < (int)in_path_list.size(); n++)
	{
		fprintf(stderr, "Case %d: %s\n", n+1, in_path_list[n].c_str());
		
		sprintf(command_str, "%s \"%s\" \"%s\" %d 2",
			DETECTOR_FILE_NAME,
			in_path_list[n].c_str(),
			tmp_path,
			core_num);

		// Execute detector (as feature extraction mode)
		PROCESS_INFORMATION pInfo;
		STARTUPINFO sInfo;

		ZeroMemory(&sInfo, sizeof(sInfo));

		if (!CreateProcess((LPTSTR)DETECTOR_FILE_NAME, (LPTSTR)command_str, NULL, NULL,
				FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &sInfo, &pInfo))
		{
			fprintf(stderr, "%04d\n", GetLastError());
		}

		CloseHandle(pInfo.hThread);
		WaitForSingleObject(pInfo.hProcess, INFINITE);
		CloseHandle(pInfo.hProcess);

		// move feature extration file
		if(PathFileExists(src_data_file_name) && !PathIsDirectory(src_data_file_name))
		{
			sprintf(dst_data_file_name, "%s\\featData_%05d.csv", tmp_path, n);
			rename(src_data_file_name, dst_data_file_name);
			feature_data_file_list.push_back(dst_data_file_name);
		}
	}
	//------------------------------------------------------------------------------------------

	//------------------------------------------------------------------------------------------
	// training
	//------------------------------------------------------------------------------------------
	char out_classifier_file_name[1024];
	
	sprintf(out_classifier_file_name, "%s\\%s", out_path, CLASSIFIER_FILE_NAME);
	
	EXAMPLESET* dataset = new EXAMPLESET;
		
	for(int n=0; n<(int)feature_data_file_list.size(); n++)
	{
		fprintf(stderr, "Load feature data: %s\n", feature_data_file_list[n].c_str());
		
		EXAMPLESET* tmp_dataset = read_example_set(feature_data_file_list[n].c_str());
	
		if(n == 0)  dataset->num_features = tmp_dataset->num_features;
		
		for(int i=0; i<(int)tmp_dataset->examples.size(); i++)
		{
			dataset->examples.push_back(tmp_dataset->examples[i]);
		}
	}

	MAHALANOBISDISTANCERATIOCLASSIFIER* mdr_classifier;
	mdr_classifier = training_mahalanobis_distance_ratio_classifier(dataset);

	write_mahalanobis_distance_ratio_classifier(mdr_classifier, out_classifier_file_name);

	delete_example_set(dataset);
	delete_mahalanobis_distance_ratio_classifier(mdr_classifier);
	//------------------------------------------------------------------------------------------

	return 0;
}