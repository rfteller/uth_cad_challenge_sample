

#include "..\example_set.h"



EXAMPLEDATA* new_example_data(int num_features)
{
	if(num_features==0)		return NULL;

	EXAMPLEDATA* data = new EXAMPLEDATA;
	data->label = 0;
	data->descriptor = new float [num_features];
	memset(data->descriptor, 0x00, sizeof(float)*num_features);

	return data;
}










