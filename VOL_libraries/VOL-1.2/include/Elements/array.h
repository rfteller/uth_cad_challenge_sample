/************************************************************************************************

	VOLUME-ONE Library (VOL):
	
		array.h:	memory allocation of multi-dimensional(1D-4D) array


	All Rights Reserved (C) 2002-	VOLUME-ONE developpers group

		2002.12.14:		first version for open source
		2004.03.05:		2nd release of VOL-1.1

************************************************************************************************/

#ifndef ARRAY_H




#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void*			VOL_New1DArray(int length, int unit);
void** 			VOL_New2DArray(int width, int height, int unit);
void***			VOL_New3DArray(int width, int height, int depth, int unit);
void****		VOL_New4DArray(int width, int height, int depth, int channel, int unit);


void*			VOL_Get1DArrayOf2DArray(void** data,int unit);
void*			VOL_Get1DArrayOf3DArray(void*** data,int unit);
void*			VOL_Get1DArrayOf4DArray(void**** data,int unit);

void			VOL_Delete1DArray(void* data);
void			VOL_Delete2DArray(void** data,int width,int height,int unit);
void			VOL_Delete3DArray(void*** data,int width,int height,int depth,int unit);
void			VOL_Delete4DArray(void**** data,int width,int height,int depth,int channel,int unit);

void			VOL_SwapBytesOfArray(void* array,int unit,int length);


void*			VOL_GetLocal1DArrayOf2DArray(void** array2D,int unit,int y);
void**			VOL_GetLocal2DArrayOf3DArray(void*** array3D,int unit,int z);
void*			VOL_GetLocal1DArrayOf3DArray(void*** array3D,int unit,int z,int y);
void***			VOL_GetLocal3DArrayOf4DArray(void**** array4D,int unit,int c);
void**			VOL_GetLocal2DArrayOf4DArray(void**** array4D,int unit,int c,int z);
void*			VOL_GetLocal1DArrayOf4DArray(void**** array4D,int unit,int c,int z,int y);


float			VOL_GetValueOf1DArrayAsFloat(void* array1D,int unit,int size,int position);


// nearest neighbour
unsigned char	VOL_GetValueOf1DArrayUINT8(void* array1D,int size,float position);
char			VOL_GetValueOf1DArraySINT8(void* array1D,int size,float position);
unsigned short	VOL_GetValueOf1DArrayUINT16(void* array1D,int size,float position);
short			VOL_GetValueOf1DArraySINT16(void* array1D,int size,float position);
unsigned int	VOL_GetValueOf1DArrayUINT32(void* array1D,int size,float position);
int				VOL_GetValueOf1DArraySINT32(void* array1D,int size,float position);
float			VOL_GetValueOf1DArrayFLOAT32(void* array1D,int size,float position);
double			VOL_GetValueOf1DArrayFLOAT64(void* array1D,int size,float position);

unsigned char	VOL_GetValueOf2DArrayUINT8(void** array2D,int w,int h,float x,float y);
char			VOL_GetValueOf2DArraySINT8(void** array2D,int w,int h,float x,float y);
unsigned short	VOL_GetValueOf2DArrayUINT16(void** array2D,int w,int h,float x,float y);
short			VOL_GetValueOf2DArraySINT16(void** array2D,int w,int h,float x,float y);
unsigned int	VOL_GetValueOf2DArrayUINT32(void** array2D,int w,int h,float x,float y);
int				VOL_GetValueOf2DArraySINT32(void** array2D,int w,int h,float x,float y);
float			VOL_GetValueOf2DArrayFLOAT32(void** array2D,int w,int h,float x,float y);
double			VOL_GetValueOf2DArrayFLOAT64(void** array2D,int w,int h,float x,float y);

unsigned char	VOL_GetValueOf3DArrayUINT8(void*** array3D,int w,int h,int d,float x,float y,float z);
char			VOL_GetValueOf3DArraySINT8(void*** array3D,int w,int h,int d,float x,float y,float z);
unsigned short	VOL_GetValueOf3DArrayUINT16(void*** array3D,int w,int h,int d,float x,float y,float z);
short			VOL_GetValueOf3DArraySINT16(void*** array3D,int w,int h,int d,float x,float y,float z);
unsigned int	VOL_GetValueOf3DArrayUINT32(void*** array3D,int w,int h,int d,float x,float y,float z);
int				VOL_GetValueOf3DArraySINT32(void*** array3D,int w,int h,int d,float x,float y,float z);
float			VOL_GetValueOf3DArrayFLOAT32(void*** array3D,int w,int h,int d,float x,float y,float z);
double			VOL_GetValueOf3DArrayFLOAT64(void*** array3D,int w,int h,int d,float x,float y,float z);

