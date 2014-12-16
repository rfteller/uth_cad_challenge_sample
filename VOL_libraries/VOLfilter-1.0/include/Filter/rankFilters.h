/***********************************************************************************

	Volume One Library (VOL):

		rankFilters.h

***********************************************************************************/

#ifndef RANKFILTERS_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void		VOL_RankFilter(VOL_RAWVOLUMEDATA* rawVolumeData, int c, VOL_KERNEL* kernel, int rank);
void		VOL_MedianFilter(VOL_RAWVOLUMEDATA* rawVolumeData, int c, VOL_KERNEL* kernel);

void		VOL_MinimumFilter(VOL_RAWVOLUMEDATA* rawVolumeData, int c, VOL_KERNEL* kernel);
void		VOL_MaximumFilter(VOL_RAWVOLUMEDATA* rawVolumeData, int c, VOL_KERNEL* kernel);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

#define RANKFILTERS_H
