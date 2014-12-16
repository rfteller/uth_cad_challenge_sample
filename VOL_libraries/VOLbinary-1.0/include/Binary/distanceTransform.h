#ifndef DISTANCETRANSFORM_H


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int	VOL_DistanceTransform(VOL_RAWVOLUMEDATA* rawVolumeData, int c, int distance_type);
int	VOL_DistanceTransformByVoxelList(VOL_RAWVOLUMEDATA* rawVolumeData, int c, int distance_type);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

#define DISTANCETRANSFORM_H
