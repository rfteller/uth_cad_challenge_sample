/***********************************************************************************

	Volume One Library (VOL):

		gradient.h

***********************************************************************************/

#ifndef GRADIENT_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void		VOL_GradientFilter(VOL_RAWVOLUMEDATA* volume, int c, char* direction);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

#define GRADIENT_H
