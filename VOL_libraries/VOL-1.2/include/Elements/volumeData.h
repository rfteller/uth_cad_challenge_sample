/************************************************************************************************

	VOLUME-ONE Library (VOL):

		volumeData.h:	volume data with geometry


	All Rights Reserved (C) 2002-	VOLUME-ONE developpers group

		2002.12.14:		first version for open source
		2004.03.05:		2nd release of VOL-1.1

************************************************************************************************/

#ifndef VOLUMEDATA_H

typedef struct VolVolumeData
{
	VOL_RAWVOLUMEDATA*	rawVolumeData;	// raw volume data

	VOL_COLORMAP**	colormap;

	VOL_VECTOR3D*	origin;
	VOL_VECTOR3D	*u, *v, *w;			// directional unit vectors |u|=|v|=|w|=1
	VOL_SIZE3D*		voxelSize;

	char*	voxelSizeUnitString;		// unit strings
	char**	channelDescriptionString;	// ex. scale value, name (red, blue, ...), faeature, etc.

} VOL_VOLUMEDATA;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

VOL_VOLUMEDATA*		VOL_NewVolumeData(VOL_INTSIZE4D* matrixSize, int* voxelUnit, int* voxelType);
VOL_VOLUMEDATA*		VOL_NewVolumeDataFromRawVolumeData(VOL_RAWVOLUMEDATA* rawVolumeData);
VOL_VOLUMEDATA*		VOL_NewSingleChannelVolumeData(VOL_INTSIZE3D* matrixSize, int voxelUnit, int voxelType);
VOL_VOLUMEDATA*		VOL_ExtractSingleChannelVolumeData(VOL_VOLUMEDATA* rawVolumeData,int c);
VOL_VOLUMEDATA*		VOL_DuplicateVolumeData(VOL_VOLUMEDATA* volumeData);
void				VOL_DeleteVolumeData(VOL_VOLUMEDATA* volumeData);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

#define VOLUMEDATA_H
