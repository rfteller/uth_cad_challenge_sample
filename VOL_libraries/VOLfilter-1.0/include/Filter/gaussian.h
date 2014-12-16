/***********************************************************************************

	Volume One Library (VOL):

		gaussian.h

***********************************************************************************/

#ifndef GAUSSIAN_H



#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void		VOL_GaussianFilter(VOL_RAWVOLUMEDATA* volume,int c,float sigma);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

#define GAUSSIAN_H

