#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <cstring>
#include <codecvt>


long int numb = 0;
long int numb2 = 0;
long int numb3 = 0;
long int numb4 = 0;
long int numb5 = 0;
long int numb6 = 0;

enum format
{
	WITH_SLASHN,
	NO_SLASHN
};


char **readText(FILE *file, int *nStrings)
{
	//----------reading-----------
	struct stat tmp;
	fstat(fileno(file), &tmp);
	long int size = tmp.st_size;

	char *bigString = (char *)calloc(size + 1, sizeof(char));
	if((errno != 0) || bigString == nullptr)
	{
		perror("Memory cannot be allocated");
		exit(EXIT_FAILURE);
	}
	
	if(fread(bigString, size, 1, file) != 1)
	{
		printf("reading error\n");	
		exit(EXIT_FAILURE);
	}
	

	//-----calculating number of strings-----
	int i = 0;
	int nStr = 1;	
	while(bigString[i] != 0)
	{
		if(bigString[i] == '\n')
			nStr++;
		i++;
	}	

	if(nStrings)
		*nStrings = nStr;
	

	//------big string -> pointer array------
	char **text = (char **)calloc(nStr, sizeof(char *));
	if(errno != 0)
	{
		perror("Memory cannot be allocated");
		exit(EXIT_FAILURE);
	}

	text[0] = bigString;
	int n = 1;
	i = 0;
	while(bigString[i] != 0)
	{
		if(bigString[i] == '\n')
		{
			bigString[i] = 0;
			text[n] = &bigString[i + 1];
			n++;
		}		
		i++;
	}

	return text;
}


void writeText(char **text, FILE *res, int nStrings, format form)
{
	char c[1];
	c[0] = '\n';
	c[1] = 0;
	int s = 0;
	for(int i = 0; i < nStrings; i++)
	{	
		s = fwrite(text[i], strlen(text[i]), 1, res);
		if((s != 1) && (text[i][0] != 0))
		{
			printf("writing error\n");
			exit(EXIT_FAILURE);
		}
		if((form == WITH_SLASHN) || (text[i][0] != 0))
		{	
			s = fwrite(c, 1, 1, res);
			if(s != 1)
			{
				printf("writing error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}


bool isRusLetter(char a)
{
}


bool inEngLetter(char a)
{
}



bool isLetter(char a)
{	
	printf("n = %ld; n2 = %ld; n3 = %ld; n4 = %ld; n5 = %ld; n6 = %ld\n", 
		numb++, numb2, numb3, numb4, numb5, numb6);
	//printf("1\n");
	if(a > 0)
	{
		//printf("2\n");
		return false;
	}
	
	return true; 
}


int strcmpl(char *st1, char* st2)
{
	if(st1[0] == 0)
	{
		if(st2[0] == 0)
			return 0;
		return -1;	
	}

	if(st2[0] == 0)
		return 1;

	printf("n2 = %ld\n", numb2++);
	if(!isLetter(st1[0]))
	{
		//printf("3\n");
		return strcmpl(&st1[1], st2);
	}
	
	printf("n3 = %ld\n", numb3++);
	if(!isLetter(st2[0]))
	{
		//printf("4\n");
		return strcmpl(st1, &st2[1]);
	}
	
	if(st1[0] > st2[0])
		return 1;

	if(st1[0] < st2[0])
		return -1;

	if(st1[0] == 0)
		return 0;

	return strcmpl(&st1[1], &st2[1]);
}


int strcmpr(char *st1, char* st2, int len1, int len2)
{
	//пустая строка
	if(len1 == 0)
	{
		if(len2 == 0)
			return 0;
		return -1;	
	}

	if(len2 == 0)
		return 1;	
	
	printf("n4 = %ld\n", numb4++);
	//не буква
	if(!isLetter(st1[len1 - 1]))
	{
		printf("5\n");
		return strcmpr(st1, st2, len1 - 1, len2);
	}
	printf("n5 = %ld\n", numb5++);
	if(!isLetter(st2[len2 - 1]))
	{		
		printf("6\n");
		return strcmpr(st1, st2, len1, len2 - 1);
	}
	//сравнение
	if(st1[len1 - 1] > st2[len2 - 1])
	{
		if((st1[len1 - 1] > -81) && (st2[len2 - 1] < -81))
			return -1;
		
		return 1;
	}

	
	if(st1[len1 - 1] < st2[len2 - 1])
	{
		if((st1[len1 - 1] < -81) && (st2[len2 - 1] > -81))
			return 1;

		return -1;
	}
	//если равны
	return strcmpr(st1, st2, len1 - 1, len2 - 1);

}


int leftCmp(const void *a, const void *b)
{
	char *st1 = *(char **)a;
	char *st2 = *(char **)b;
	
	printf("n6 = %ld\n", numb6++);
	return strcmpl(st1, st2);
}


int rightCmp(const void *a, const void *b)
{
	char *st1 = *(char **)a;
	char *st2 = *(char **)b;
	
	return strcmpr(st1, st2, strlen(st1), strlen(st2));
}


void leftSort(char **text, int nStrings)
{
	qsort(text, nStrings, sizeof(char *), leftCmp); 
}


void rightSort(char **text, int nStrings)
{
	qsort(text, nStrings, sizeof(char *), rightCmp); 
}


void memfree(char **text, char *bigString)
{
	free(bigString);
	free(text);
}


int main()
{
	FILE *file = fopen("2.txt", "r");
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
	
	int nStrings;
	char **text = readText(file, &nStrings);
	char *bigString = text[0]; 
	writeText(text, res, nStrings, WITH_SLASHN);
	
	char ns[2];
	ns[0] = '\n';
	ns[1] = '\n';
	ns[2] = '\0';

	fwrite(ns, 2, 1, res);
	leftSort(text, nStrings);
	writeText(text, res, nStrings, NO_SLASHN);

	fwrite(ns, 2, 1, res);
	rightSort(text, nStrings);
	writeText(text, res, nStrings, NO_SLASHN);
		

	fclose(file);
	if(errno != 0)
	{
		fprintf(stderr, "file fclose() failed\n");
		exit(EXIT_FAILURE);		
	}
	/*
	char a[2];
	a[1] = '\n';
	int b = -75;
	for(int i = 1; i < 128; i++)
	{
		if(i == 3)
			i = b;
		printf("%d - %d - %c\n", i, (char)i, (char)i);
		a[0] = (char)i;
		if(i == 3)
			a[0] = -75;
		if(fwrite(a, 2, 1, res) < 1)
		{
			perror("error");
			exit(EXIT_FAILURE);
		}
		if(i == b)
			i = 3;	
	}
	*/
	fclose(res);
	if(errno != 0)
	{
		fprintf(stderr, "res fclose() failed\n");
	}

	memfree(text, bigString);

	return 0;
}