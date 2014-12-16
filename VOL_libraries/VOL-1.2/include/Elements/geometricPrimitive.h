/************************************************************************************************

	VOLUME-ONE Library (VOL):
	
		geometricPrimitive.h:	geometric primitives such as 2D/3D vectors


	All Rights Reserved (C) 2002-	VOLUME-ONE developpers group

		2002.12.14:		first version for open source
		2004.03.05:		2nd release of VOL-1.1

************************************************************************************************/

#ifndef GEOMETRICPRIMITIVE_H

#define VOL_PI	3.141529


typedef struct VolVector2D		{	float	x, y;	}										VOL_VECTOR2D;
typedef struct VolIntVector2D	{	int		x, y;	}										VOL_INTVECTOR2D;
typedef struct VolVector3D		{	float	x, y, z; }										VOL_VECTOR3D;
typedef struct VolIntVector3D	{	int		x, y, z; }										VOL_INTVECTOR3D;

typedef struct VolSize2D		{	float	width, height; }								VOL_SIZE2D;
typedef struct VolIntSize2D		{	int		width, height;	}								VOL_INTSIZE2D;
typedef struct VolSize3D		{	float	width, height, depth; }							VOL_SIZE3D;
typedef struct VolIntSize3D		{	int		width, height, depth; }							VOL_INTSIZE3D;
typedef struct VolIntSize4D		{	int		width, height, depth, channel; }				VOL_INTSIZE4D;

typedef struct VolLine2D		{	VOL_VECTOR2D* position;		VOL_VECTOR2D* direction;}	VOL_LINE2D;
typedef struct VolBox2D			{	VOL_VECTOR2D* origin;		VOL_SIZE2D*	 size;	}		VOL_BOX2D;
typedef struct VolIntBox2D		{	VOL_INTVECTOR2D* origin;	VOL_INTSIZE2D*	size;	}	VOL_INTBOX2D;

typedef struct VolLine3D		{	VOL_VECTOR3D* position;		VOL_VECTOR3D* direction; }	VOL_LINE3D;
typedef struct VolPlane3D		{	VOL_VECTOR3D* position;		VOL_VECTOR3D* normal;	}	VOL_PLANE3D;
typedef struct VolBox3D			{	VOL_VECTOR3D* origin;		VOL_SIZE3D* size;	}		VOL_BOX3D;
typedef struct VolIntBox3D		{	VOL_INTVECTOR3D* origin;	VOL_INTSIZE3D* size;}		VOL_INTBOX3D;




#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


VOL_VECTOR2D*		VOL_NewVector2D(float x,float y);
void				VOL_DeleteVector2D(VOL_VECTOR2D* vector);
VOL_VECTOR2D*		VOL_DuplicateVector2D(VOL_VECTOR2D* vector);

VOL_INTVECTOR2D*	VOL_NewIntVector2D(int x,int y);
void				VOL_DeleteIntVector2D(VOL_INTVECTOR2D* vector);
VOL_INTVECTOR2D*	VOL_DuplicateIntVector2D(VOL_INTVECTOR2D* vector);

VOL_SIZE2D*			VOL_NewSize2D(float width,float height);
void				VOL_DeleteSize2D(VOL_SIZE2D* vector);
VOL_SIZE2D*			VOL_DuplicateSize2D(VOL_SIZE2D* vector);

VOL_INTSIZE2D*		VOL_NewIntSize2D(int width,int height);
void				VOL_DeleteIntSize2D(VOL_INTSIZE2D* size);
VOL_INTSIZE2D*		VOL_DuplicateIntSize2D(VOL_INTSIZE2D* size);
int					VOL_RasterLengthOfIntSize2D(VOL_INTSIZE2D* size);

VOL_LINE2D*			VOL_NewLine2D(VOL_VECTOR2D* position,VOL_VECTOR2D* direction);
void				VOL_DeleteLine2D(VOL_LINE2D* line);

VOL_BOX2D*			VOL_NewBox2D(VOL_VECTOR2D* origin,VOL_SIZE2D* size);
int					VOL_CheckIfBox1IsWithinBox2_2D(VOL_BOX2D* box1,VOL_BOX2D* box2);
void				VOL_DeleteBox2D(VOL_BOX2D* box);

VOL_INTBOX2D*		VOL_NewIntBox2D(VOL_INTVECTOR2D* origin,VOL_INTSIZE2D* size);
void				VOL_DeleteIntBox2D(VOL_INTBOX2D* box);
int					VOL_CheckIfIntBox1IsWithinIntBox2_2D(VOL_INTBOX2D* box1,VOL_INTBOX2D* box2);




VOL_VECTOR3D*		VOL_NewVector3D(float x,float y,float z);
void				VOL_DeleteVector3D(VOL_VECTOR3D* vector);
VOL_VECTOR3D*		VOL_DuplicateVector3D(VOL_VECTOR3D* vector);

