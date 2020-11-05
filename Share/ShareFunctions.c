#include "ShareFunctions.h"

void CheakArgs(int argc)
{
	if (argc < 2)
	{
		printf("ERROR: Not enough input arguments");
		exit(ERR_CODE_NOT_ENOUGH_ARGUMENTS);
	}
	if (argc > 2)
	{
		printf("ERROR: Too many input arguments");
		exit(ERR_CODE_TOO_MANY_ARGUMENTS);
	}
}
	void CloseFileWarp(FILE * file)
	{
		errno_t file_status = fclose(file);
		if (file_status)
		{
			printf("Failed to close file.\n");
			exit(FAILAD_TO_CLOSE_FILE);
		}
	}

	void OpenFileWarp(FILE* file,char*str,char mode)
	{

			int file_status = (int)fopen_s(file, str, mode);
			if (0 != file_status)
			{
				printf_s("Failed to open file.\n");
				exit(FAILAD_TO_OPEN_FILE);
			}
	}

	void CheakAlocation(void* p_arr)
	{
		if (p_arr == NULL) {
			printf_s("MEMORY_ALLOCATION_FAILURE.\n");
			exit(MEMORY_ALLOCATION_FAILURE);
		}
	}
