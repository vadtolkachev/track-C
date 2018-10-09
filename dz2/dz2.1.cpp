#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <cstring>


/*! \mainpage Онегин(дз2)
 * 
 * \author Вадим Толкачёв 
 *
 * \date 09.10.2018 
 *
 * Contact: vadtolkachev@gmail.com
 *
 */

/// Формат вывода теста
enum format
{
	WITH_SLASHN, ///< с пустыми строками
	NO_SLASHN ///< без пустых строк
};


/*!
Читает из файла, записывает текст в большую строку, создает указатели на строки текста.
\param file указатель на файл откуда читать
\param nStrings указатель на переменную, в которую будет записано кол-во строк
\return массив указателей на строки
*/
char **readText(FILE *file, int *nStrings)
{
	//----------reading-----------
	struct stat tmp;
	fstat(fileno(file), &tmp);
	long int size = tmp.st_size;

	char *bigString = (char *)calloc(size + 1, sizeof(char));
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


/*!
Записывает текст в файл.
\param text текст, который будет записан
\param res файл, в который будет записан текст
\param nStrings количество строк в тексте
\param form формат записи(с пустыми строками/без них)
*/
void writeText(char **text, FILE *res, int nStrings, format form)
{
	char c[1];
	c[0] = '\n';
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


/*!
Реверс строки.
\param st строка
*/
void strev(char *st)
{
	int len = strlen(st);
	char tmp;
	for(int i = 0; i < len/2; i++)
	{
		tmp = st[i];
		st[i] = st[len-1-i];
		st[len-1-i] = tmp;
	}
}


/*!
Реверс всех строк теста.
\param text массив строк
\param nString число строк
*/
void textrev(char **text, int nString)
{
	for(int i = 0; i < nString; i++)
		strev(text[i]);
}


/*!
Проверка на то, что символ является буквой.
\param a проверяемый символ
*/
bool isLetter(char a)
{
	if((a < 65) || ((a > 90) && (a < 97)) || (a > 122))
		return false;

	return true; 
}


/*!
Сравнение строк без учета знаков препинания.
\return число меньше нуля, если первая строка "меньше", больше нуля, если "больше", 0 если равны
*/
int strcmpl(char *st1, char* st2)
{
	if(!isLetter(st1[0]))
		return strcmpl(&st1[1], st2);

	if(!isLetter(st2[0]))
		return strcmpl(st1, &st2[1]);

	return strcmp(st1, st2);
}


/*!
strcmpl для qsort.
*/
int leftCmp(const void *a, const void *b)
{
	char *st1 = *(char **)a;
	char *st2 = *(char **)b;
	
	return strcmpl(st1, st2);
}


/*!
Сортировка строк в тексте(с начала строки).
\param text текст, строки которого нужно отсортировать
\param nStrings количество строк
*/
void leftSort(char **text, int nStrings)
{
	qsort(text, nStrings, sizeof(char *), leftCmp); 
}


/*!
Сортировка строк в тексте(с конца строки).
\param text текст, строки которого нужно отсортировать
\param nStrings количество строк
*/
void rightSort(char **text, int nStrings)
{
	textrev(text, nStrings);
	qsort(text, nStrings, sizeof(char *), leftCmp); 
	textrev(text, nStrings);
}


/*!
Удалить текст из памяти.
\param text массив указателей на строки
\param bigString указатель на первую строку текста до сортировки
*/
void memfree(char **text, char *bigString)
{
	free(bigString);
	free(text);
}


int main()
{
	FILE *file = fopen("3.txt", "r");
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
	writeText(text, res, nStrings, NO_SLASHN);
	
	char ns[2];
	ns[0] = '\n';
	ns[1] = '\n';

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
		exit(EXIT_FAILURE);	
	}
	
	memfree(text, bigString);
	return 0;
}