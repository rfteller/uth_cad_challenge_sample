

#include "..\gaussian_distribution.h"


GAUSSIAN* new_gaussian_distirubtion(int num_features)
{
	GAUSSIAN* data = new GAUSSIAN;
	
	data->nf = num_features;

	data->mean = new float [num_features];
	memset(data->mean, 0x00, sizeof(float)*num_features);

	data->co_var = new float* [num_features];
	data->co_var[0] = new float [num_features*num_features];
	for(int j=1; j<num_features; j++)
	{
		data->co_var[j] = data->co_var[0]+j*num_features;
	}
	memset(data->co_var[0], 0x00, sizeof(float)*num_features*num_features);

	return data;
}



