/************************************************************************************************

	VOLUME-ONE Library (VOL):
	
		scale.h:	scaling data


	All Rights Reserved (C) 2002-	VOLUME-ONE developpers group

		2002.12.14:		first version for open source
		2004.03.05:		2nd release of VOL-1.1

************************************************************************************************/

#ifndef SCALE_H

#define VOL_SCALING_METHOD_NEAREST_NEIGHBOUR	0
#define VOL_SCALING_METHOD_LINEAR				1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


void	VOL_ScaleArray(int srcLength,void* srcArray,int srcUnit,int dstLength,void* dstArray,int dstUnit);

void	VOL_ScaleRawVolumeData(VOL_RAWVOLUMEDATA* volume,VOL_INTSIZE3D* newSize,int method);
void	VOL_ScaleRawImageData(VOL_RAWIMAGEDATA* image,VOL_INTSIZE2D* newSize,int method);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

#define SCALE_H