VOL_INTVECTOR3D*	VOL_NewIntVector3D(int x,int y,int z);
VOL_INTVECTOR3D*	VOL_DuplicateIntVector3D(VOL_INTVECTOR3D* vector);
void				VOL_DeleteIntVector3D(VOL_INTVECTOR3D* vector);

VOL_SIZE3D*			VOL_NewSize3D(float width,float height,float depth);
void				VOL_DeleteSize3D(VOL_SIZE3D* vector);
VOL_SIZE3D*			VOL_DuplicateSize3D(VOL_SIZE3D* vector);

VOL_INTSIZE3D*		VOL_NewIntSize3D(int width,int height,int depth);
void				VOL_DeleteIntSize3D(VOL_INTSIZE3D* size);
VOL_INTSIZE3D*		VOL_DuplicateIntSize3D(VOL_INTSIZE3D* size);
VOL_INTSIZE3D*		VOL_GetIntSize3DFromIntSize4D(VOL_INTSIZE4D* size);
int					VOL_RasterLengthOfIntSize3D(VOL_INTSIZE3D* size);
int					VOL_CompareIntSize3D(VOL_INTSIZE3D* is1,VOL_INTSIZE3D* is2);


VOL_LINE3D*			VOL_NewLine3D(VOL_VECTOR3D* origin,VOL_VECTOR3D* direction);
void				VOL_DeleteLine3D(VOL_LINE3D* line);

VOL_PLANE3D*		VOL_NewPlane3D(VOL_VECTOR3D* position,VOL_VECTOR3D* normal);
void				VOL_DeletePlane3D(VOL_PLANE3D* plane);

VOL_BOX3D*			VOL_NewBox3D(VOL_VECTOR3D* origin,VOL_SIZE3D* size);
int					VOL_CheckIfBox1IsWithinBox2_3D(VOL_BOX3D* box1,VOL_BOX3D* box2);
void				VOL_DeleteBox3D(VOL_BOX3D* box);

VOL_INTBOX3D*		VOL_NewIntBox3D(VOL_INTVECTOR3D* origin,VOL_INTSIZE3D* size);
VOL_INTBOX3D*		VOL_DuplicateIntBox3D(VOL_INTBOX3D* intBox3D);
int					VOL_CheckIfIntBox1IsWithinIntBox2_3D(VOL_INTBOX3D* box1,VOL_INTBOX3D* box2);
int					VOL_CheckIfIntVector3DisWithinIntBox3D(VOL_INTVECTOR3D* vector,VOL_INTBOX3D* box);
void				VOL_DeleteIntBox3D(VOL_INTBOX3D* box);


VOL_INTSIZE4D*		VOL_NewIntSize4D(int width,int height,int depth,int channel);
void				VOL_DeleteIntSize4D(VOL_INTSIZE4D* vector);
VOL_INTSIZE4D*		VOL_DuplicateIntSize4D(VOL_INTSIZE4D* vector);
int					VOL_CompareIntSize4D(VOL_INTSIZE4D* is1,VOL_INTSIZE4D* is2);
int					VOL_CompareIntSize3Dof4D(VOL_INTSIZE4D* is1,VOL_INTSIZE4D* is2);



float			VOL_InnerProduct3D(VOL_VECTOR3D* v1, VOL_VECTOR3D* v2);
float			VOL_InnerProduct2D(VOL_VECTOR2D* v1, VOL_VECTOR2D* v2);

void			VOL_OuterProduct3D(VOL_VECTOR3D* v1, VOL_VECTOR3D* v2, VOL_VECTOR3D* v3);

float			VOL_VectorLength3D(VOL_VECTOR3D* vector);
float			VOL_VectorLength2D(VOL_VECTOR2D* vector);

float			VOL_NormalizeVector3D(VOL_VECTOR3D* vector);
float			VOL_NormalizeVector2D(VOL_VECTOR2D* vector);

void			VOL_CalculateAnglesOfVector3D(VOL_VECTOR3D* vector, float* theta,float* phi);
void			VOL_CalculateAngleOfVector2D(VOL_VECTOR2D* vector, float* theta);

float			VOL_RadianToDegree(float angle);
float			VOL_DegreeToRadian(float angle);


VOL_VECTOR3D*	VOL_NewVector3DonLine3D(VOL_LINE3D* line,float parameter);
VOL_VECTOR3D*	VOL_IntersectionOfPlane3DandLine3D(VOL_PLANE3D* plane,VOL_LINE3D* line,float* parameter);


int				VOL_CheckIfIntsize2DIsSame(VOL_INTSIZE2D* size1,VOL_INTSIZE2D* size2);
int				VOL_CheckIfIntsize3DIsSame(VOL_INTSIZE3D* size1,VOL_INTSIZE3D* size2);
int				VOL_CheckIfIntsize4DIsSame(VOL_INTSIZE4D* size1,VOL_INTSIZE4D* size2);


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif

#define GEOMETRICPRIMITIVE_H
