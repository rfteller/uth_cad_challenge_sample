

#include "..\example_set.h"


void delete_example_set(EXAMPLESET* dataset)
{
	if(dataset==NULL)		return;

	for(int i=0; i<(int)dataset->examples.size(); i++)
	{
		delete_example_data(dataset->examples[i]);
	}

	dataset->examples.clear();

	delete dataset;
}










