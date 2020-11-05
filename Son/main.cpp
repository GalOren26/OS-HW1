#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "../Share/ShareFunctions.h"
void CountNumOfFires(char forest[]);

int main(int argc, char* argv[])
{
	CheakArgs(argc);
	char* forest = argv[1];
	CountNumOfFires(forest);
}
