
#include <cstdio>

float** new_matrix(int n_row, int n_col);

// o_mat = mat1 * mat2
float** multiply_matrices(
	float** mat1, int n_row1, int n_col1, float** mat2, int n_row2, int n_col2)
{
	if(mat1==NULL || mat2==NULL || n_col1!=n_row2)	return NULL;

	float** o_mat = new_matrix(n_row1, n_col2);

	for(int j=0; j<n_row1; j++) {
	for(int i=0; i<n_col2; i++) {
		double tmp = 0.0;
		for(int t=0; t<n_col1; t++)		tmp += (double)mat1[j][t]*(double)mat2[t][i];
		o_mat[j][i] = (float)tmp;
	}}

	return o_mat;
}

