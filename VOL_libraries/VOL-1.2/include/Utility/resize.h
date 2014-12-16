/************************************************************************************************

	VOLUME-ONE Library (VOL):
	
		resize.h:	resizing data (attaching offset, etc.)


	All Rights Reserved (C) 2002-	VOLUME-ONE developpers group

		2002.12.14:		first version for open source
		2004.03.05:		2nd release of VOL-1.1

************************************************************************************************/


#ifndef RESIZE_H

#define VOL_RESIZE_BACKGROUNDTYPE_ZERO					0
#define VOL_RESIZE_BACKGROUNDTYPE_BORDERCOPY_MIRROR		1
#define VOL_RESIZE_BACKGROUNDTYPE_BORDERCOPY_UNIFORM	2

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int		VOL_ResizeRawVolumeData(VOL_RAWVOLUMEDATA* rawVolumeData,VOL_INTBOX3D* box,int backgroundType);

int		VOL_AttachOffsetXYZ(VOL_RAWVOLUMEDATA* rawVolumeData,int offset,int backgroundType);
int		VOL_RemoveOffsetXYZ(VOL_RAWVOLUMEDATA* rawVolumeData,int offset);

int		VOL_AttachOffsetXY(VOL_RAWVOLUMEDATA* rawVolumeData,int offset,int backgroundType);
int		VOL_RemoveOffsetXY(VOL_RAWVOLUMEDATA* rawVolumeData,int offset);

int		VOL_AttachOffsetZ(VOL_RAWVOLUMEDATA* rawVolumeData,int offset,int backgroundType);
int		VOL_RemoveOffsetZ(VOL_RAWVOLUMEDATA* rawVolumeData,int offset);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

#define RESIZE_H

