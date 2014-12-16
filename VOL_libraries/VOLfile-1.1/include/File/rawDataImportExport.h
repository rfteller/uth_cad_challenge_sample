/***********************************************************************************

	Volume One Library (VOL):

		rawDataImportExport.h

***********************************************************************************/

#ifndef RAWDATAIMPORTEXPORT_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int		VOL_GetFileLength(char* filename);

int		VOL_ImportRawVolumeData( char* filename, VOL_RAWVOLUMEDATA* rawVolumeData, int offset );
int		VOL_ExportRawVolumeData( char* filename, VOL_RAWVOLUMEDATA* rawVolumeData);
int		VOL_AddRawVolumeDataToFile( FILE* fp, VOL_RAWVOLUMEDATA* rawVolumeData);

int		VOL_ImportSingleChannelOfRawVolumeData( char* filename, VOL_RAWVOLUMEDATA* rawVolumeData, int c, int offset );
int		VOL_ExportSingleChannelOfRawVolumeData( char* filename, VOL_RAWVOLUMEDATA* rawVolumeData, int c );

int		VOL_ImportSingleSlice( char* filename, VOL_RAWVOLUMEDATA* rawVolumeData, int c, int z, int offset );

VOL_RAWVOLUMEDATA*	VOL_NewSingleChannelRawVolumeDataFromFile(char* filename,VOL_INTSIZE3D* matrixSize,int voxelUnit,int voxelType,int offset);

int		VOL_ImportBinaryVolume( char* filename, VOL_RAWVOLUMEDATA* rawVolumeData, int c, int offset );
int		VOL_ExportBinaryVolume( char* filename, VOL_RAWVOLUMEDATA* rawVolumeData, int c );
 
#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif

#define RAWDATAIMPORTEXPORT_H
