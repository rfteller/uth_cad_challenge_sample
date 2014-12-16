/***********************************************************************************

	Volume One Library (VOL):

		labeled_morphology.h

***********************************************************************************/

#ifndef LABELED_MORPHOLOGY_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void		VOL_DilateLabeledVolume(VOL_RAWVOLUMEDATA* labeledVolumeData, int c, int iteration);
void		VOL_ErodeLabeledVolume(VOL_RAWVOLUMEDATA* labeledVolumeData, int c, int iteration);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

#define LABELED_MORPHOLOGY_H
