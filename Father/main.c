#include "../Share/ShareFunctions.h"
#include <string.h>
int main(int argc, char* argv[])
{
	CheakArgs(argc);
	FILE* p_forest_file = NULL;
	char p_current_line[MAX_LINE_LEN] = { 0 };
	char** p_forest_matrix = NULL;
	void* p_temp_ptr;
	// Open file
	OpenFileWarp(p_forest_file, argv[1], 'r');

	// ---Read lines  from file---

	//dimention line and number of genration
	int dim =(int) fgets(p_current_line, MAX_LINE_LEN, p_forest_file);
	int gen_num = (int)fgets(p_current_line, MAX_LINE_LEN, p_forest_file);
	if (dim <= 0 || gen_num<= 0){
		printf_s("NOT_VALID_INPUT.\n");
		exit(NOT_VALID_INPUT);
	}
	//allocate matrix 
	p_temp_ptr= calloc(dim, sizeof(char*));
	CheakAlocation(p_temp_ptr);
	p_forest_matrix = (char**)p_temp_ptr;
	// fill matrix 
	fgets(p_current_line, MAX_LINE_LEN, p_forest_file);
	for  (int i=0;NULL != p_current_line;i++)
	{
		p_temp_ptr=calloc(dim, sizeof(char));
		CheakAlocation(p_temp_ptr);
		p_forest_matrix[i] = (char*)p_temp_ptr;
		//parse the string skip ,
		for (int j=0; j+=2; j<dim)
		{
			p_forest_matrix[i][j] = p_current_line[j];
		}
		fgets(p_current_line, MAX_LINE_LEN, p_forest_file);
	}



	// Close file&&free allocation 
	for (int i = 0; i < dim;i++)
	{
		free(p_forest_matrix[i]);
	}
	free(p_forest_matrix);
	CloseFileWarp(p_forest_file);
}