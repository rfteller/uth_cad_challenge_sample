

#include "..\example_set.h"


int num_of_examples(EXAMPLESET* dataset)
{
	if(dataset==NULL)	return 0;
	return (int)dataset->examples.size();
}











