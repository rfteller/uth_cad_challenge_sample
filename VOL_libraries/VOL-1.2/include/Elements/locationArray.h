/************************************************************************************************

	VOLUME-ONE Library (VOL):
	
		locationArray.h:	array for 2D/3D locations


	All Rights Reserved (C) 2002-	VOLUME-ONE developpers group

		2002.12.14:		first version for open source
		2004.03.05:		2nd release of VOL-1.1

************************************************************************************************/

#ifndef LOCATIONARRAY_H


typedef struct VolLocationArray
{
	int		nElements, nElementsMax;
	int		xMin, yMin, zMin;
	int		xMax, yMax, zMax;
	int		*x, *y, *z;
	int		*rasterPosition;

	VOL_INTSIZE3D*	rasterMatrixSize;

} VOL_LOCATIONARRAY;




#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

VOL_LOCATIONARRAY*	VOL_NewLocationArray(int nElementsMax);
VOL_LOCATIONARRAY*	VOL_NewLocationArrayFromBinaryVolumeData(VOL_RAWVOLUMEDATA* volume,int c);	// from a channel
void				VOL_DeleteLocationArray(VOL_LOCATIONARRAY* locationArray);

void	VOL_SetRasterPositionOfLocationArrayElements(VOL_LOCATIONARRAY* locationArray,VOL_INTSIZE3D*	matrixSize);

int		VOL_AppendLocationArrayElement(VOL_LOCATIONARRAY* locationArray,VOL_INTVECTOR3D* location);
int		VOL_AddLocationArrayElement(VOL_LOCATIONARRAY* locationArray,VOL_INTVECTOR3D* location);
int		VOL_DeleteLocationArrayElement(VOL_LOCATIONARRAY* locationArray,VOL_INTVECTOR3D* location);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif

#define LOCATIONARRAY_H
