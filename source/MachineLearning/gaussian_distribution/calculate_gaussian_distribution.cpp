

#include "..\gaussian_distribution.h"


GAUSSIAN* calculate_gaussian_distribution(EXAMPLESET* train_set, unsigned char label)
{
	int num_e = num_of_labeled_examples(train_set, label);
	int num_f = train_set->num_features;

	GAUSSIAN* gauss = new_gaussian_distirubtion(num_f);

	EXAMPLEDATA** temp_ary = new EXAMPLEDATA* [num_e];
	int cnt = 0;
	for(int i=0; i<(int)train_set->examples.size(); i++) {
		if(train_set->examples[i]->label==label)	temp_ary[cnt++] = train_set->examples[i];
	}

	for(int j1=0; j1<num_f; j1++) {
		double temp_mean = 0.0;
		for(int i=0; i<num_e; i++) {
			temp_mean += (double)temp_ary[i]->descriptor[j1]/(double)num_e;
		}
		gauss->mean[j1] = (float)temp_mean;
	}

	for(int j1=0; j1<num_f; j1++) {
	for(int j2=0; j2<=j1; j2++) {
		double temp_co_var = 0.0;
		for(int i=0; i<num_e; i++) {
			double sub1 = (double)(temp_ary[i]->descriptor[j1] - gauss->mean[j1]);
			double sub2 = (double)(temp_ary[i]->descriptor[j2] - gauss->mean[j2]);
			temp_co_var += sub1*sub2/(double)(num_e-1);
	//		fprintf(stderr, "\n#%d: [%d]%f,[%d]%f -> %f,%f -> %f", 
	//			i,j1,temp_ary[i]->descriptor[j1],j2,temp_ary[i]->descriptor[j2],sub1,sub2,temp_co_var);
	//		getchar();
		}
		gauss->co_var[j1][j2] = gauss->co_var[j2][j1] = (float)temp_co_var;
	//	fprintf(stderr, "\nco_var[%d][%d]=%f", j1,j2,temp_co_var);
	//	getchar();
	}}

	delete [] temp_ary;

	return gauss;
}


