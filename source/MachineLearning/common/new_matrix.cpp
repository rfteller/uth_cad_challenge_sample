
#include <cstring>


float** new_matrix(int n_row, int n_col)
{
	float** mat = new float* [n_row];
	mat[0] = new float [n_row*n_col];
	for(int i=1; i<n_row; i++)	mat[i] = mat[0]+n_col*i;
	memset(mat[0], 0x00, sizeof(float)*n_row*n_col);
	return mat;
}

