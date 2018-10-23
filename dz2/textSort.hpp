#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <cstring>


const int RUS_FIRST_BYTE_1 = -47;
const int RUS_FIRST_BYTE_2 = -48;
const int RUS_MAX_SECOND_BYTE = -65;
const int SIZE_OF_RUS = 33;
const int SIZE_OF_ENG = 26;
const int NUMB_OF_YO = 7;
const int ASCII_NUMB_OF_YO_1 = RUS_FIRST_BYTE_1;
const int ASCII_NUMB_OF_YO_2 = -111;
const int ASCII_NUMB_OF_BIG_YO_1 = RUS_FIRST_BYTE_2;
const int ASCII_NUMB_OF_BIG_YO_2 = -127;
const int ASCII_NUMB_OF_RUS_A = -80; 
const int ASCII_NUMB_OF_ENG_A = 65;


enum format
{
	WITH_SLASHN,
	NO_SLASHN,
	NO_GARBAGE
};


void exitErr(const char *s);


int calcNumbOfStr(char *bigString);
char *readText(FILE *file);
char **formatText(char *bigString, int nStr);
char **getText(FILE *file, int *nStrings);
void writeText(char **text, FILE *res, int nStrings, format form);


bool isRusLetter(char a, char b);
bool isEngLetter(char a);
bool isLetter(char a, char b);
bool isGarbage(char *str);
int getRusNumb(char a1, char a2);
int getEngNumb(char a);
char *findFirstLetter(char *str);
int findLastLetter(char *str);


int strcmpl(char *st1, char* st2);
int fstrcmpl(char *st1, char* st2);
int strcmpr(char *st1, char* st2, int len1, int len2);
int fstrcmpr(char *st1, char* st2);
int leftCmp(const void *a, const void *b);
int rightCmp(const void *a, const void *b);
void leftSort(char **text, int nStrings);
void rightSort(char **text, int nStrings);


void memfree(char **text, char *bigString);