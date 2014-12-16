/************************************************************************************************

	VOLUME-ONE Library (VOL):
	
		matrix.h:	matrix & vector operation


	All Rights Reserved (C) 2002-	VOLUME-ONE developpers group

		2002.12.14:		first version for open source
		2004.03.05:		2nd release of VOL-1.1

************************************************************************************************/

#ifndef MATRIX_H




typedef struct VolVector		{	int n;		float*	data;	}		VOL_VECTOR;
typedef struct VolMatrix		{	int m, n;	float**	data;	}		VOL_MATRIX;


typedef struct VolIntVector		{	int n;		int*	data;	}		VOL_INTVECTOR;
typedef struct VolIntMatrix		{	int m, n;	int**	data;	}		VOL_INTMATRIX;




#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



VOL_VECTOR*			VOL_NewVector(int n);
void				VOL_DeleteVector(VOL_VECTOR* vector);
VOL_MATRIX*			VOL_NewMatrix(int m,int n);
void				VOL_DeleteMatrix(VOL_MATRIX* matrix);



VOL_INTVECTOR*		VOL_NewIntVector(int n);
void				VOL_DeleteIntVector(VOL_INTVECTOR* vector);
VOL_INTMATRIX*		VOL_NewIntMatrix(int m,int n);
void				VOL_DeleteIntMatrix(VOL_INTMATRIX* matrix);


float			VOL_NormalizeVector(VOL_VECTOR* vector);

float			VOL_SumSquareOfMatrix(VOL_MATRIX* matrix);
float			VOL_NormalizeMatrix(VOL_MATRIX* matrix);
VOL_MATRIX*		VOL_NewUnitMatrix(int n);
VOL_MATRIX*		VOL_GetTransposedMatrix(VOL_MATRIX* matrix);
VOL_MATRIX*		VOL_Multiply2Matrices(VOL_MATRIX* matrix1,VOL_MATRIX* matrix2);
VOL_MATRIX*		VOL_Multiply3Matrices(VOL_MATRIX* matrix1,VOL_MATRIX* matrix2,VOL_MATRIX* matrix3);
VOL_VECTOR*		VOL_MultiplyMatrixAndVector(VOL_MATRIX* matrix,VOL_VECTOR* vector);


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif

#define MATRIX_H
