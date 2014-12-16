////////////////////////////////////////////////////////////////////////////////////////
//
//
//		Volume One Library (VOL):
//
//		volumeOneFileImportExport.h: I/O function for Volume-One file (.vol)  
//
//			main coder: Y. Nomura
//
//			update history
//
//			2013.08.16 Add to VOLfilter
//
//
////////////////////////////////////////////////////////////////////////////////////////


#ifndef VOLUME_ONE_FILE_IO_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

VOL_RAWVOLUMEDATA*	VOL_LoadVolumeOneFile(char* fileName);
int					VOL_SaveVolumeOneFile(char* fileName, VOL_RAWVOLUMEDATA* volume);

VOL_VECTOR3D*	VOL_LoadCursorMemory(char* fileName, int* numMemory);
int				VOL_SaveCursorMemory(char* fileName, VOL_MATRIX* pos);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

#define VOLUME_ONE_FILE_IO_H
