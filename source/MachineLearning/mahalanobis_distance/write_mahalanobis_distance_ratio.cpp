#define _CRT_SECURE_NO_DEPRECATE

#include <cstdio>
#include <cstdlib>

int write_mahalanobis_distance_ratio(float* dist_rat, int num_examples, char* filename)
{
	FILE* fpo = fopen(filename, "w");
	for(int i=0; i<num_examples; i++) {
		fprintf(fpo, "%le\n", dist_rat[i]);
	}
	fclose(fpo);
	return 0;
}

