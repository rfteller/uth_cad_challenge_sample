

#include "..\example_set.h"


void delete_example_data(EXAMPLEDATA* data)
{
	delete [] data->descriptor;
	delete data;
}





