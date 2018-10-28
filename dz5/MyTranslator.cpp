#include "MyTranslator.hpp"
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <cstring>


const char N_ADD = 1;
const char N_SUB = 2;
const char N_MUL = 3;
const char N_DIV = 4;

const char N_OUT = 5;
const char N_END = 6;
const char N_PUSH = 7;
const char N_POP = 8;

const char N_PUSH_R = 10; 
const char N_PUSH_PR = 11; 
const char N_POP_R = 12; 
const char N_POP_PR = 13; 

const char N_RAX = 20;
const char N_RBX = 21;
const char N_RCX = 22;
const char N_RDX = 23;
const char N_NOR = 30;




int MyTranslator::translate(FILE *asmFile, FILE *txtFile, FILE *binFile, TrFormat format)
{
	if((!asmFile) || (!txtFile) || (!binFile))
		return NULLPTR_ERR;

	struct stat tmp;
	fstat(fileno(asmFile), &tmp);
	long int size = tmp.st_size;
	//printf("size = %ld\n", size);

	char *bigString = (char *)calloc(size + 1, sizeof(char));
	if((errno != 0) || bigString == nullptr)
		return NULLPTR_ERR;

	if(fread(bigString, size, 1, asmFile) != 1)
		return READ_ERR;

	//printf("1.strlen = %ld\n", strlen(bigString));
	//bigString[size] = '\n';
	//printf("2.strlen = %ld\n", strlen(bigString));

	int checkErr;
	if(format == INT_F)
		checkErr = parseInt(bigString, txtFile, binFile); 
	
	if(checkErr != SUCCESS)
		return PARSE_ERR;

	return SUCCESS;
}


int MyTranslator::parseInt(char *bigString, FILE *txtFile, FILE *binFile)
{
	int checkErr;
	int len = strlen(bigString);
	
	for(int i = 0; i < len; i++)
	{
		checkErr = parseText(bigString, &i, txtFile, binFile);
	}

	return checkErr;
}


