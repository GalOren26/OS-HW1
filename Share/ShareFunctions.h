  
#include <stdio.h>
#include <stdlib.h>
#ifndef __Hard_coded_data 
#define __Hard_coded_data 
#include "HardCodedData.h"
#endif
void CheakArgs(int argc);
void CloseFileWarp(FILE* file);
void OpenFileWarp(FILE** file, const char* str, char* mode);
void CheakAlocation(void* p_arr);