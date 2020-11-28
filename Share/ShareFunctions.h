  
#include <stdio.h>
#include <stdlib.h>
#ifndef __Hard_coded_data 
#define __Hard_coded_data 
#include "HardCodedData.h"
#endif

void CheakArgs(int argc);
void CloseFileWrap(FILE* file);
int OpenFileWrap(FILE** file, const char* str, char* mode);
int CheakAlocation(void* p_arr);