/************************************************************************************************

	VOLUME-ONE Library (VOL):
	
		misc.h:	misc functions (clear, replace value, etc.)


	All Rights Reserved (C) 2002-	VOLUME-ONE developpers group

		2002.12.14:		first version for open source
		2004.03.05:		2nd release of VOL-1.1

************************************************************************************************/


#ifndef MISC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void	VOL_ClearRawImageData(VOL_RAWIMAGEDATA* image,int c);
void	VOL_ClearRawVolumeData(VOL_RAWVOLUMEDATA* volume,int c);

void	VOL_ClearRawImageDataByMinimumValue(VOL_RAWIMAGEDATA* image,int c);
void	VOL_ClearRawVolumeDataByMinimumValue(VOL_RAWVOLUMEDATA* volume,int c);

void	VOL_ReplaceValueOfRawVolumeData(VOL_RAWVOLUMEDATA* volume,int c,VOL_VALUE* srcValue,VOL_VALUE* dstValue);
void	VOL_ShiftValueOfRawVolumeData(VOL_RAWVOLUMEDATA* volume,int c,VOL_VALUE* shift,int fRangeCheck);
void	VOL_ScaleValueOfRawVolumeData(VOL_RAWVOLUMEDATA* volume,int c,float factor,float bias,int fRangeCheck);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif

#define MISC_H
