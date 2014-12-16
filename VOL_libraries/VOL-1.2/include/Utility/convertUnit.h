/************************************************************************************************

	VOLUME-ONE Library (VOL):
	
		convertUnit.h:	utility for conversion of unit


	All Rights Reserved (C) 2002-	VOLUME-ONE developpers group

		2002.12.14:		first version for open source
		2004.03.05:		2nd release of VOL-1.1

************************************************************************************************/

#ifndef CONVERTUNIT_H

#define VOL_CONVERTUNIT_TYPE_DIRECT					0
#define VOL_CONVERTUNIT_TYPE_DIRECT_CHECKRANGE		1
#define VOL_CONVERTUNIT_TYPE_SCALE					2
#define VOL_CONVERTUNIT_TYPE_SCALE_CHECKRANGE		3

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void	VOL_CopyArrayWithUnitConvert(int length,void* srcArray,void* dstArray,int srcUnit,int dstUnit,VOL_VALUERANGE* srcRange,VOL_VALUERANGE* dstRange,int convertsionType);

int		VOL_ConvertPixelUnit(VOL_RAWIMAGEDATA* rawImageData, int c, int newPixelUnit, VOL_VALUERANGE* oldRange,VOL_VALUERANGE* newRange, int conversionType );
int		VOL_ConvertVoxelUnit(VOL_RAWVOLUMEDATA* rawVolumeData, int c, int newVoxelUnit, VOL_VALUERANGE* oldRange,VOL_VALUERANGE* newRange, int conversionType );

void	VOL_ConvertRawVolumeRgbaToUint8x4(VOL_RAWVOLUMEDATA* rawVolumeData);
void	VOL_ConvertRawVolumeUint8x4ToRgba(VOL_RAWVOLUMEDATA* rawVolumeData);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

#define CONVERTUNIT_H
