

#include "..\mahalanobis_distance.h"
#include <cstdio>
#include <cstring>


float** new_matrix(int n_row, int n_col);


MDCPARAM* new_mdc_param(int num_feature)
{
	MDCPARAM* param = new MDCPARAM;
	param->mean = new float [num_feature];
	memset(param->mean, 0x00, sizeof(float)*num_feature);
	param->inv_co_var = new_matrix(num_feature, num_feature);
	return param;
}

