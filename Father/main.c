
#ifndef __SHARE_FUNCTIONS
#define __SHARE_FUNCTIONS
#define _CRTDBG_MAP_ALLOC
#include "../Share/ShareFunctions.h"
#endif // !__Hard_coded_data 
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
//#include <vld.h> -memory leak cheaker
#include "FatherFunctions.h"
#include <windows.h>


/// <summary>
/// auters: gal oren ,rami ayoub
/// </summary>
/// <param name="argv">need to get the string that consist the input file name. </param>
/// <returns>return 0 if success </returns>
int main(int argc, char* argv[])
	{

	CheakArgs(argc);
	FILE* p_input_file = NULL;
	FILE* p_out_file = NULL;
	char* NameOfFile = "output.txt";
	char** p_forest_matrix = NULL;
	char* p_forest_line = NULL;
	int dim = 0;
	int gen_num = 0; 
	// process data
	PROCESS_INFORMATION procinfo;
	DWORD				waitcode;
	DWORD				exitcode;


	// Open file
	OpenFileWrap(&p_input_file, argv[1],"r");
	//read file to p_forest_matrix return dim of the squre matrix.
	ReadFileToMatrix(p_input_file,&p_forest_matrix,& dim,&gen_num);
	int max_size = dim * dim + LEN_OF_SPACE_AND_EXIT_CODE;
	int len_of_command = dim * dim + LEN_OF_COOMAND;
	//open output file 
	OpenFileWrap(&p_out_file, NameOfFile, "w");
	//run the son -> save to file -> update matrix 
	for (int i = 0; i <gen_num ; i++)
	{
		//convert matrix to line to pass the son as command and save to output file 
		ConvertMatrixToLine(p_forest_matrix, &p_forest_line, dim, max_size);
		char* command = (char*)calloc(len_of_command, sizeof(char));
		CheakAlocation((void*)command);
		sprintf_s(command,len_of_command,"%s %s", "son.exe", p_forest_line);
		PrintMatrix(p_forest_matrix,dim);
		//create son and cheak for success 
		CreateSon(command, &procinfo);
		// wait for signle object for TIMEOUT_IN_MILLISECONDS and handle it acording the waitcode 
		WaitForSingleObjectWrap(&waitcode, &procinfo);
		GetExitCodeProcess(procinfo.hProcess, &exitcode);
		printf("The exit code for the process is 0x%x\n\n", exitcode);
		SaveStateTofile(exitcode, p_forest_line, max_size, p_out_file);
		UpdateMatrix(p_forest_matrix, dim);
		//FREE ALLOCATION AND HANDLERS 
		CloseHandle(procinfo.hProcess); /* Closing the handle to the process */
		CloseHandle(procinfo.hThread); /* Closing the handle to the main thread of the process */
		free(p_forest_line);
		free(command);
		}
	// Close file&&free allocation 
	for (int i = 0; i < dim ;i++)
	{
		free(p_forest_matrix[i]);
	}
	free(p_forest_matrix);
	CloseFileWrap(p_input_file);
	CloseFileWrap(p_out_file);
	return(0);
}

