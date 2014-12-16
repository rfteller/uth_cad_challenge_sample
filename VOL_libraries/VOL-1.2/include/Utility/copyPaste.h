/************************************************************************************************

	VOLUME-ONE Library (VOL):
	
		copyPaste.h:	data copy & paste


	All Rights Reserved (C) 2002-	VOLUME-ONE developpers group

		2002.12.14:		first version for open source
		2004.03.05:		2nd release of VOL-1.1

************************************************************************************************/

#ifndef COPYPASTE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void	VOL_CopyRawVolumeData(	VOL_RAWVOLUMEDATA* srcData,int srcC, VOL_RAWVOLUMEDATA* dstData,int dstC,
										VOL_INTBOX3D* srcBox,VOL_INTVECTOR3D* dstOrigin);

void	VOL_CopyRawImageData(VOL_RAWIMAGEDATA* srcData,int srcC,VOL_RAWIMAGEDATA* dstData,int dstC,
										VOL_INTBOX2D* srcBox,VOL_INTVECTOR2D* dstOrigin);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

#define COPYPASTE_H