int MyTranslator::readInt(char *str, int *res, int *len)
{
	int n = 0;
	int tmp_res = 0;

	if(str[0] == '\n')
		return PARSE_ERR;	

	for(int i = 0; i < 11; i++)
	{
		if(((str[i] < '0') || (str[i] > '9')) && (str[i] != '\n') && (str[i] != ']') && ((str[i] != '-') || (i != 0)))
		{
			printf("error:str[i] = %c\n", str[i]);
			return PARSE_ERR;
		}

		if((str[i] == '\n') || (str[i] == ']'))
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
	*len = n;
	*res = tmp_res;

	return SUCCESS;
}


int MyTranslator::parseText(char *bigString, int *index, FILE *txtFile, FILE *binFile)
{
	int len = strlen(bigString);
	int i = *index;	
	int checkErr = SUCCESS;

	switch(bigString[i])
	{
		case('p'):
		{
			checkErr = parsePush(bigString, &i, txtFile, binFile);

			if(checkErr != SUCCESS)
				checkErr = parsePop(bigString, &i, txtFile, binFile);
	
			if(checkErr != SUCCESS)
				return checkErr;

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

		default: return PARSE_ERR;
	}

	*index = i;
	return SUCCESS;
}


int MyTranslator::parsePush(char *bigString, int *index, FILE *txtFile, FILE *binFile)
{
	int *pInt;
	char buf[4];
	int res = 0;
	int res_len = 0;
	int i = *index;
	int len = strlen(bigString);
	int checkErr = SUCCESS;
		

	if(bigString[i+1] != 'u')
		return PARSE_ERR;

	if(bigString[i+2] != 's')
		return PARSE_ERR;
	
	if(bigString[i+3] != 'h')
		return PARSE_ERR;
	
	if(bigString[i+4] != ' ')
		return PARSE_ERR;

	if(bigString[i+5] == '[')
	{
		if(bigString[i+6] == 'r')
		{
			if((bigString[i+7] != 'a') && (bigString[i+7] != 'b') && (bigString[i+7] != 'c') && (bigString[i+7] != 'd'))
				return PARSE_ERR;
						
			if(bigString[i+8] != 'x')
				return PARSE_ERR;

			if(bigString[i+7] == 'a')
			{
				fprintf(txtFile, "%d %d", N_PUSH_R, N_RAX);
				fprintf(binFile, "%c%c", N_PUSH_R, N_RAX);							
			}

			if(bigString[i+7] == 'b')
			{
				fprintf(txtFile, "%d %d", N_PUSH_R, N_RBX);
				fprintf(binFile, "%c%c", N_PUSH_R, N_RBX);	
			}

			if(bigString[i+7] == 'c')
			{
				fprintf(txtFile, "%d %d", N_PUSH_R, N_RCX);
				fprintf(binFile, "%c%c", N_PUSH_R, N_RCX);								
			}

			if(bigString[i+7] == 'd')
			{
				fprintf(txtFile, "%d %d", N_PUSH_R, N_RDX);
				fprintf(binFile, "%c%c", N_PUSH_R, N_RDX);								
			}
						
						
			if((bigString[i+9] != ']') && (bigString[i+9] != '+') && (bigString[i+9] != '-'))
				return PARSE_ERR;
						
			i += 9;
			res = 0;

			if(bigString[i] == '+')
			{	
				i++;
	
				checkErr = readInt(&bigString[i], &res, &res_len);
				i += res_len;
			}

			if(bigString[i] == '-')
			{		
				checkErr = readInt(&bigString[i], &res, &res_len);				
				i += res_len;
			}

			if(checkErr != SUCCESS)
				return PARSE_ERR;
						
			if(bigString[i] != ']')
				return PARSE_ERR;
						
			if(bigString[i+1] != '\n')
				return PARSE_ERR;
						
			i++;
			if(i > len)
				return PARSE_ERR;

			pInt = (int *)buf;
			*pInt = res;
			fprintf(txtFile, " %d\n", *(int *)buf);
			fprintf(binFile, "%c", N_PUSH);
			for(int l = 0; l < 4; l++)
				fprintf(binFile, "%c", buf[l]);
						
		}
		else
		{
			if(readInt(&bigString[i+6], &res, &res_len) != SUCCESS)
				return PARSE_ERR;
						

			i += res_len + 7;
			if(bigString[i-1] != ']')
				return PARSE_ERR;

			if(bigString[i] != '\n')
				return PARSE_ERR;
							
			if(i > len)
				return PARSE_ERR;		

			pInt = (int *)buf;
			*pInt = res;
			//printf("b = %d; (int)buf = %d\n", b, *(int *)buf);
			fprintf(txtFile, "%d %d %d\n", N_PUSH_R, N_NOR, *(int *)buf);
			fprintf(binFile, "%c%c", N_PUSH_R, N_NOR);
			for(int l = 0; l < 4; l++)
				fprintf(binFile, "%c", buf[l]);
			if(errno)
				perror("push");
		}

	}
	else
	{
		int res = 0;
		int res_len = 0;

		if(readInt(&bigString[i+5], &res, &res_len) != SUCCESS)
			return PARSE_ERR;

		i += res_len + 5;
		if(bigString[i] != '\n')
			return PARSE_ERR;
	
		if(i > len)
			return PARSE_ERR;		

		pInt = (int *)buf;
		*pInt = res;
		//printf("b = %d; (int)buf = %d\n", b, *(int *)buf);
		fprintf(txtFile, "%d %d\n", N_PUSH, *(int *)buf);
		fprintf(binFile, "%c", N_PUSH);
		for(int l = 0; l < 4; l++)
			fprintf(binFile, "%c", buf[l]);
		if(errno)
			perror("push");
	}

	*index = i;
	return SUCCESS;

}


int MyTranslator::parsePop(char *bigString, int *index, FILE *txtFile, FILE *binFile)
{
	return PARSE_ERR;
}