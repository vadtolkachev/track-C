#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <cstring>
#include <locale>
#include <wchar.h>


int main()
{
	setlocale(LC_CTYPE,"");

	FILE *file = fopen("1.txt", "r");
	if(errno != 0)
	{
		fprintf(stderr, "failed to open file\n");
		exit(EXIT_FAILURE);
	}

	FILE *res = fopen("res.txt", "w");
	if(errno != 0)
	{
		fprintf(stderr, "failed to open res\n");
		exit(EXIT_FAILURE);
	}

	struct stat tmp;
	fstat(fileno(file), &tmp);
	long int size = tmp.st_size;
	
	wchar_t *bigString = (wchar_t *)calloc(size + 1, sizeof(wchar_t));
	if(errno != 0)
	{
		perror("Memory cannot be allocated");
		exit(EXIT_FAILURE);
	}
	
	if(fread(bigString, size, 1, file) != 1)
	{
		printf("reading error\n");	
		exit(EXIT_FAILURE);
	}
	
	//for(int i = 0; i < size; i++)
	//	wprintf(L"%d.%d = %lc\n",i, bigString[i], bigString[i]);

	printf("size = %ld\n", size); 
	
	//for(int i = 0; i < size; i++)
	//	wprintf(L"%lc", bigString[i]);
	//wprintf(L"%s", bigString);

	if(errno != 0)
	{
		fprintf(stderr, "print\n");
		exit(EXIT_FAILURE);		
	}
	/*
	int s = fwrite(bigString, wcslen(bigString), 1, res);
	if((s < 0) || (errno != 0))
	{
		printf("writing error\n");
		exit(EXIT_FAILURE);
	}*/
	

	fclose(file);
	if(errno != 0)
	{
		fprintf(stderr, "file fclose() failed\n");
		exit(EXIT_FAILURE);		
	}

	fclose(res);
	if(errno != 0)
	{
		fprintf(stderr, "res fclose() failed\n");
		exit(EXIT_FAILURE);	
	}

	free(bigString);

	return 0;
}