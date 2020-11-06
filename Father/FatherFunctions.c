#include "FatherFunctions.h"
#ifndef __SHARE_FUNCTIONS
#define __SHARE_FUNCTIONS
#include "../Share/ShareFunctions.h"
#endif // !__Hard_coded_data 

int ReadFileToMatrix(FILE* p_forest_file, char***retuend_matrix)
{
	char p_current_line[MAX_LINE_LEN] = { 0 };
	void* p_temp_ptr;
	char** p_forest_matrix = NULL;

	//dimention line and number of genration->atoi func convert string to num 
	int dim = atoi(fgets(p_current_line, MAX_LINE_LEN, p_forest_file));
	int gen_num = atoi(fgets(p_current_line, MAX_LINE_LEN, p_forest_file));
	if (dim <= 0 || gen_num <= 0) {
		printf_s("NOT_VALID_INPUT.\n");
		exit(NOT_VALID_INPUT);
	}
	//allocate matrix 
	p_temp_ptr = calloc(dim, sizeof(char*));
	CheakAlocation(p_temp_ptr);
	p_forest_matrix = (char**)p_temp_ptr;
	// fill matrix 
	char* p_valid_line = fgets(p_current_line, MAX_LINE_LEN, p_forest_file);
	for (int i = 0; NULL != p_valid_line; i++)
	{
		p_temp_ptr = calloc(dim, sizeof(char));
		CheakAlocation(p_temp_ptr);
		p_forest_matrix[i] = (char*)p_temp_ptr;
		//parse the string skip , mul by 2 to skip ,
		for (int j = 0; j < 2 * dim; j += 2)
		{
			p_forest_matrix[i][j / 2] = p_current_line[j];
			printf("%c ", p_forest_matrix[i][j / 2]);
		}
		printf("\n");
		p_valid_line = fgets(p_current_line, MAX_LINE_LEN, p_forest_file);
	}
	*retuend_matrix = p_forest_matrix;
	return dim;
}
