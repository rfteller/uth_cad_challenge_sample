
#include <stdio.h>
#include <vector>
#include <string>

#include "VOL.h"
#include "VOLbinary.h"
#include "VOLfile.h"
#include "LibCircusCS.h"

#include "..\MachineLearning\example_set.h"

using namespace std;

int check_answer(
	const char* in_path,
	CircusCS_BASICDCMTAGVALUES* basic_tag_values,
	vector<vector<float>>& cand_properties,
	EXAMPLESET* dataset,
	char* log_file_name);


