#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <cstring>


const int RUS_FIRST_BYTE_1 = -47;
const int RUS_FIRST_BYTE_2 = -48;
const int RUS_MAX_SECOND_BYTE = -65;
const int SIZE_OF_RUS = 33;
const int NUMB_OF_YO = 7;
const int ASCII_NUMB_OF_YO_1 = RUS_FIRST_BYTE_1;
const int ASCII_NUMB_OF_YO_2 = -111;
const int ASCII_NUMB_OF_BIG_YO_1 = RUS_FIRST_BYTE_2;
const int ASCII_NUMB_OF_BIG_YO_2 = -127;
const int ASCII_NUMB_OF_RUS_A = -80; 


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

/*
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
*/


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
	
	//Чтобы номер заглавных букв был равен номеру строчных букв
	if(n >= SIZE_OF_RUS )
		n -= SIZE_OF_RUS - 1;

	//ё
	if(n >= NUMB_OF_YO)
		n++;

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