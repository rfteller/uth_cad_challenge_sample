/************************************************************************************************

	VOLUME-ONE Library (VOL):
	
		rotate.h:	rotate volume


	All Rights Reserved (C) 2002-	VOLUME-ONE developpers group

		2002.12.14:		first version for open source
		2004.03.05:		2nd release of VOL-1.1

************************************************************************************************/

#ifndef ROTATE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int		VOL_RotateRawVolumeData(VOL_RAWVOLUMEDATA* volume, char* axis_string);
int		VOL_RotateRawVolumeData90deg(VOL_RAWVOLUMEDATA* volume, char* axis_string);
int		VOL_RotateRawVolumeData180deg(VOL_RAWVOLUMEDATA* volume, char* axis_string);

int		VOL_RotateRawVolumeDataByAngle(VOL_RAWVOLUMEDATA* volume, char* axis_string,float degree);

int		VOL_RotateChannelOfRawVolumeDataByAngle(VOL_RAWVOLUMEDATA* volume, int c, char* axis_string,float degree);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

#define ROTATE_H
