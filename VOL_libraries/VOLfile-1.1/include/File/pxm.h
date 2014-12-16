/***********************************************************************************

	Volume One Library (VOL):

		pxm.h

***********************************************************************************/

#ifndef PXM_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

VOL_RAWIMAGEDATA*	VOL_ReadPXM( char* fname );
int					VOL_WritePXM( char* fname, VOL_RAWIMAGEDATA* image, int c );

VOL_RAWIMAGEDATA*	VOL_ReadPGM( char* fname );
VOL_RAWIMAGEDATA*	VOL_ReadPPM( char* fname );
int					VOL_WritePGM( char* fname, VOL_RAWIMAGEDATA* image, int c );
int					VOL_WritePPM( char* fname, VOL_RAWIMAGEDATA* image, int c );


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif

#define PXM_H
