////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Sample codes for UTH CAD Challenge
//
//	      aneurysm_detector_main.cpp : Main function of lung nodule detector
//
//    [CAUTION] The sample codes are permitted to use only for research purposes.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_DEPRECATE

#include<stdio.h>

#include "LibCircusCS.h"
#include "lung_nodule_detection.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	// Check the number of arguments
	if(argc < 4 || argc > 5) 
	{
		fprintf(stderr, "[Usage] LungNoduleDetector.exe [input path] [output path]");
		fprintf(stderr, " [number of cores]");
		fprintf(stderr, " [mode (1:detection(default), 2:feature extraction only)]\n");	
		return -1;
	}

	char in_path[1024];
	char out_path[1024];

	// Set input/output path
	strcpy(in_path,  argv[1]);
	strcpy(out_path, argv[2]);

	// Get the number of cores
	int core_num = atoi(argv[3]);

	// Set mode
	int mode = (argc == 5 && atoi(argv[4]) == 2) ? 2 : 1;

	// Lung nodule detection
	int candidates_num = lung_nodule_detection(
		in_path, 
		out_path, 
		core_num,
		mode);

	return 0;
}
