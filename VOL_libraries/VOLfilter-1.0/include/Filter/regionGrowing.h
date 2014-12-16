/***********************************************************************************

	Volume One Library (VOL):

		regionGrowing.h

***********************************************************************************/

#ifndef REGIONGROWING_H


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

unsigned int	VOL_RegionGrowing(VOL_RAWVOLUMEDATA* rawVolumeData, int c, VOL_RAWVOLUMEDATA* seedVolume, int seedC, VOL_VOLVALUERANGE* thresholdRange, int neighbourType);
unsigned int	VOL_RegionGrowingSeededByPoints(VOL_RAWVOLUMEDATA* rawVolumeData, int c, VOL_VOLVALUERANGE* thresholdRange, int neighbourType, VOL_LOCATIONARRAY* locationArray);


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif

#define REGIONGROWING_H
