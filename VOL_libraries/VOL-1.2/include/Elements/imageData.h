/************************************************************************************************

	VOLUME-ONE Library (VOL):

		imageData.h:	image data with geometry


	All Rights Reserved (C) 2002-	VOLUME-ONE developpers group

		2002.12.14:		first version for open source
		2004.03.05:		2nd release of VOL-1.1

************************************************************************************************/

#ifndef IMAGEDATA_H

typedef struct VolImageData
{
	VOL_RAWIMAGEDATA*	rawImageData;	// raw image data

	VOL_COLORMAP**	colormap;

	VOL_VECTOR2D*	origin;
	VOL_VECTOR2D	*u, *v;				// directional unit vectors |u|=|v|=1
	VOL_VECTOR3D	*O, *U, *V;			// origin and directional unit vectors in 3D space
	VOL_SIZE2D*		pixelSize;

	char*	pixelSizeUnitString;		// unit strings
	char**	channelDescriptionString;	// ex. scale value, name (red, blue, ...), faeature, etc.

} VOL_IMAGEDATA;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

VOL_IMAGEDATA*		VOL_NewImageData(VOL_INTSIZE3D* matrixSize, int* pixelUnit, int* pixelType);
VOL_IMAGEDATA*		VOL_NewSingleChannelImageData(VOL_INTSIZE2D* matrixSize, int pixelUnit, int pixelType);
VOL_IMAGEDATA*		VOL_ExtractSingleChannelImageData(VOL_IMAGEDATA* rawImageData,int c);
VOL_IMAGEDATA*		VOL_DuplicateImageData(VOL_IMAGEDATA* imageData);
void				VOL_DeleteImageData(VOL_IMAGEDATA* imageData);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

#define IMAGEDATA_H
