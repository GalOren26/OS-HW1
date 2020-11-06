#ifndef __SHARE_FUNCTIONS
#define __SHARE_FUNCTIONS
#include "../Share/ShareFunctions.h"
#endif // !__Hard_coded_data 
#include <string.h>
#include "stdlib.h"
#include <stdio.h>
#include "FatherFunctions.h"
int main(int argc, char* argv[])
{
	FILE* p_forest_file = NULL;
	char** p_forest_matrix = NULL;
	CheakArgs(argc);
	// Open file
	OpenFileWarp(&p_forest_file, argv[1],"r");
	//read file to p_forest_matrix return dim of the squre matrix.
	int dim=ReadFileToMatrix(p_forest_file,&p_forest_matrix);

	// Close file&&free allocation 
	for (int i = 0; i < dim;i++)
	{
		free(p_forest_matrix[i]);
	}
	free(p_forest_matrix);
	CloseFileWarp(p_forest_file);
}