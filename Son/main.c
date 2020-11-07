
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SonFunctions.h"
#include "../Share/ShareFunctions.h"

int main(int argc, char* argv[])
{
	CheakArgs(argc);
	char* forest = argv[1];
	CountNumOfFires(forest);
}
