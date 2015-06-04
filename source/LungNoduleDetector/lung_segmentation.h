////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Sample codes for UTH CAD Challenge
//
//	      lung_segmentation.h : Lung are segmentation from CT images
//
//    [CAUTION 1] The sample codes are permitted to use only for research purposes.
//
//    [CAUTION 2] If you use this algorithm, you should cite the paper: 
//                   Nomura Y et al., "Reduction of false positives at vessel bifurcations in
//                   omputerized detection of lung nodules," Journal of Biomedical Graphics and
//                   Computing, vol.4, no.3, pp.36-46, 2014.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef LUNG_SEGMENTATION_H
#define LUNG_SEGMENTATION_H

#ifdef __cplusplus
extern "C"
{
#endif

void lung_segmentation(VOL_RAWVOLUMEDATA* volume);

#ifdef __cplusplus
}
#endif

#endif
