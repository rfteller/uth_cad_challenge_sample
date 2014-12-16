
#ifndef _GAUSSIAN_DISTRIBUTION__H_


#include "example_set.h"


typedef struct _GAUSSIAN_
{
	int nf;
	float* mean;
	float** co_var;
}
GAUSSIAN;


GAUSSIAN* new_gaussian_distirubtion(int num_features);
void delete_gaussian_distribution(GAUSSIAN* data);
GAUSSIAN* calculate_gaussian_distribution(EXAMPLESET* train_set, unsigned char label);


#define _GAUSSIAN_DISTRIBUTION__H_
#endif
