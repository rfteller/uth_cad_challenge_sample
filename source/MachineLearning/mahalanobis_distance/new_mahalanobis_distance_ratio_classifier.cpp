

#include "..\mahalanobis_distance.h"
#include <cstdio>
#include <cstring>


MAHALANOBISDISTANCERATIOCLASSIFIER* new_mahalanobis_distance_ratio_classifier(int num_feature)
{
	MAHALANOBISDISTANCERATIOCLASSIFIER* classifier = new MAHALANOBISDISTANCERATIOCLASSIFIER;

	classifier->num_class = 2;
	classifier->num_feature = num_feature;
	classifier->param = new MDCPARAM* [classifier->num_class];
	for(int c=0; c<classifier->num_class; c++)
	{
		classifier->param[c] = new_mdc_param(num_feature);
	}

	return classifier;
}



