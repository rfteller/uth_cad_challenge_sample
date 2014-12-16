/***********************************************************************************

	Volume One Library (VOL):

		convolution.h

***********************************************************************************/

#ifndef CONVOLUTION_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void		VOL_Convolution(VOL_RAWVOLUMEDATA* volume, int c, VOL_KERNEL* kernel);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

#define CONVOLUTION_H
