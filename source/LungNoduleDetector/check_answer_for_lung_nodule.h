////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Sample codes for UTH CAD Challenge
//
//	      check_answer_for_lung_nodule.cpp : Judge lesion candidates as true positives or not
//                                            (same criterion as ANODE'09 study) 
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

using namespace std;

int check_answer_for_lung_nodule(
	const char* in_path,
	CircusCS_BASICDCMTAGVALUES* basic_tag_values,
	vector<vector<float>>& cand_properties,
	EXAMPLESET* dataset,
	char* log_file_name);


