/************************************************************************************************

	VOLUME-ONE Library (VOL):
	
		reformat.h:	reformating data (multi-chan. image -> volume, etc.)


	All Rights Reserved (C) 2002-	VOLUME-ONE developpers group

		2002.12.14:		first version for open source
		2004.03.05:		2nd release of VOL-1.1

************************************************************************************************/

#ifndef REFORMAT_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

VOL_RAWVOLUMEDATA* 	VOL_ReformatToSingleChannelVolume(VOL_RAWIMAGEDATA* image);
VOL_RAWIMAGEDATA*	VOL_ReformatToMultiChannelImage(VOL_RAWVOLUMEDATA* single_channel_volume);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

#define REFORMAT_H
