#define _CRT_SECURE_NO_DEPRECATE

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "..\mahalanobis_distance.h"


std::vector<std::string>* separate_std_string(
	std::vector<std::string>* dest, const std::string &src, const std::string &delim);


MAHALANOBISDISTANCERATIOCLASSIFIER*  
	read_mahalanobis_distance_ratio_classifier(const char* filename)
{
	FILE* fpi = fopen(filename, "r"); 

	if(fpi==NULL) {
		fprintf(stderr, "error: cannot open file %s\n", filename);
		return 0;
	}

	char buf[1000000];
	std::string buffer;
	std::string delim(",");
	std::vector<std::string> strs;

	// header
	fgets(buf, 1000000, fpi);
	if( strcmp(buf, "mahalanobis_distance_ratio_classifier\n") != 0 ) {
		fclose(fpi);
		return NULL;
	}

	// num_class, num_feature
	int num_class, num_feature;
	for(int i=0; i<2; i++) {
		fgets(buf, 1000000, fpi);
		buffer = buf;
		separate_std_string(&strs, buffer, delim);
		if(i==0)	num_class = atoi(strs[1].c_str());
		else		num_feature = atoi(strs[1].c_str());
		strs.clear();
	}

	MAHALANOBISDISTANCERATIOCLASSIFIER* classifier;
	classifier = new_mahalanobis_distance_ratio_classifier(num_feature);

	for(int c=0; c<classifier->num_class; c++){

		// string: "mean__class_(c)"
		fgets(buf, 1000000, fpi);

		// mean vector
		fgets(buf, 1000000, fpi);		
		buffer = buf;
		separate_std_string(&strs, buffer, delim);
		for(int i=0; i<classifier->num_feature; i++) {
			classifier->param[c]->mean[i] = (float)atof(strs[i].c_str());
		}
		strs.clear();
	
		// string: "inv_co_var__class_(c)"
		fgets(buf, 1000000, fpi);			

		// inverce of co-variance matrix
		for(int j=0; j<classifier->num_feature; j++) {
			fgets(buf, 1000000, fpi);
			buffer = buf;
			separate_std_string(&strs, buffer, delim);
			for(int i=0; i<classifier->num_feature; i++) {
				classifier->param[c]->inv_co_var[j][i] = (float)atof(strs[i].c_str());
			}
			strs.clear();
		}
	}

	fclose(fpi);

	return classifier;
}


int write_mahalanobis_distance_ratio_classifier(
	MAHALANOBISDISTANCERATIOCLASSIFIER* classifier, const char* filename)
{
	FILE* fpo = fopen(filename, "w");

	if(fpo==NULL) {
		fprintf(stderr, "error: cannot open file %s\n", filename);
		return 0;
	}

	fprintf(fpo, "mahalanobis_distance_ratio_classifier\n");
	fprintf(fpo, "num_class,%d\n", classifier->num_class);
	fprintf(fpo, "num_feature,%d\n", classifier->num_feature);

	for(int c=0; c<classifier->num_class; c++) {
		fprintf(fpo, "mean__class_%d\n", c);
		for(int i=0; i<classifier->num_feature; i++) {
			fprintf(fpo, "%le,", classifier->param[c]->mean[i]);
		}
		fprintf(fpo, "\n");
		fprintf(fpo, "inv_co_var__class_%d\n", c);
		for(int j=0; j<classifier->num_feature; j++) {
			for(int i=0; i<classifier->num_feature; i++) {
				fprintf(fpo, "%le,", classifier->param[c]->inv_co_var[j][i]);
			}
			fprintf(fpo, "\n");
		}
	}

	fclose(fpo);

	return 0;
}





