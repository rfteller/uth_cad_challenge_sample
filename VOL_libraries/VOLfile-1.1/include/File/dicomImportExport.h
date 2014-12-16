/***********************************************************************************

	Volume One Library (VOL):

		dicomImport.h

***********************************************************************************/

#ifndef DICOMIMPORTEXPORT_H

/*
#define DICOM_VR_TYPE_US	0
#define DICOM_VR_TYPE_SS	0
#define DICOM_VR_TYPE_UL	0
#define DICOM_VR_TYPE_SL	0
#define DICOM_VR_TYPE_US	0
#define DICOM_VR_TYPE_US	0
#define DICOM_VR_TYPE_US	0
#define DICOM_VR_TYPE_US	0
#define DICOM_VR_TYPE_US	0
#define DICOM_VR_TYPE_US	0
#define DICOM_VR_TYPE_US	0
#define DICOM_VR_TYPE_US	0
#define DICOM_VR_TYPE_US	0
#define DICOM_VR_TYPE_US	0
#define DICOM_VR_TYPE_US	0
*/



typedef struct VolDicomDataElement
{
	unsigned short	groupID;
	unsigned short	elementID;
	unsigned int	elementLength;
	unsigned char	elementType[8];
	int				elementTypeLength;	// 4 or 8
	int				vrType;

	void*			data;

} VOL_DICOMDATAELEMENT;


typedef struct VolDicomElementList
{
	unsigned short	groupID;

	unsigned int	groupLength;

	int				fNeglect;

	VOL_LIST*	elements;

} VOL_DICOMELEMENTLIST;


typedef struct VolDicomData
{
	VOL_LIST*	groups;

} VOL_DICOMDATA;



#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


VOL_DICOMELEMENTLIST*	VOL_NewDicomElementList();
void					VOL_DeleteDicomElementList(VOL_DICOMELEMENTLIST* elementList);

VOL_DICOMDATA*	VOL_NewDicomData();
VOL_DICOMDATA*	VOL_GetDicomDataFromFile(char* filename);
int				VOL_WriteDicomDataToFile(char* filename,VOL_DICOMDATA* dicomData);
void			VOL_DeleteDicomData(VOL_DICOMDATA* dicomData);

int			VOL_GetSingleDataElementFromDicomFile(char* filename,unsigned short groupWord,unsigned short elementWord,int* _elementLength,char* buffer);

int			VOL_ReplaceDicomElement(VOL_DICOMDATA* dicomData,unsigned short groupWord,unsigned short elementWord,char* data,int elementLength);
int			VOL_ReplaceDicomElementUS(VOL_DICOMDATA* dicomData,unsigned short groupWord,unsigned short elementWord,unsigned short us);
int			VOL_ReplaceDicomElementSS(VOL_DICOMDATA* dicomData,unsigned short groupWord,unsigned short elementWord,short ss);
int			VOL_ReplaceDicomElementUL(VOL_DICOMDATA* dicomData,unsigned short groupWord,unsigned short elementWord,unsigned int ul);
int			VOL_ReplaceDicomElementSL(VOL_DICOMDATA* dicomData,unsigned short groupWord,unsigned short elementWord,int sl);
int			VOL_ReplaceDicomElementIS(VOL_DICOMDATA* dicomData,unsigned short groupWord,unsigned short elementWord,int integer);

int			VOL_InsertDicomElement(VOL_DICOMDATA* dicomData,VOL_DICOMDATAELEMENT* dataElement);


int		VOL_GetDicomHeaderLength(char* filename);

