#include <stdio.h>
#include <stdlib.h>
#include <string>
#ifndef __SHARE_FUNCTIONS
#define __SHARE_FUNCTIONS
#include "../Share/ShareFunctions.h"
#endif // !__Hard_coded_data 
void CountNumOfFires(char forest[]);

int main(int argc, char* argv[])
{
	CheakArgs(argc);
	char* forest = argv[1];
	CountNumOfFires(forest);
}