// interpolated
unsigned char	VOL_GetValueOf1DArrayUINT8i(void* array1D,int size,float position);
char			VOL_GetValueOf1DArraySINT8i(void* array1D,int size,float position);
unsigned short	VOL_GetValueOf1DArrayUINT16i(void* array1D,int size,float position);
short			VOL_GetValueOf1DArraySINT16i(void* array1D,int size,float position);
unsigned int	VOL_GetValueOf1DArrayUINT32i(void* array1D,int size,float position);
int				VOL_GetValueOf1DArraySINT32i(void* array1D,int size,float position);
float			VOL_GetValueOf1DArrayFLOAT32i(void* array1D,int size,float position);
double			VOL_GetValueOf1DArrayFLOAT64i(void* array1D,int size,float position);

unsigned char	VOL_GetValueOf2DArrayUINT8i(void** array2D,int w,int h,float x,float y);
char			VOL_GetValueOf2DArraySINT8i(void** array2D,int w,int h,float x,float y);
unsigned short	VOL_GetValueOf2DArrayUINT16i(void** array2D,int w,int h,float x,float y);
short			VOL_GetValueOf2DArraySINT16i(void** array2D,int w,int h,float x,float y);
unsigned int	VOL_GetValueOf2DArrayUINT32i(void** array2D,int w,int h,float x,float y);
int				VOL_GetValueOf2DArraySINT32i(void** array2D,int w,int h,float x,float y);
float			VOL_GetValueOf2DArrayFLOAT32i(void** array2D,int w,int h,float x,float y);
double			VOL_GetValueOf2DArrayFLOAT64i(void** array2D,int w,int h,float x,float y);

unsigned char	VOL_GetValueOf3DArrayUINT8i(void*** array3D,int w,int h,int d,float x,float y,float z);
char			VOL_GetValueOf3DArraySINT8i(void*** array3D,int w,int h,int d,float x,float y,float z);
unsigned short	VOL_GetValueOf3DArrayUINT16i(void*** array3D,int w,int h,int d,float x,float y,float z);
short			VOL_GetValueOf3DArraySINT16i(void*** array3D,int w,int h,int d,float x,float y,float z);
unsigned int	VOL_GetValueOf3DArrayUINT32i(void*** array3D,int w,int h,int d,float x,float y,float z);
int				VOL_GetValueOf3DArraySINT32i(void*** array3D,int w,int h,int d,float x,float y,float z);
float			VOL_GetValueOf3DArrayFLOAT32i(void*** array3D,int w,int h,int d,float x,float y,float z);
double			VOL_GetValueOf3DArrayFLOAT64i(void*** array3D,int w,int h,int d,float x,float y,float z);


///

// nearest neighbour without range check
unsigned char	VOL_GetValueOf1DArrayUINT8woRC(void* array1D,int size,float position);
char			VOL_GetValueOf1DArraySINT8woRC(void* array1D,int size,float position);
unsigned short	VOL_GetValueOf1DArrayUINT16woRC(void* array1D,int size,float position);
short			VOL_GetValueOf1DArraySINT16woRC(void* array1D,int size,float position);
unsigned int	VOL_GetValueOf1DArrayUINT32woRC(void* array1D,int size,float position);
int				VOL_GetValueOf1DArraySINT32woRC(void* array1D,int size,float position);
float			VOL_GetValueOf1DArrayFLOAT32woRC(void* array1D,int size,float position);
double			VOL_GetValueOf1DArrayFLOAT64woRC(void* array1D,int size,float position);

unsigned char	VOL_GetValueOf2DArrayUINT8woRC(void** array2D,int w,int h,float x,float y);
char			VOL_GetValueOf2DArraySINT8woRC(void** array2D,int w,int h,float x,float y);
unsigned short	VOL_GetValueOf2DArrayUINT16woRC(void** array2D,int w,int h,float x,float y);
short			VOL_GetValueOf2DArraySINT16woRC(void** array2D,int w,int h,float x,float y);
unsigned int	VOL_GetValueOf2DArrayUINT32woRC(void** array2D,int w,int h,float x,float y);
int				VOL_GetValueOf2DArraySINT32woRC(void** array2D,int w,int h,float x,float y);
float			VOL_GetValueOf2DArrayFLOAT32woRC(void** array2D,int w,int h,float x,float y);
double			VOL_GetValueOf2DArrayFLOAT64woRC(void** array2D,int w,int h,float x,float y);