int		VOL_GetImageNumberOfDicomFile(char* filename,int* image_number);
int		VOL_GetSopInstanceUidOfDicomFile(char* filename,char* string);
int		VOL_GetMediaStorageSopInstanceUidOfDicomFile(char* filename,char* string);
int		VOL_GetMatrixSizeOfDicomFile(char* filename,VOL_INTSIZE2D* matrixSize);
int		VOL_GetFieldOfViewOfDicomFile(char* filename,float* fov);
int		VOL_GetDistanceBetweenSlicesOfDicomFile(char* filename,float* dbs);
int		VOL_GetSliceThicknesssOfDicomFile(char* filename,float* thickness);
int		VOL_GetTablePositionOfDicomFile(char* filename,float* table_position);
int		VOL_GetImagePositionOfDicomFile(char* filename,VOL_VECTOR3D* image_position);
int		VOL_GetPixelUnitOfDicomFile(char* filename,int* pixel_unit);
int		VOL_GetImagesInAcquisitionOfDicomFile(char* filename,int* number);


int		VOL_GetImageNumberOfDicomData(VOL_DICOMDATA* dicomData,int* image_number);
int		VOL_GetStudyInstanceUidOfDicomData(VOL_DICOMDATA* dicomData,char* string);
int		VOL_GetSeriesNumberOfDicomData(VOL_DICOMDATA* dicomData,int* series_number);
int		VOL_GetSopInstanceUidOfDicomData(VOL_DICOMDATA* dicomData,char* string);
int		VOL_GetMediaStorageSopInstanceUidOfDicomData(VOL_DICOMDATA* dicomData,char* string);
int		VOL_GetMatrixSizeOfDicomData(VOL_DICOMDATA* dicomData,VOL_INTSIZE2D* matrixSize);
int		VOL_GetFieldOfViewOfDicomData(VOL_DICOMDATA* dicomData,float* fov);
int		VOL_GetSliceThicknessOfDicomData(VOL_DICOMDATA* dicomData,float* thickness);
int		VOL_GetDistanceBetweenSlicesOfDicomData(VOL_DICOMDATA* dicomData,float* dbs);
int		VOL_GetTablePositionOfDicomData(VOL_DICOMDATA* dicomData,float* table_position);
int		VOL_GetImagePositionOfDicomData(VOL_DICOMDATA* dicomData,VOL_VECTOR3D* image_position);
int		VOL_GetPixelUnitOfDicomData(VOL_DICOMDATA* dicomData,int* pixel_unit);
int		VOL_GetImagesInAcquisitionOfDicomData(VOL_DICOMDATA* dicomData,int* number);

int		VOL_SetImageNumberOfDicomData(VOL_DICOMDATA* dicomData,int image_number);
int		VOL_SetSopInstanceUidOfDicomData(VOL_DICOMDATA* dicomData,char* string);
int		VOL_SetStudyInstanceUidOfDicomData(VOL_DICOMDATA* dicomData,char* string);
int		VOL_SetSeriesInstanceUidOfDicomData(VOL_DICOMDATA* dicomData,char* string);
int		VOL_SetMediaStorageSopInstanceUidOfDicomData(VOL_DICOMDATA* dicomData,char* string);
int		VOL_SetMatrixSizeOfDicomData(VOL_DICOMDATA* dicomData,VOL_INTSIZE2D* matrixSize);
int		VOL_SetFieldOfViewOfDicomData(VOL_DICOMDATA* dicomData,float fov);
int		VOL_SetSliceThicknessOfDicomData(VOL_DICOMDATA* dicomData,float thickness);
int		VOL_SetDistanceBetweenSlicesOfDicomData(VOL_DICOMDATA* dicomData,float dbs);
int		VOL_SetTablePositionOfDicomData(VOL_DICOMDATA* dicomData,float table_position);
int		VOL_SetImagePositionOfDicomData(VOL_DICOMDATA* dicomData,VOL_VECTOR3D* image_position);
int		VOL_SetPixelUnitOfDicomData(VOL_DICOMDATA* dicomData,int pixel_unit);
int		VOL_SetImagesInAcquisitionOfDicomData(VOL_DICOMDATA* dicomData,int number);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

#define DICOMIMPORTEXPORT_H
