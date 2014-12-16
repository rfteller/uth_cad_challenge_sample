

#include "..\example_set.h"


int num_of_labeled_examples(EXAMPLESET* dataset, unsigned char label)
{
	if(dataset==NULL)	return 0;

	int count = 0;
	for(int i=0; i<(int)dataset->examples.size(); i++) {
		if(dataset->examples[i]->label==label)	count++;
	}

	return count;
}






