#include "MyTranslator.hpp"
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <cstring>


const char N_PUSH = 1;
const char N_ADD = 2;
const char N_SUB = 3;
const char N_MUL = 4;
const char N_DIV = 5;
const char N_OUT = 6;
const char N_END = 7;


int MyTranslator::translate(FILE *asmFile, FILE *txtFile, FILE *binFile, TrFormat format)
{
	if((!asmFile) || (!txtFile) || (!binFile))
		return NULLPTR_ERR;

	struct stat tmp;
	fstat(fileno(asmFile), &tmp);
	long int size = tmp.st_size;

	char *bigString = (char *)calloc(size + 1, sizeof(char));
	if((errno != 0) || bigString == nullptr)
		return NULLPTR_ERR;

	if(fread(bigString, size, 1, asmFile) != 1)
		return READ_ERR;
	
	int checkErr;
	if(format == INT_F)
		checkErr = parseInt(bigString, txtFile, binFile); 
	
	if(checkErr != SUCCESS)
		return PARSE_ERR;

	return SUCCESS;
}


int MyTranslator::parseInt(char *bigString, FILE *txtFile, FILE *binFile)
{
	int len = strlen(bigString);	
	char buf[4];

	for(int i = 0; i < len; i++)
	{
		switch(bigString[i])
		{
			case('p'):
			{
				if(bigString[i+1] != 'u')
					return PARSE_ERR;

				if(bigString[i+2] != 's')
					return PARSE_ERR;
	
				if(bigString[i+3] != 'h')
					return PARSE_ERR;
	
				if(bigString[i+4] != ' ')
					return PARSE_ERR;

				int b = 0;
				int numb = 0;
				if(readInt(&bigString[i+5], &b, &numb) != SUCCESS)
					return PARSE_ERR;

				i += numb + 5;
				if(bigString[i] != '\n')
					return PARSE_ERR;
	
				if(i > len)
					return PARSE_ERR;		

				int *pInt = (int *)buf;
				*pInt = b;
				//printf("b = %d; (int)buf = %d\n", b, *(int *)buf);
				fprintf(txtFile, "%d %d\n", N_PUSH, *(int *)buf);
				fprintf(binFile, "%c", N_PUSH);
				for(int l = 0; l < 4; l++)
					fprintf(binFile, "%c", buf[l]);
				if(errno)
					perror("push");

				break;				
			}

			case('a'):
			{
				if(bigString[i+1] != 'd')
					return PARSE_ERR;

				if(bigString[i+2] != 'd')
					return PARSE_ERR;

				i += 3;
				if(bigString[i] != '\n')
					return PARSE_ERR;
				if(i > len)
					return PARSE_ERR;

				fprintf(txtFile, "%d\n", N_ADD);
				fprintf(binFile, "%c", N_ADD);

				break;
			}
			
			case('m'):
			{
				if(bigString[i+1] != 'u')
					return PARSE_ERR;

				if(bigString[i+2] != 'l')
					return PARSE_ERR;

				i += 3;
				if(bigString[i] != '\n')
					return PARSE_ERR;
				if(i > len)
					return PARSE_ERR;

				fprintf(txtFile, "%d\n", N_MUL);
				fprintf(binFile, "%c", N_MUL);

				break;				
			}

			case('s'):
			{
				if(bigString[i+1] != 'u')
					return PARSE_ERR;

				if(bigString[i+2] != 'b')
					return PARSE_ERR;

				i += 3;
				if(bigString[i] != '\n')
					return PARSE_ERR;
				if(i > len)
					return PARSE_ERR;

				fprintf(txtFile, "%d\n", N_SUB);
				fprintf(binFile, "%c", N_SUB);

				break;				
			}

			case('d'):
			{
				if(bigString[i+1] != 'i')
					return PARSE_ERR;

				if(bigString[i+2] != 'v')
					return PARSE_ERR;

				i += 3;
				if(bigString[i] != '\n')
					return PARSE_ERR;
				if(i > len)
					return PARSE_ERR;

				fprintf(txtFile, "%d\n", N_DIV);
				fprintf(binFile, "%c", N_DIV);	

				break;			
			}

			case('o'):
			{
				if(bigString[i+1] != 'u')
					return PARSE_ERR;

				if(bigString[i+2] != 't')
					return PARSE_ERR;

				i += 3;
				if(bigString[i] != '\n')
					return PARSE_ERR;
				if(i > len)
					return PARSE_ERR;

				fprintf(txtFile, "%d\n", N_OUT);
				fprintf(binFile, "%c", N_OUT);

				break;				
			}

			case('e'):
			{
				if(bigString[i+1] != 'n')
					return PARSE_ERR;

				if(bigString[i+2] != 'd')
					return PARSE_ERR;

				i += 3;
				if(bigString[i] != '\n')
					return PARSE_ERR;
				if(i > len)
					return PARSE_ERR;

				fprintf(txtFile, "%d\n", N_END);
				fprintf(binFile, "%c", N_END);

				break;			
			}

			default:
			{
				return PARSE_ERR;
			}
		}
	}

	return SUCCESS;
}


int MyTranslator::readInt(char *str, int *res, int *numb)
{
	int n = 0;
	int tmp_res = 0;

	if(str[0] == '\n')
		return PARSE_ERR;	

	for(int i = 0; i < 11; i++)
	{
		if(((str[i] < '0') || (str[i] > '9')) && (str[i] != '\n') && ((str[i] != '-') || (i != 0)))
		{
			//printf("str[i] = %c\n", str[i]);
			return PARSE_ERR;
		}

		if(str[i] == '\n')
			break;

		if(n == 9)
		{
			if(tmp_res > 214748364)
				return PARSE_ERR;
	
			int next = str[i] - (int)'0';
			if((tmp_res == 214748364) && (next > 7))
				return PARSE_ERR;
		}
		
		if((str[i] >= '0') && (str[i] <= '9'))
		{
			n++;
			tmp_res = 10*tmp_res;
			tmp_res += str[i] - (int)'0';
			//printf("%d.tmp_res = %d\n", i, tmp_res);
		}
	}

	if((str[0] == '0') && (n != 1))
		return PARSE_ERR;

	if(str[0] == '-')
	{
		if(str[1] == '0')
			return PARSE_ERR;

		n++;
		tmp_res = -tmp_res;
	}
	
	//printf("n = %d; res = %d\n", n, tmp_res);
	*numb = n;
	*res = tmp_res;

	return SUCCESS;
}