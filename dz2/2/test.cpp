#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


char **alloct()
{
	int size = 4;

	char *bigString = (char *)calloc(size + 1, sizeof(char));
	if(errno != 0)
	{
		perror("Memory cannot be allocated");
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < size; i++)
	{
		bigString[i] = '0'+i+1;
	}
	
	int nStr = 2;	
	
	char **text = (char **)calloc(nStr, sizeof(char *));
	if(errno != 0)
	{
		perror("Memory cannot be allocated");
		exit(EXIT_FAILURE);
	}

	text[0] = bigString;
	for(int i = 1; i < nStr; i++)
	{
		text[i] = &bigString[2*i];
	}

	return text;
}


int main()
{
	char **text = alloct();	
	
	free(text[0]);
	free(text);
	
	return 0;
}
