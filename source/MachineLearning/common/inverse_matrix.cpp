

#include <cstdio>
#include <cstring>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define NRANSI
#include "..\nr2_c211\nr.h"

#ifdef __cplusplus
}
#endif /* __cplusplus */


//#define DEBUG_STDERR_PRINT
#ifdef DEBUG_STDERR_PRINT
int print_matrix(int n_row, int n_col, float** m);
#endif


float** new_matrix(int n_row, int n_col);
void delete_matrix(float** mat);


float** inverse_square_matrix(float** mat, int size) 
{
	if(mat==NULL || size==0) {
		return NULL;
	}

	float** inv_mat = new_matrix(size, size);

	switch(size)
	{

	case 1:
		inv_mat[0][0] = 1.0f/mat[0][0];
		break;

	case 2:
		{
			double a11 = (double)mat[0][0], a12 = (double)mat[0][1];
			double a21 = (double)mat[1][0], a22 = (double)mat[1][1];
			double detA = a11 * a22 - a12 * a21;

			if( detA != 0.0 ) {
				inv_mat[0][0] = (float)(a22/detA);		inv_mat[0][1] = (float)(-a12/detA);
				inv_mat[1][0] = (float)(-a21/detA);		inv_mat[1][1] = (float)(a11/detA);
			} else {
				fprintf(stderr, "Error : Determinant of the matrix is zero.\n");
				inv_mat[0][0] = -1.0f;
				return inv_mat;
			}
		}
		break;

	default:

#ifdef DEBUG_STDERR_PRINT
		fprintf(stderr, "set_lu\n");
		print_matrix(size+1, size+1, mat_lu);
#endif
		float** mat_lu = new_matrix(size+1, size+1);
		for(int j=0; j<size; j++) {
			for(int i=0; i<size; i++)	mat_lu[j+1][i+1] = mat[j][i];
		}

#ifdef DEBUG_STDERR_PRINT
		fprintf(stderr, "ludcmp\n");
#endif
		float num_swap;	
		int* idx_swap = new int [size*2];
		memset(idx_swap, 0x00, sizeof(int)*size*2);
		ludcmp(mat_lu, size, idx_swap, &num_swap);

#ifdef DEBUG_STDERR_PRINT
		fprintf(stderr, "lubksb,");
#endif
		float* column = new float [size*2];
		for(int j=0; j<size; j++) {
#ifdef DEBUG_STDERR_PRINT
		fprintf(stderr, "j%d: ", j);
#endif
			memset(column, 0x00, sizeof(float)*size*2);
			column[j+1] = 1.0f;
			lubksb(mat_lu, size, idx_swap, column);
			for(int i=0; i<size; i++) {
				inv_mat[j][i] = column[i+1];
#ifdef DEBUG_STDERR_PRINT
				fprintf(stderr, "%e, ", inv_mat[j][i]);
#endif
			}
#ifdef DEBUG_STDERR_PRINT
		fprintf(stderr, "\n");
#endif
		}

		delete_matrix(mat_lu);
		delete [] idx_swap;
		delete [] column;
#ifdef DEBUG_STDERR_PRINT
		fprintf(stderr, "del,");
#endif
		break;

	} // end of switch


	return inv_mat;
}




