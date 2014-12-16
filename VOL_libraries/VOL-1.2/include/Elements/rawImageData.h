/************************************************************************************************

	VOLUME-ONE Library (VOL):
	
		rawImageData.h:	'raw' image data without geometry


	All Rights Reserved (C) 2002-	VOLUME-ONE developpers group

		2002.12.14:		first version for open source
		2004.03.05:		2nd release of VOL-1.1

************************************************************************************************/


#ifndef RAWIMAGEDATA_H


typedef struct VolRawImageData
{
	VOL_INTSIZE3D*	matrixSize;			// width height depth(channel)
	int*			pixelUnit;			// array unit
	int*			pixelType;			// type
	void**			data;				// 1D array x channels
	void***			array3D;			// 2D array x channels

} VOL_RAWIMAGEDATA;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

VOL_RAWIMAGEDATA*		VOL_NewRawImageData(VOL_INTSIZE3D* matrixSize, int* pixelUnit, int* pixelType);
VOL_RAWIMAGEDATA*		VOL_NewSingleChannelRawImageData(VOL_INTSIZE2D* matrixSize, int pixelUnit, int pixelType);
VOL_RAWIMAGEDATA*		VOL_ExtractSingleChannelRawImageData(VOL_RAWIMAGEDATA* rawImageData,int c);
VOL_RAWIMAGEDATA*		VOL_DuplicateRawImageData(VOL_RAWIMAGEDATA* rawImageData);
void					VOL_DeleteRawImageData(VOL_RAWIMAGEDATA* rawImageData);

int				VOL_GetNumberOfPixels(VOL_RAWIMAGEDATA* rawImageData);

void			VOL_SwapContentsOfRawImageData(VOL_RAWIMAGEDATA* rawImageData1,VOL_RAWIMAGEDATA* rawImageData2);

VOL_INTBOX2D*	VOL_GetBoundingBoxOfWholeImage(VOL_RAWIMAGEDATA* rawImageData);
int				VOL_CheckIfBoxIsWithinRawImageData(VOL_INTBOX2D* box,VOL_RAWIMAGEDATA* rawImageData);


int		VOL_AddNewChannelInRawImageData(VOL_RAWIMAGEDATA* rawImageData,int pixelUnit,int pixelType);
int		VOL_DuplicateChannelOfRawImageData(VOL_RAWIMAGEDATA* rawImageData,int c);
int		VOL_DeleteChannelOfRawImageData(VOL_RAWIMAGEDATA* rawImageData,int c);


void			VOL_ChangeColorTypeOfRgbaRawImageData(VOL_RAWIMAGEDATA* rawImageData);
void			VOL_InterleavedCopyRgbaRawImageData(VOL_RAWIMAGEDATA* interleaved,VOL_RAWIMAGEDATA* non_interleaved);
void			VOL_NonInterleavedCopyRgbaRawImageData(VOL_RAWIMAGEDATA* non_interleaved,int c,VOL_RAWIMAGEDATA* interleaved);

void**			VOL_GetLocal2DArrayOfImage(VOL_RAWIMAGEDATA* rawImageData,int c);
void*			VOL_GetLocal1DArrayOfImage(VOL_RAWIMAGEDATA* rawImageData,int c,int y);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

#define RAWIMAGEDATA_H
















