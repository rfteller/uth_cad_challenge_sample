/************************************************************************************************

	VOLUME-ONE Library (VOL):
	
		binaryVolume.h:	binary volume data


	All Rights Reserved (C) 2002-	VOLUME-ONE developpers group

		2002.12.14:		first version for open source
		2004.03.05:		2nd release of VOL-1.1

************************************************************************************************/

#ifndef BINARYVOLUME_H

#define VOL_BINARYVOLUME_BACKGROUND		0		// must NOT be changed
#define VOL_BINARYVOLUME_FOREGROUND		1		// must NOT be changed



#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int		VOL_CheckIfTheChannelIsBinaryVolume(VOL_RAWVOLUMEDATA* rawVolumeData, int c);					// c: channel id

void	VOL_ClearBinaryVolume(VOL_RAWVOLUMEDATA* rawVolumeData,int c);
void	VOL_InvertBinaryVolume(VOL_RAWVOLUMEDATA* rawVolumeData, int c);

void	VOL_ForceToBeBinaryVolume(VOL_RAWVOLUMEDATA* rawVolumeData, int c);		// non zero -> foreground

int		VOL_CountForegroundVoxelsOfBinaryVolume(VOL_RAWVOLUMEDATA* rawVolumeData, int c);
int		VOL_CountBackgroundVoxelsOfBinaryVolume(VOL_RAWVOLUMEDATA* rawVolumeData, int c);

VOL_INTBOX3D*	VOL_GetMinimumBoundingBoxOfBinaryVolume(VOL_RAWVOLUMEDATA* rawVolumeData,int c);



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

#define BINARYVOLUME_H
