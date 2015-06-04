////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Sample codes for UTH CAD Challenge
//
//	      aneurysm_training_main.cpp : Main function of training program 
//                                      for cerebral aneurysm detection
//
//    [CAUTION] The sample codes are permitted to use only for research purposes.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aneurysm_training.h"

////////////////////////////////////////////////////////////////////////////////////////////////////


int main(int argc, char *argv[])
{
	// Check the number of arguments
	if(argc != 3) 
	{
		fprintf(stderr, "[Usage] AneurysmDetector_training.exe [configuration file name]");
		fprintf(stderr, " [number of cores]\n");
		return -1;
	}

	char configuration_file_name[1024];

	// Set configuration file name
	strcpy(configuration_file_name, argv[1]);

	// Get the number of cores
	int core_num = atoi(argv[2]);

	// Aneurysm detection
	aneurysm_detector_training(configuration_file_name, core_num);

	return 0;
}
