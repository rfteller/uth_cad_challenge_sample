/***********************************************************************************

	Volume One Library (VOL):

		curvature.h

***********************************************************************************/


#ifndef CURVATURE_H

#define VOL_CURVATURE_TYPE_GAUSSIAN_AND_MEAN			0
#define VOL_CURVATURE_TYPE_TWO_PRINCIPALS				1
#define VOL_CURVATURE_TYPE_SHAPE_INDEX_AND_CURVEDNESS	2

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


void	VOL_CurvatureFilter(VOL_RAWVOLUMEDATA* volume,float scale,int type);
void	VOL_ConvertCurvature(VOL_RAWVOLUMEDATA* volume,int src_type,int dst_type);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

#define CURVATURE_H
