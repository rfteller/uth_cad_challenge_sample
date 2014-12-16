#define _CRT_SECURE_NO_DEPRECATE

#include <cstdio>
#include <vector>


std::vector<std::string>* separate_std_string(std::vector<std::string>* dest, const std::string &src, const std::string &delim);
float** new_matrix(int n_row, int n_col);


float** read_matrix(char* filename, int* n_row, int* n_col)
{
	FILE* fpi = fopen(filename, "r");

	char buf[1000000];
	std::string buffer;
	std::string delim(",");
	std::vector<std::string> strs;

	fgets(buf, 1000000, fpi);
	buffer = buf;
	separate_std_string(&strs, buffer, delim);
	*n_row = atoi(strs[1].c_str());
	strs.clear();

	fgets(buf, 1000000, fpi);
	buffer = buf;
	separate_std_string(&strs, buffer, delim);
	*n_col = atoi(strs[1].c_str());
	strs.clear();

	float** matrix = new_matrix(*n_row, *n_col);
	for(int j=0; j<*n_row; j++) {
		fgets(buf, 1000000, fpi);
		buffer = buf;
		separate_std_string(&strs, buffer, delim);
		for(int i=0; i<*n_col; i++)		matrix[j][i] = (float)atof(strs[i].c_str());
		strs.clear();
	}

	fclose(fpi);

	return matrix;
}


int write_matrix(float** matrix, int n_row, int n_col, char* filename)
{
	FILE* fpo = fopen(filename, "w");
	fprintf(fpo, "n_row,%d,\n", n_row);
	fprintf(fpo, "n_col,%d,\n", n_col);
	for(int j=0; j<n_row; j++) {
		for(int i=0; i<n_col; i++)	fprintf(fpo, "%e,", matrix[j][i]);
		fprintf(fpo, "\n");
	}
	fclose(fpo);
	return 0;
}


int print_matrix(int n_row, int n_col, float** m)
{
	fprintf(stderr, "matrix_size(%d,%d)\n", n_row, n_col);
	for(int j=0; j<n_row; j++) {
		fprintf(stderr, "[row:%d] ", j);
		for(int i=0; i<n_col; i++)	fprintf(stderr, "%e, ", m[j][i]);
		fprintf(stderr, "\n", n_col);
	}
	return 0;
}


