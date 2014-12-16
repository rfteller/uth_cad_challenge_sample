/************************************************************************************************

	VOLUME-ONE Library (VOL):
	
		rawVolumeData.h:	'raw' volume data without geometry


	All Rights Reserved (C) 2002-	VOLUME-ONE developpers group

		2002.12.14:		first version for open source
		2004.03.05:		2nd release of VOL-1.1

************************************************************************************************/


#ifndef RAWVOLUMEDATA_H


typedef struct VolRawVolumeData
{
	VOL_INTSIZE4D*	matrixSize;
	int*			voxelUnit;			// array unit
	int*			voxelType;			// type
	void**			data;				// 1D array x channels
	void****		array4D;			// 3D array x channels

} VOL_RAWVOLUMEDATA;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

VOL_RAWVOLUMEDATA*		VOL_NewRawVolumeData(VOL_INTSIZE4D* matrixSize,int* voxelUnit,int* voxelType);
VOL_RAWVOLUMEDATA*		VOL_NewSingleChannelRawVolumeData(VOL_INTSIZE3D* matrixSize,int voxelUnit,int voxelType);
VOL_RAWVOLUMEDATA*		VOL_ExtractSingleChannelRawVolumeData(VOL_RAWVOLUMEDATA* rawVolumeData,int c);
VOL_RAWVOLUMEDATA*		VOL_DuplicateRawVolumeData(VOL_RAWVOLUMEDATA* rawVolumeData);
void					VOL_DeleteRawVolumeData(VOL_RAWVOLUMEDATA* rawVolumeData);

int				VOL_GetNumberOfVoxels(VOL_RAWVOLUMEDATA* rawVolumeData);
VOL_INTBOX3D*	VOL_GetBoundingBoxOfWholeVolume(VOL_RAWVOLUMEDATA* rawVolumeData);
int				VOL_CheckIfBoxIsWithinRawVolumeData(VOL_INTBOX3D* box,VOL_RAWVOLUMEDATA* rawVolumeData);

void			VOL_SwapContentsOfRawVolumeData(VOL_RAWVOLUMEDATA* rawVolumeData1,VOL_RAWVOLUMEDATA* rawVolumeData2);
void			VOL_SwapChannelsOfRawVolumeData(VOL_RAWVOLUMEDATA* rawVolumeData1,int c1,VOL_RAWVOLUMEDATA* rawVolumeData2,int c2);

void			VOL_ForceIntBox3DWithinRawVolumeData(VOL_INTBOX3D* box,VOL_RAWVOLUMEDATA* volume);

int			VOL_AddNewChannelInRawVolumeData(VOL_RAWVOLUMEDATA* rawVolumeData,int voxelUnit,int voxelType);
int			VOL_AddNewChannelOfRawVolumeData(VOL_RAWVOLUMEDATA* dstVolume,VOL_RAWVOLUMEDATA* srcVolume,int src_channel);
int			VOL_DuplicateChannelOfRawVolumeData(VOL_RAWVOLUMEDATA* rawVolumeData,int c);
int			VOL_DeleteChannelOfRawVolumeData(VOL_RAWVOLUMEDATA* rawVolumeData,int c);

int			VOL_DivideSingleChannelRawVolumeData(VOL_RAWVOLUMEDATA* rawVolumeData,int channels,int interleavedType);

void			VOL_ChangeColorTypeOfRgbaRawVolumeData(VOL_RAWVOLUMEDATA* volume);
void			VOL_InterleavedCopyRgbaRawVolumeData(VOL_RAWVOLUMEDATA* interleaved,VOL_RAWVOLUMEDATA* non_interleaved);
void			VOL_NonInterleavedCopyRgbaRawVolumeData(VOL_RAWVOLUMEDATA* non_interleaved,int c,VOL_RAWVOLUMEDATA* interleaved);

void***			VOL_GetLocal3DArrayOfVolume(VOL_RAWVOLUMEDATA* rawVolumeData,int c);
void**			VOL_GetLocal2DArrayOfVolume(VOL_RAWVOLUMEDATA* rawVolumeData,int c,int z);
void*			VOL_GetLocal1DArrayOfVolume(VOL_RAWVOLUMEDATA* rawVolumeData,int c,int z,int y);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

#define RAWVOLUMEDATA_H