unsigned char	VOL_GetValueOf3DArrayUINT8woRC(void*** array3D,int w,int h,int d,float x,float y,float z);
char			VOL_GetValueOf3DArraySINT8woRC(void*** array3D,int w,int h,int d,float x,float y,float z);
unsigned short	VOL_GetValueOf3DArrayUINT16woRC(void*** array3D,int w,int h,int d,float x,float y,float z);
short			VOL_GetValueOf3DArraySINT16woRC(void*** array3D,int w,int h,int d,float x,float y,float z);
unsigned int	VOL_GetValueOf3DArrayUINT32woRC(void*** array3D,int w,int h,int d,float x,float y,float z);
int				VOL_GetValueOf3DArraySINT32woRC(void*** array3D,int w,int h,int d,float x,float y,float z);
float			VOL_GetValueOf3DArrayFLOAT32woRC(void*** array3D,int w,int h,int d,float x,float y,float z);
double			VOL_GetValueOf3DArrayFLOAT64woRC(void*** array3D,int w,int h,int d,float x,float y,float z);

// interpolated without range check
unsigned char	VOL_GetValueOf1DArrayUINT8iwoRC(void* array1D,int size,float position);
char			VOL_GetValueOf1DArraySINT8iwoRC(void* array1D,int size,float position);
unsigned short	VOL_GetValueOf1DArrayUINT16iwoRC(void* array1D,int size,float position);
short			VOL_GetValueOf1DArraySINT16iwoRC(void* array1D,int size,float position);
unsigned int	VOL_GetValueOf1DArrayUINT32iwoRC(void* array1D,int size,float position);
int				VOL_GetValueOf1DArraySINT32iwoRC(void* array1D,int size,float position);
float			VOL_GetValueOf1DArrayFLOAT32iwoRC(void* array1D,int size,float position);
double			VOL_GetValueOf1DArrayFLOAT64iwoRC(void* array1D,int size,float position);

unsigned char	VOL_GetValueOf2DArrayUINT8iwoRC(void** array2D,int w,int h,float x,float y);
char			VOL_GetValueOf2DArraySINT8iwoRC(void** array2D,int w,int h,float x,float y);
unsigned short	VOL_GetValueOf2DArrayUINT16iwoRC(void** array2D,int w,int h,float x,float y);
short			VOL_GetValueOf2DArraySINT16iwoRC(void** array2D,int w,int h,float x,float y);
unsigned int	VOL_GetValueOf2DArrayUINT32iwoRC(void** array2D,int w,int h,float x,float y);
int				VOL_GetValueOf2DArraySINT32iwoRC(void** array2D,int w,int h,float x,float y);
float			VOL_GetValueOf2DArrayFLOAT32iwoRC(void** array2D,int w,int h,float x,float y);
double			VOL_GetValueOf2DArrayFLOAT64iwoRC(void** array2D,int w,int h,float x,float y);

unsigned char	VOL_GetValueOf3DArrayUINT8iwoRC(void*** array3D,int w,int h,int d,float x,float y,float z);
char			VOL_GetValueOf3DArraySINT8iwoRC(void*** array3D,int w,int h,int d,float x,float y,float z);
unsigned short	VOL_GetValueOf3DArrayUINT16iwoRC(void*** array3D,int w,int h,int d,float x,float y,float z);
short			VOL_GetValueOf3DArraySINT16iwoRC(void*** array3D,int w,int h,int d,float x,float y,float z);
unsigned int	VOL_GetValueOf3DArrayUINT32iwoRC(void*** array3D,int w,int h,int d,float x,float y,float z);
int				VOL_GetValueOf3DArraySINT32iwoRC(void*** array3D,int w,int h,int d,float x,float y,float z);
float			VOL_GetValueOf3DArrayFLOAT32iwoRC(void*** array3D,int w,int h,int d,float x,float y,float z);
double			VOL_GetValueOf3DArrayFLOAT64iwoRC(void*** array3D,int w,int h,int d,float x,float y,float z);


// interpolated for RGBA color

unsigned int	VOL_GetValueOf1DArrayUINT32RGBAi(void* array1D,int size,float position);
unsigned int	VOL_GetValueOf2DArrayUINT32RGBAi(void** array2D,int w,int h,float x,float y);
unsigned int	VOL_GetValueOf3DArrayUINT32RGBAi(void*** array3D,int w,int h,int d,float x,float y,float z);

unsigned int	VOL_GetValueOf1DArrayUINT32RGBAiwoRC(void* array1D,int size,float position);
unsigned int	VOL_GetValueOf2DArrayUINT32RGBAiwoRC(void** array2D,int w,int h,float x,float y);
unsigned int	VOL_GetValueOf3DArrayUINT32RGBAiwoRC(void*** array3D,int w,int h,int d,float x,float y,float z);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

#define ARRAY_H
