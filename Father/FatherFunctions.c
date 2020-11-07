#include "FatherFunctions.h"
#ifndef __SHARE_FUNCTIONS
#define __SHARE_FUNCTIONS
#include "../Share/ShareFunctions.h"
#endif // !__Hard_coded_data 

void  ReadFileToMatrix(FILE* p_forest_file, char***retuend_matrix,int *dim_ret , int * gen_num_ret)
{
	char p_current_line[MAX_LINE_LEN] = { 0 };
	char** p_forest_matrix = NULL;

	//dimention line and number of genration->atoi func convert string to num 
	int dim = atoi(fgets(p_current_line, MAX_LINE_LEN, p_forest_file));
	int gen_num = atoi(fgets(p_current_line, MAX_LINE_LEN, p_forest_file));
	if (dim <= 0 || gen_num <= 0) {
		printf_s("NOT_VALID_INPUT.\n");
		exit(NOT_VALID_INPUT);
	}
	//allocate matrix 
	p_forest_matrix = (char**)calloc(dim, sizeof(char*));
	CheakAlocation((void*)p_forest_matrix);
	// fill matrix 
	fgets(p_current_line, MAX_LINE_LEN, p_forest_file);
	for (int i = 0; i<dim; i++)
	{
		p_forest_matrix[i] = (char* )calloc(dim+1, sizeof(char));
		CheakAlocation((void*)p_forest_matrix[i]);
		//parse the string skip , mul by 2 to skip ,
		for (int j = 0; j < 2 * dim; j += 2)
		{
			p_forest_matrix[i][j / 2] = p_current_line[j];
		//	printf("%c ", p_forest_matrix[i][j / 2]);
		}
		//printf("\n");
		fgets(p_current_line, MAX_LINE_LEN, p_forest_file);
	}
	*retuend_matrix = p_forest_matrix;
	*dim_ret = dim;
	*gen_num_ret = gen_num;
}

void CreateSon(LPTSTR CommandLine, PROCESS_INFORMATION* ProcessInfoPtr)
{
	BOOL	retVal;
	STARTUPINFO	startinfo = { sizeof(STARTUPINFO), NULL, 0 }; /* <ISP> here we */
															  /* initialize a "Neutral" STARTUPINFO variable. Supplying this to */
															  /* CreateProcess() means we have no special interest in this parameter. */
															  /* This is equivalent to what we are doing by supplying NULL to most other */
															  /* parameters of CreateProcess(). */

	retVal= CreateProcess(
		NULL, /*  No module name (use command line). */
		CommandLine,			/*  Command line. */
		NULL,					/*  Process handle not inheritable. */
		NULL,					/*  Thread handle not inheritable. */
		FALSE,					/*  Set handle inheritance to FALSE. */
		NORMAL_PRIORITY_CLASS,	/*  creation/priority flags. */
		NULL,					/*  Use parent's environment block. */
		NULL,					/*  Use parent's starting directory. */
		&startinfo,				/*  Pointer to STARTUPINFO structure. */
		ProcessInfoPtr			/*  Pointer to PROCESS_INFORMATION structure. */
	);
	if (retVal == 0)
	{
		printf("Process Creation Failed!\n");
		exit(FAILED_CREATE_PROCESS);
	}
}


void WaitForSingleObjectWrap(DWORD* waitcode, PROCESS_INFORMATION* procinfo)
{
	*waitcode = WaitForSingleObject(
		procinfo->hProcess,
		TIMEOUT_IN_MILLISECONDS); /* Waiting 5 secs for the process to end */


	if (*waitcode != WAIT_OBJECT_0) /* Process is still alive */
	{
		printf("Process was not terminated before timeout!\n"
			"Terminating brutally!\n");
		TerminateProcess(
			procinfo->hProcess,
			BRUTAL_TERMINATION_CODE); /* Terminating process with an exit code of 55h */
		Sleep(10); /* Waiting a few milliseconds for the process to terminate,
					note the above command may also fail, so another WaitForSingleObject is required.
					We skip this for brevity */
		exit(SON_TERMINATING_BRUTALLY);
	}
}

