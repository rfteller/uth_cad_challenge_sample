/***********************************************************************************

	Volume One Library (VOL):

		thresholding.h

***********************************************************************************/

#ifndef THRESHOLDING_H


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

unsigned int	VOL_Thresholding(VOL_RAWVOLUMEDATA* rawVolumeData, int c, VOL_VALUE* threshold );
unsigned int	VOL_ThresholdingMinMax(VOL_RAWVOLUMEDATA* rawVolumeData, int c, VOL_VOLVALUERANGE* range );
unsigned int	VOL_ThresholdingBySingleFloat32Value(VOL_RAWVOLUMEDATA* rawVolumeData, int c, float threshold );

unsigned int	VOL_HysteresisThresholding(VOL_RAWVOLUMEDATA* volume, int c, VOL_VOLVALUERANGE* seedThresholdRange, VOL_VOLVALUERANGE* growThresholdRange, int neighbourType);


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif

#define THRESHOLDING_H
