

#include "..\example_set.h"


EXAMPLESET* new_example_set(int num_examples, int num_features)
{
	if(num_examples==0 || num_features==0)		return NULL;

	EXAMPLESET* dataset = new EXAMPLESET;
	dataset->num_features = num_features;
	dataset->examples.reserve(num_examples);

	for(int i=0; i<num_examples; i++) {
		EXAMPLEDATA* temp_data = new_example_data(num_features);
		dataset->examples.push_back(temp_data);
	}

	return dataset;
}


