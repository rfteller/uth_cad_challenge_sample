
#ifndef _MAHALANOBIS_DISTANCE__H_


#include "example_set.h"


typedef struct _MAHALANOBIS_DISTANCE_CALCULATION_PARAMETERS_
{
	float** inv_co_var;		// invease of co-var matrix
	float* mean;			// mean of feature vectors
}
MDCPARAM;

typedef struct _MAHALANOBIS_DISTANCE_RATIO_CLASSIFIER_
{
	MDCPARAM** param;	// parameters for calculating mahalanobis distance
	int num_feature;	// num of features
	int num_class;		// num of class = 2
}
MAHALANOBISDISTANCERATIOCLASSIFIER;


MAHALANOBISDISTANCERATIOCLASSIFIER* training_mahalanobis_distance_ratio_classifier(EXAMPLESET* train_set);
MAHALANOBISDISTANCERATIOCLASSIFIER* read_mahalanobis_distance_ratio_classifier(const char* filename);
int write_mahalanobis_distance_ratio_classifier(MAHALANOBISDISTANCERATIOCLASSIFIER* classifier, const char* filename);
int write_mahalanobis_distance_ratio(float* dist_rat, int num_examples, char* filename);

MDCPARAM* new_mdc_param(int num_feature);
void delete_mdc_param(MDCPARAM* param);

MAHALANOBISDISTANCERATIOCLASSIFIER* new_mahalanobis_distance_ratio_classifier(int num_feature);
void delete_mahalanobis_distance_ratio_classifier(MAHALANOBISDISTANCERATIOCLASSIFIER* classifier);

float calculate_mahalanobis_distance(EXAMPLEDATA* data, int num_features, MDCPARAM* mdc);
float* mahalanobis_distance_array(EXAMPLESET* test_set, MAHALANOBISDISTANCERATIOCLASSIFIER* mdr_classifier);

// ratio = [mahalanobis_dist_to_class_0]/[mahalanobis_dist_to_class_1]
float calculate_mahalanobis_distance_ratio(EXAMPLEDATA* data, MAHALANOBISDISTANCERATIOCLASSIFIER* mdr_classifier);
float* mahalanobis_distance_ratio_array(EXAMPLESET* test_set, MAHALANOBISDISTANCERATIOCLASSIFIER* mdr_classifier);


#define _MAHALANOBIS_DISTANCE__H_
#endif
