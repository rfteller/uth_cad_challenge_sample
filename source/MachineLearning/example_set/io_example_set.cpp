#define _CRT_SECURE_NO_DEPRECATE

#include "..\example_set.h"


// common\separate_std_string.cpp
std::vector<std::string>* separate_std_string(
	std::vector<std::string>* dest, const std::string &src, const std::string &delim);


EXAMPLESET* read_example_set(const char* filename)
{
	EXAMPLESET* dataset = new EXAMPLESET;
	dataset->num_features = 0;

	FILE* fpi = fopen(filename, "r");

	if(fpi==NULL) {
		fprintf(stderr,"error: cannot open %s\n", filename);
		return NULL;
	}

	char buf[1000000];
	std::string delim(",");
	std::string buffer;
	std::vector<std::string> strs;
	int count = 0;

	while( fgets(buf, 1000000, fpi)!=NULL ) {
		buffer = buf;
		separate_std_string(&strs, buffer, delim);
		if(!dataset->num_features) {
			dataset->num_features = (int)strs.size()-1;
		}
		if(dataset->num_features+1==(int)strs.size()) {
			EXAMPLEDATA* temp_data = new_example_data(dataset->num_features);
			temp_data->label = (unsigned char)atoi(strs[0].c_str());
			for(int i=0; i<dataset->num_features; i++) {
				temp_data->descriptor[i] = (float)atof(strs[i+1].c_str());
			}
			dataset->examples.push_back(temp_data);
			count++;
		}
		strs.clear();
	}

	fprintf(stderr, "read %d lines\n", (int)dataset->examples.size());
	fclose(fpi);

	return dataset;
}


int write_example_set(const char* filename, EXAMPLESET* dataset)
{
	FILE* fpo = fopen(filename, "w");

	if(fpo==NULL) {
		fprintf(stderr,"error: cannot open file %s\n", filename);
		return 0;
	}

	for(int i=0; i<(int)dataset->examples.size(); i++) {
		fprintf(fpo, "%d", (int)dataset->examples[i]->label);
		for(int j=0; j<dataset->num_features; j++) {
			fprintf(fpo, ",%e", dataset->examples[i]->descriptor[j]);
		}
		fprintf(fpo, "\n");
	}

	fclose(fpo);

	return 0;
}












