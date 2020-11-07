#include "SonFunctions.h"
void CountNumOfFires(char forest[])
{
	int x = 0;
	int counter = 0;
	for (int i = 0; i < strlen(forest); i++)
	{
		if (forest[i] == 'F') {
			counter++;
		}
	}
	exit(counter);
}
