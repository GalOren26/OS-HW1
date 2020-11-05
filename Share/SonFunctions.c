void CountNumOfFires(char forest[])
{
	int counter = 0;
	for (int i = 0; i < strlen(forest); i++)
	{
		if (forest[i] == 'F') {
			counter++;
		}
	}
	exit(counter);
}
