#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <cstring>


void exitErr(const char *s)
{
	printf("error: %s\n", s);
	exit(EXIT_FAILURE);
}


bool isRusLetter(char a, char b)
{
	if((b > -65) || ((a != -47) && (a != -48)))
	{
		//printf("2");
		return false;
	}
	return true; 
}


int getRusNumb(char a1, char a2)
{
	if(!isRusLetter(a1, a2))
		exitErr("getRusNumb");

	int n = 0;
	if(a1 == -47)
		n = 64;

	n += a2 + 113;

	if(n > 32)
		n -= 32;

	if(n > 6)
		n++;
	
	if((n == 35) || (n == -14))
		n = 7;

	return n;
}


int main()
{
	FILE *file = fopen("1.txt", "r");
	if(errno != 0)
		exitErr("failed to open file");


	FILE *res = fopen("res.txt", "w");
	if(errno != 0)
		exitErr("failed to open res");

	struct stat tmp;
	fstat(fileno(file), &tmp);
	long int size = tmp.st_size;
	
	char *bigString = (char *)calloc(size + 1, sizeof(char));
	if(errno != 0)
		exitErr("Memory cannot be allocated");
	
	if(fread(bigString, size, 1, file) != 1)
		exitErr("reading error");	
	
	//for(int i = 0; i < size; i++)
	//	wprintf(L"%d.%d = %lc\n",i, bigString[i], bigString[i]);

	//printf("size = %ld\n", size); 
	//bigString[0] = -48;
	//bigString[1] = -80;
	//for(int i = 0; i < size; i++)
	//	printf("%c", bigString[i]);
	for(int i = 0; i < size; i++)
	{	
		if((i % 3) == 0)
			printf("%d.", ((int)i/3) + 1);
		
		printf("%c = %d; ", bigString[i], bigString[i]);
		printf("let = %d; ", isRusLetter(bigString[i], bigString[i+1]));
		if(isRusLetter(bigString[i], bigString[i+1]))
			printf("n = %d\n", getRusNumb(bigString[i], bigString[i+1]));
	}
	
	//printf("%s", bigString);
	printf("\nsize = %ld\n", size);

	if(errno != 0)
		exitErr("print");

	/*
	int s = fwrite(bigString, wcslen(bigString), 1, res);
	if((s < 0) || (errno != 0))
	{
		printf("writing error\n");
		exit(EXIT_FAILURE);
	}*/
	

	fclose(file);
	if(errno != 0)
		exitErr("file close");

	fclose(res);
	if(errno != 0)
		exitErr("file res");

	free(bigString);

	return 0;
}