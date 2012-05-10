#pragma warning(disable:4996) 

#include <stdio.h>
#include <math.h>

#include <string>
#include <vector>

#include "LibCircusCS.h"
#include "export.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define WINDOW_LEVEL	0
#define WINDOW_WIDTH	0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
exportImageFilesFromVolumeData(char* jobRootPath,
							   short* orgVolume,
							   unsigned char* resultVolume,
							   CircusCS_INTSIZE3D* matrixSize)
{

	//------------------------------------------------------------------------------------------------------------------
	//  Export image files (as PNG file)
	//------------------------------------------------------------------------------------------------------------------
	char orgFname[1024], resFname[1024];
	int  length = matrixSize->width * matrixSize->height;

	for(int k=0; k<matrixSize->depth; k++)
	{
		// Extreact single slice 
		short*         orgImg    = CircusCS_ExtractSingleSliceFromVolumeData<short>(orgVolume,
			                                                                        matrixSize,
																					k,
																					AXIAL_SECTION);
		unsigned char* resultImg = CircusCS_ExtractSingleSliceFromVolumeData<unsigned char>(resultVolume,
			                                                                                matrixSize,
																							k,
																							AXIAL_SECTION,
																							PIXEL_TYPE_RGB_COLOR);

		// Set window level and window width (original data) 
		unsigned char* orgImgUint8 = CircusCS_SetWindowAndConvertToUint8Image<short>(orgImg,
																					 length,
																					 WINDOW_LEVEL,
																					 WINDOW_WIDTH);
		// Export original image
		sprintf(orgFname, "%s\\org%04d.png", jobRootPath, k+1);
		CircusCS_SaveImageAsPng(orgFname, orgImgUint8, matrixSize->width, matrixSize->height);

		free(orgImg);
		free(orgImgUint8);
		

			


		// Export result image
		sprintf(resFname, "%s\\result%04d.png", jobRootPath, k+1);
		CircusCS_SaveImageAsPng(resFname, resultImg, matrixSize->width, matrixSize->height, PIXEL_TYPE_RGB_COLOR);

		free(resultImg);

	} // end for
	//------------------------------------------------------------------------------------------------------------------

	return 0;
}