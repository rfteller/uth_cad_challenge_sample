
#include "..\mahalanobis_distance.h"
#include <cstdio>
#include <cstring>


float calculate_mahalanobis_distance(EXAMPLEDATA* data, int num_features, MDCPARAM* mdc);


float calculate_mahalanobis_distance_ratio(EXAMPLEDATA* data, MAHALANOBISDISTANCERATIOCLASSIFIER* mdr_classifier)
{
	float d0 = calculate_mahalanobis_distance(data, mdr_classifier->num_feature, mdr_classifier->param[0]);
	float d1 = calculate_mahalanobis_distance(data, mdr_classifier->num_feature, mdr_classifier->param[1]);
	return d0/d1;
}