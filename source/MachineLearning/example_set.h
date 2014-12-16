
#ifndef _EXAMPLE_SET__H_


#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

//////
//
//	--- example set file �d�l (text/csv file) ---
//
//	1. �J���}��؂�
//	2. 1�s��1���
//	3. �e�s�ɂ́C(�����ʐ�+1) �̃J����
//	4. ��1�J�����͋��t���x�� (0~255, unsigned int).
//	5. ��2�J�����ȍ~�͓�����
//	6. �����ʂ̋L�q���͓���
//  
// 
//	--- example set file �̗� (��萔=n, �����ʐ�=m) ---
//	[���t���x��(1�Ԗڂ̗��)],[��1������(1�Ԗڂ̗��)],[��2������(1�Ԗڂ̗��)], ... ,[��m������(1�Ԗڂ̗��)]
//	[���t���x��(2�Ԗڂ̗��)],[��1������(2�Ԗڂ̗��)],[��2������(2�Ԗڂ̗��)], ... ,[��m������(2�Ԗڂ̗��)]
//	...
//	[���t���x��(n�Ԗڂ̗��)],[��1������(n�Ԗڂ̗��)],[��2������(n�Ԗڂ̗��)], ... ,[��m������(n�Ԗڂ̗��)]
//  (EOF)
//
/////

typedef struct _EXAMPLE_DATA_
{
	float* descriptor;		// feature descriptor
	unsigned char label;	// teacher label (used for training)
}
EXAMPLEDATA;

typedef struct _EXAMPLE_SET_
{
	std::vector<EXAMPLEDATA*> examples;		// examples
	int num_features;						// number of features
}
EXAMPLESET;


EXAMPLEDATA* new_example_data(int num_features);
void delete_example_data(EXAMPLEDATA* data);

EXAMPLESET* read_example_set(const char* filename);
int write_example_set(const char* filename, EXAMPLESET* dataset);

EXAMPLESET* new_example_set(int num_examples, int num_features);
void delete_example_set(EXAMPLESET* dataset);

int num_of_examples(EXAMPLESET* dataset);
int num_of_labeled_examples(EXAMPLESET* dataset, unsigned char label);


#define _EXAMPLE_SET__H_
#endif
