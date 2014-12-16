/***********************************************************************************

	Volume One Library (VOL):

		morphology.h

***********************************************************************************/

#ifndef MORPHOLOGY_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void		VOL_DilateBinaryVolume(VOL_RAWVOLUMEDATA* rawVolumeData, int c, VOL_KERNEL* kernel);
void		VOL_ErodeBinaryVolume(VOL_RAWVOLUMEDATA* rawVolumeData, int c, VOL_KERNEL* kernel);


void		VOL_DilateBinaryVolumeBySphere(VOL_RAWVOLUMEDATA* rawVolumeData, int c, float radius);
void		VOL_ErodeBinaryVolumeBySphere(VOL_RAWVOLUMEDATA* rawVolumeData, int c, float radius);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

#define MORPHOLOGY_H
