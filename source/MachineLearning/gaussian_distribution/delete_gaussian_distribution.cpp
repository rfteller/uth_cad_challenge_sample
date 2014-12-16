
#include "..\gaussian_distribution.h"


void delete_gaussian_distribution(GAUSSIAN* data)
{
	delete [] data->co_var[0];
	delete [] data->co_var;
	delete [] data->mean;
	delete data;
}


