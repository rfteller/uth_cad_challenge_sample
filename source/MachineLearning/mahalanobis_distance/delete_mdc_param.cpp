
#include "..\mahalanobis_distance.h"
#include <cstdio>
#include <cstring>


void delete_matrix(float** mat);


void delete_mdc_param(MDCPARAM* param)
{
	delete [] param->mean;
	delete_matrix(param->inv_co_var); 
	delete param;
}

