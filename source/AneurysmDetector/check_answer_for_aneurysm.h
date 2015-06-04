////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Sample codes for UTH CAD Challenge
//
//	      check_answer_for_aneurysm.cpp : Judge lesion candidates as true positives or not
//
//    [CAUTION] The sample codes are permitted to use only for research purposes.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <vector>
#include <string>

#include "VOL.h"
#include "VOLbinary.h"
#include "VOLfile.h"
#include "LibCircusCS.h"

#include "..\MachineLearning\example_set.h"

#define   DETECTION_THRESHOLD_MM	3.0f

using namespace std;

int check_answer_for_aneurysm(
	const char* in_path,
	CircusCS_BASICDCMTAGVALUES* basic_tag_values,
	vector<vector<float>>& cand_properties,
	EXAMPLESET* dataset,
	char* log_file_name);


