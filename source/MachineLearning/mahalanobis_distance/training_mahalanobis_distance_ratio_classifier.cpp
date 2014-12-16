

#include "..\mahalanobis_distance.h"
#include "..\gaussian_distribution.h"
#include "..\example_set.h"




float** inverse_square_matrix(float** mat, int size);
int write_matrix(float** matrix, int n_row, int n_col, char* filename);
float** read_matrix(char* filename, int* n_row, int* n_col);
void delete_matrix(float** mat);
int print_matrix(int n_row, int n_col, float** m);

#define NUM_CLASS 2

MAHALANOBISDISTANCERATIOCLASSIFIER* 
	training_mahalanobis_distance_ratio_classifier(EXAMPLESET* train_set)
{
	int num_f = train_set->num_features;
	int num_e0 = num_of_labeled_examples(train_set, 0);
	int num_e1 = num_of_labeled_examples(train_set, 1);
	if(num_e0*num_e1==0)	return NULL;

	MAHALANOBISDISTANCERATIOCLASSIFIER* mdrc = new MAHALANOBISDISTANCERATIOCLASSIFIER;
	mdrc->num_class = NUM_CLASS;
	mdrc->num_feature = num_f;
	mdrc->param = new MDCPARAM* [NUM_CLASS];

	for(int c=0; c<NUM_CLASS; c++) {

		mdrc->param[c] = new MDCPARAM;

		GAUSSIAN* tmp_gauss = calculate_gaussian_distribution(train_set, c);
		
		mdrc->param[c]->mean = new float [num_f];
		memcpy(mdrc->param[c]->mean, tmp_gauss->mean, sizeof(float)*num_f);

		mdrc->param[c]->inv_co_var = inverse_square_matrix(tmp_gauss->co_var, num_f);

		delete_gaussian_distribution(tmp_gauss);
	}

	return mdrc;
}


