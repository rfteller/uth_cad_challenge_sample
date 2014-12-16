
#include "..\mahalanobis_distance.h"
#include <cstdio>
#include <cstring>


float* mahalanobis_distance_array(
	EXAMPLESET* test_set, MAHALANOBISDISTANCERATIOCLASSIFIER* mdr_classifier)
{
	float* dist = new float [(int)test_set->examples.size()];
	for(int i=0; i<(int)test_set->examples.size(); i++) {
		dist[i] = calculate_mahalanobis_distance_ratio(test_set->examples[i], mdr_classifier);
	}
	return dist;
}


