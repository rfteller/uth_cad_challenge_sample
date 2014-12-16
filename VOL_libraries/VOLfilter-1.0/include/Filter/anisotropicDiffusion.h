/***********************************************************************************

	Volume One Library (VOL):

		anisotropicDiffusion.h

***********************************************************************************/

#ifndef ANISOTROPICDIFFUSION_H



#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void		VOL_AnisotropicDiffusionFilter(VOL_RAWVOLUMEDATA* volume,int c,float sigma,float lambda,int nIteration);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

#define ANISOTROPICDIFFUSION_H

