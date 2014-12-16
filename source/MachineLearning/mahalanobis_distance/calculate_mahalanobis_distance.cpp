
#include "..\mahalanobis_distance.h"
#include <cstdio>
#include <cstring>


float** new_matrix(int n_row, int n_col);
float** multiply_matrices(float** mat1, int n_row1, int n_col1, float** mat2, int n_row2, int n_col2);
void delete_matrix(float** mat);
int print_matrix(int n_row, int n_col, float** m);


float calculate_mahalanobis_distance(EXAMPLEDATA* data, int num_features, MDCPARAM* mdc)
{
	float* sub_mean = new float [num_features];
	for (int i=0; i<num_features; i++) {
		sub_mean[i] = data->descriptor[i] - mdc->mean[i];
	}

	float** m1 = new float* [1];
	float** m1t = new float* [num_features];
	m1[0] = sub_mean;
	for (int i=0; i<num_features; i++)	m1t[i] = &(sub_mean[i]);

	float** m2 = multiply_matrices(m1, 1, num_features, mdc->inv_co_var, num_features, num_features);

	float** out = multiply_matrices(m2, 1, num_features, m1t, num_features, 1);

	float md = out[0][0];

	delete [] sub_mean;
	delete [] m1;
	delete [] m1t;
	delete_matrix(m2);
	delete_matrix(out);

	return md;
}

