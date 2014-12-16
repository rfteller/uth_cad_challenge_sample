/************************************************************************************************

	VOLUME-ONE Library (VOL):
	
		overlay.h:	data merge functions


	All Rights Reserved (C) 2002-	VOLUME-ONE developpers group

		2002.12.14:		first version for open source
		2004.03.05:		2nd release of VOL-1.1

************************************************************************************************/


#ifndef OVERLAY_H

#define VOL_DATAOVERLAYTYPE_AVERAGE		123
#define VOL_DATAOVERLAYTYPE_LOWER		356
#define VOL_DATAOVERLAYTYPE_HIGHER		458
#define VOL_DATAOVERLAYTYPE_SUBTRACTION	765

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int		VOL_OverlayRawVolumeData(VOL_RAWVOLUMEDATA* src1,VOL_RAWVOLUMEDATA* src2,VOL_RAWVOLUMEDATA* dst,int type);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif

#define OVERLAY_H
