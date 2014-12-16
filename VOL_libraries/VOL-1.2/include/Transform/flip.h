/************************************************************************************************

	VOLUME-ONE Library (VOL):
	
		flip.h:	flip volume


	All Rights Reserved (C) 2002-	VOLUME-ONE developpers group

		2002.12.14:		first version for open source
		2004.03.05:		2nd release of VOL-1.1

************************************************************************************************/

#ifndef FLIP_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void	VOL_FlipRawVolumeData(VOL_RAWVOLUMEDATA* rawVolumeData,int c,VOL_INTBOX3D* boxVOI,char* directionString);
void	VOL_FlipRawImageData(VOL_RAWIMAGEDATA* rawImageData,int c,VOL_INTBOX2D* boxROI,char* directionString);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

#define FLIP_H
