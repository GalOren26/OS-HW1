#pragma once
#include "stdlib.h"
#include <stdio.h>
#include <Windows.h>
int CreateSon(LPTSTR CommandLine, PROCESS_INFORMATION* ProcessInfoPtr);
int WaitForSingleObjectWrap(DWORD* waitcode, PROCESS_INFORMATION* procinfo);
int SaveStateTofile(DWORD exitcode, char* p_line,int max_size, FILE* p_out_file);
void ConvertMatrixToLine(char** p_forest_matrix, char** p_forest_line, int dim,int max_size);
void PrintMatrix(char** matrix, int dim);
int UpdateMatrix(char** returned_matrix, int size);
void ReadFileToMatrix(FILE* p_forest_file, char*** retuend_matrix, int* dim_ret, int* gen_num_ret);