#include <stdio.h>


char **readText(FILE *file, int *nStrings)
{
	
}


int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("wrong argv\n");
		exit(EXIT_FAILURE);
	}
	
	FILE *fp = fopen("data.txt","r");
	if (fp == NULL)
	{
		fprintf(stderr, "fopen() failed in file %s at line # %d", __FILE__,__LINE__);
		exit(EXIT_FAILURE);
	}

	return 0;
}
