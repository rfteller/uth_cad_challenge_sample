#ifndef MASKING_H


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void	VOL_MaskRawVolumeData(VOL_RAWVOLUMEDATA* volume, int c, VOL_RAWVOLUMEDATA* mask, int cMask,VOL_VALUE* background_value);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

#define MASKING_H
