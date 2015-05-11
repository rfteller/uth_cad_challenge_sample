#define _CRT_SECURE_NO_DEPRECATE

#include<stdio.h>

#include "LibCircusCS.h"
#include "aneurysm_detection.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main(int argc, char *argv[])
{
	// Check the number of arguments
	if(argc < 4 || argc > 5) 
	{
		fprintf(stderr, "[Usage] AneurysmDetector.exe [input path] [output path] [number of cores]");
		fprintf(stderr, " [mode (1:detection(default), 2:feature extraction only)]\n");	
		return -1;
	}

	char in_path[1024];
	char out_path[1024];

	// Set input/output path
	strcpy(in_path,  argv[1]);
	strcpy(out_path, argv[2]);

	// Get the number of cores
	int coreNum = atoi(argv[3]);

	// Set mode
	int mode = (argc == 5 && atoi(argv[4]) == 2) ? 2 : 1;

	// Aneurysm detection
	int candNum = aneurysm_detection_in_mra(
		in_path, 
		out_path, 
		coreNum,
		mode);

	return 0;
}
