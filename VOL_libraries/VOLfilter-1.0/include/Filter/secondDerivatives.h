/***********************************************************************************

	Volume One Library (VOL):

		secondDerivatives.h

***********************************************************************************/

#ifndef SECONDDERIVATIVES_H


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void	VOL_SecondDerivativesFilter(VOL_RAWVOLUMEDATA* volume,float scale);	// signals -> hessian lambdas

#ifdef __cplusplus
}
#endif /* __cplusplus */



#endif	// SECONDDERIVATIVES_H


#define SECONDDERIVATIVES_H

