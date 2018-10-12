#include "textSort.hpp"


void exitErr(const char *s)
{
	printf("error: %s\n", s);
	exit(EXIT_FAILURE);
}


int calcNumbOfStr(char *bigString)
{
	int i = 0;
	int nStr = 1;	
	while(bigString[i] != 0)
	{
		if(bigString[i] == '\n')
			nStr++;
		i++;
	}
	
	return nStr;
}


char *readText(FILE *file)
{
	struct stat tmp;
	fstat(fileno(file), &tmp);
	long int size = tmp.st_size;

	char *bigString = (char *)calloc(size + 1, sizeof(char));
	if((errno != 0) || bigString == nullptr)
		exitErr("Memory cannot be allocated");
	
	if(fread(bigString, size, 1, file) != 1)
		exitErr("reading error");

	return bigString;
}


char **formatText(char *bigString, int nStr)
{
	char **text = (char **)calloc(nStr, sizeof(char *));
	if(errno != 0)
		exitErr("Memory cannot be allocated");

	text[0] = bigString;
	int n = 1;
	int i = 0;
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


char **getText(FILE *file, int *nStrings)
{
	char *bigString = readText(file);

	int nStr = calcNumbOfStr(bigString);
	if(nStrings)
		*nStrings = nStr;
		
	char **text = formatText(bigString, nStr);

	return text;
}


void writeText(char **text, FILE *res, int nStrings, format form)
{
	int checkErr = 0;
	for(int i = 0; i < nStrings; i++)
	{	
		checkErr = fwrite(text[i], strlen(text[i]), 1, res);
		if((checkErr != 1) && (text[i][0] != 0))
			exitErr("writing error");

		if((form == WITH_SLASHN) || (text[i][0] != 0))
			fprintf(res, "\n");
	}
}


bool isRusLetter(char a, char b)
{
	if((b > RUS_MAX_SECOND_BYTE) || ((a != RUS_FIRST_BYTE_1) && (a != RUS_FIRST_BYTE_2)))
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

	if(((a1 == ASCII_NUMB_OF_YO_1) && (a2 == ASCII_NUMB_OF_YO_2)) || 
	((a1 == ASCII_NUMB_OF_BIG_YO_1) && (a2 == ASCII_NUMB_OF_BIG_YO_2)))
		return NUMB_OF_YO;

	int n = 0;
	if(a1 == RUS_FIRST_BYTE_1)
		n = -(RUS_MAX_SECOND_BYTE + 1);

	n += a2 + (-ASCII_NUMB_OF_RUS_A) + SIZE_OF_RUS;
	
	//getRusNumb(a) = getRusNumb(A)
	if(n >= SIZE_OF_RUS )
		n -= SIZE_OF_RUS - 1;

	//for yo
	if(n >= NUMB_OF_YO)
		n++;

	return n;
}


int getEngNumb(char a)
{
	if(!isEngLetter(a))
		exitErr("cmpEng");

	int n = a - ASCII_NUMB_OF_ENG_A + 1;
	if(n > SIZE_OF_ENG)
		n -= SIZE_OF_ENG;

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