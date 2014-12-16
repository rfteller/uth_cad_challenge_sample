
#include "..\mahalanobis_distance.h"
#include <cstdio>
#include <cstring>


void delete_mahalanobis_distance_ratio_classifier(MAHALANOBISDISTANCERATIOCLASSIFIER* classifier)
{
	for(int c=0; c<classifier->num_class; c++) {
		delete_mdc_param(classifier->param[c]);
	}
	delete [] classifier->param;
	delete classifier;
}




