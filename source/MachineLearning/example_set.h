
#ifndef _EXAMPLE_SET__H_


#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

//////
//
//	--- example set file 仕様 (text/csv file) ---
//
//	1. カンマ区切り
//	2. 1行に1例題
//	3. 各行には，(特徴量数+1) 個のカラム
//	4. 第1カラムは教師ラベル (0~255, unsigned int).
//	5. 第2カラム以降は特徴量
//	6. 特徴量の記述順は統一
//  
// 
//	--- example set file の例 (例題数=n, 特徴量数=m) ---
//	[教師ラベル(1番目の例題)],[第1特徴量(1番目の例題)],[第2特徴量(1番目の例題)], ... ,[第m特徴量(1番目の例題)]
//	[教師ラベル(2番目の例題)],[第1特徴量(2番目の例題)],[第2特徴量(2番目の例題)], ... ,[第m特徴量(2番目の例題)]
//	...
//	[教師ラベル(n番目の例題)],[第1特徴量(n番目の例題)],[第2特徴量(n番目の例題)], ... ,[第m特徴量(n番目の例題)]
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