void SaveStateTofile(DWORD exitcode, char* p_line,int max_size, FILE* p_out_file)
{
	if (p_out_file == NULL)
	{
		printf("output filw is empty .\n");
		exit(FAILAD_TO_OPEN_FILE);
	}
	sprintf_s(p_line, max_size, "%s - %d\n", p_line, exitcode);
	int ret_val=fputs(p_line, p_out_file);
	if (ret_val > 0)
	{
		printf("Failed to write to file.\n");
		exit(FAILED_WRITE_TO_FILE);
	}
}

void ConvertMatrixToLine(char** p_forest_matrix, char** p_forest_line,int dim,int max_size )
{

	*p_forest_line = (char*)calloc(max_size, sizeof(char));
	CheakAlocation((void*)p_forest_line);
	for (int i = 0;i < dim; i++)
	{
		memcpy(*p_forest_line + i * dim, p_forest_matrix[i], dim);
	}
}
void PrintMatrix(char** matrix,int dim)
{
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			printf("%c ",matrix[i][j]);
		}
		printf("\n");
	}

}

void UpdateMatrix(char** returned_matrix, int dim)
{
	int  count = 0;
	char** p_temp_matrix = NULL;
	p_temp_matrix = (char**)malloc(dim * sizeof(char*));
	CheakAlocation((void*)p_temp_matrix);
	for (int i = 0; i < dim;i++)
	{
		p_temp_matrix[i] = (char*)malloc(dim * sizeof(char));
		CheakAlocation((void*)p_temp_matrix);
	}
	//running over the input matrix and updating the temp matrix:
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			if (returned_matrix[i][j] == 'F') // condition #3
			{
				p_temp_matrix[i][j] = 'G';
				continue;
			}
			//condition #1 :update all Treas to F

			if (returned_matrix[i][j] == 'T')
			{
				if (i > 0) {
					if (returned_matrix[i - 1][j] == 'F') {
						p_temp_matrix[i][j] = 'F';
						continue;
					}
				}
				if (i < dim - 1) {
					if (returned_matrix[i + 1][j] == 'F')
					{
						p_temp_matrix[i][j] = 'F';
						continue;
					}
				}
				if (j > 0) {
					if (returned_matrix[i][j - 1] == 'F')
					{
						p_temp_matrix[i][j] = 'F';
						continue;
					}
				}
				if (j < dim - 1) {
					if (returned_matrix[i][j + 1] == 'F')
					{
						p_temp_matrix[i][j] = 'F';
						continue;
					}
				}
				p_temp_matrix[i][j] = 'T';
			}
				if (returned_matrix[i][j] == 'G') //condition #2
				{
					count = 0;
					if (i > 0) {
						if (returned_matrix[i - 1][j] == 'T') { count++; }
					}
					if (i < dim - 1) {
						if (returned_matrix[i + 1][j] == 'T') { count++; }
					}
					if (j > 0) {
						if (returned_matrix[i][j - 1] == 'T') { count++; }
					}
					if (j < dim - 1) {
						if (returned_matrix[i][j + 1] == 'T') { count++; }
					}
					if (i > 0 && j > 0) {
						if (returned_matrix[i - 1][j - 1] == 'T') { count++; }
					}
					if (i > 0 && j < dim - 1) {
						if (returned_matrix[i - 1][j + 1] == 'T') { count++; }
					}
					if (i < dim - 1 && j>0) {
						if (returned_matrix[i + 1][j - 1] == 'T') { count++; }
					}
					if (i < dim - 1 && j < dim - 1) {
						if (returned_matrix[i + 1][j + 1] == 'T') { count++; }
					}

					if (count >= 2) { p_temp_matrix[i][j] = 'T'; }
					if (count < 2) { p_temp_matrix[i][j] = 'G'; }
				}
			}
		}
		for (int i = 0; i < dim; i++)
		{
			for (int j = 0; j < dim; j++)
			{
				returned_matrix[i][j] = p_temp_matrix[i][j];
			}
		}
		//Free the buffer:
		for (int i = 0; i < dim; i++) {
			free(p_temp_matrix[i]);
		}
		free(p_temp_matrix);
}
