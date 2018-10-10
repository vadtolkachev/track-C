#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <cstring>
#include <codecvt>


const int RUS_FIRST_BITE_1 = -47;
const int RUS_FIRST_BITE_2 = -48;
const int RUS_MAX_SECOND_BITE = -65;


enum format
{
	WITH_SLASHN,
	NO_SLASHN
};


void exitErr(const char *s)
{
	printf("error: %s\n", s);
	exit(EXIT_FAILURE);
}



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
	char c[2] = "";
	c[0] = '\n';
	c[1] = 0;
	int checkErr = 0;
	for(int i = 0; i < nStrings; i++)
	{	
		checkErr = fwrite(text[i], strlen(text[i]), 1, res);
		if((checkErr != 1) && (text[i][0] != 0))
		{
			printf("writing error\n");
			exit(EXIT_FAILURE);
		}
		if((form == WITH_SLASHN) || (text[i][0] != 0))
		{	
			checkErr = fwrite(c, 1, 1, res);
			if(checkErr != 1)
			{
				printf("writing error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}


bool isRusLetter(char a, char b)
{
	if((b > RUS_MAX_SECOND_BITE) || ((a != RUS_FIRST_BITE_1) && (a != RUS_FIRST_BITE_2)))
	{
		return false;
	}

	return true; 
}


bool isEngLetter(char a)
{
	if((a < 'A') || ((a > 'Z') && (a < 'a')) || (a > 'z'))
		return false;

	return true; 
}



bool isLetter(char a, char b)
{	
	if(!isRusLetter(a, b) && !isEngLetter(a))
		return false;

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
	
	//Чтобы номер заглавных букв был равен номеру строчных букв
	if(n > 32)
		n -= 32;

	//ё
	if(n > 6)
		n++;
	
	//ё
	if((n == 35) || (n == -14))
		n = 7;

	return n;
}


int getEngNumb(char a)
{
	if(!isEngLetter(a))
		exitErr("cmpEng");

	int n = a - 64;
	if(n > 32)
		n -= 32;

	return n;
}


char *findFirstLetter(char *str)
{
	int len = strlen(str);
	for(int i = 0; i < len; i++)
	{
		if(isLetter(str[i], str[i+1]))
			return &str[i];
	}
	
	return &str[len];
}


int findLastLetter(char *str)
{
	int len = strlen(str);
	for(int i = len - 1; i >= 0; i--)
	{
		if(isLetter(str[i], str[i+1]))
			return i + 1;
	}
	
	return 0;
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

	if((isRusLetter(st1[0], st1[1])) && (isRusLetter(st2[0], st2[1])))
	{
		if(getRusNumb(st1[0], st1[1]) > getRusNumb(st2[0], st2[1]))
			return 1;

		if(getRusNumb(st1[0], st1[1]) < getRusNumb(st2[0], st2[1]))
			return -1;

		return strcmpl(&st1[2], &st2[2]);
	}


	if((isEngLetter(st1[0])) && (isEngLetter(st2[0])))
	{
		if(getEngNumb(st1[0]) > getEngNumb(st2[0]))
			return 1;

		if(getEngNumb(st1[0]) < getEngNumb(st2[0]))
			return -1;

		return strcmpl(&st1[1], &st2[1]);
	}
	
	if(st1[0] > st2[0])
		return 1;

	if(st1[0] < st2[0])
		return -1;

	if(st1[0] == 0)
		return 0;

	return strcmpl(&st1[1], &st2[1]);
}


int fstrcmpl(char *st1, char* st2)
{
	return strcmpl(findFirstLetter(st1), findFirstLetter(st2));	
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
	
	
	if((isRusLetter(st1[len1-2], st1[len1-1])) && (isRusLetter(st2[len2-2], st2[len2-1])))
	{
		if(getRusNumb(st1[len1-2], st1[len1-1]) > getRusNumb(st2[len2-2], st2[len2-1]))
			return 1;

		if(getRusNumb(st1[len1-2], st1[len1-1]) < getRusNumb(st2[len2-2], st2[len2-1]))
			return -1;

		return strcmpr(st1, st2, len1-2, len2-2);
	}


	if((isEngLetter(st1[len1-1])) && (isEngLetter(st2[len2-1])))
	{
		if(getEngNumb(st1[len1-1]) > getEngNumb(st2[len2-1]))
			return 1;

		if(getEngNumb(st1[len1-1]) < getEngNumb(st2[len2-1]))
			return -1;

		return strcmpr(st1, st2, len1-1, len2-1);
	}		

	if(st1[len1 - 1] > st2[len2 - 1])
	{
		return 1;
	}

	
	if(st1[len1 - 1] < st2[len2 - 1])
	{
		return -1;
	}

	return strcmpr(st1, st2, len1 - 1, len2 - 1);

}


int fstrcmpr(char *st1, char* st2)
{
	return strcmpr(st1, st2, findLastLetter(st1), findLastLetter(st2));
}


int leftCmp(const void *a, const void *b)
{
	char *st1 = *(char **)a;
	char *st2 = *(char **)b;
	
	return fstrcmpl(st1, st2);
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
	
	char ns[3] = "";
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

	fclose(res);
	if(errno != 0)
	{
		fprintf(stderr, "res fclose() failed\n");
	}

	memfree(text, bigString);

	return 0;
}