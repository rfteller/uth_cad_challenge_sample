
#include "..\mahalanobis_distance.h"
#include <cstdio>
#include <cstring>


// output_ratio = [mahalanobis_dist_to_class_0]/[mahalanobis_dist_to_class_1]

float* mahalanobis_distance_ratio_array(EXAMPLESET* test_set, MAHALANOBISDISTANCERATIOCLASSIFIER* mdr_classifier)
{
	float* dist_ratio = new float [(int)test_set->examples.size()];
	for(int i=0; i<(int)test_set->examples.size(); i++) {
		dist_ratio[i] = calculate_mahalanobis_distance_ratio(test_set->examples[i], mdr_classifier);
	}
	return dist_ratio;
}


