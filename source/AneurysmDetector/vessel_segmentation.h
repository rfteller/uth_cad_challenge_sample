
#ifndef VESSEL_SEGMENTATION_H
#define VESSEL_SEGMENTATION_H

#ifdef __cplusplus
extern "C"
{
#endif

#define MIN_SEARCH	16
#define	MAX_SEARCH	5120

void getStaticticsOfBrainLevel(
	VOL_RAWVOLUMEDATA* volume,
	float* brain_mean,
	float* brain_sigma);

VOL_INTBOX3D* getBrainBox(
	VOL_RAWVOLUMEDATA* original,
	float brain_mean,
	float brain_sigma,
	char* log_file_name);

VOL_RAWVOLUMEDATA* getVesselMask(
	VOL_RAWVOLUMEDATA* original,
	VOL_INTBOX3D* brain_box,
	float brain_mean,
	float brain_sigma,
	char* log_file_name);

#ifdef __cplusplus
}
#endif

#endif
