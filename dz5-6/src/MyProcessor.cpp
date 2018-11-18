#include "MyProcessor.hpp"
#include <stdio.h>


MyProcessor::MyProcessor()
{
	m_code = nullptr;
	//m_RAM = nullptr;
	//m_ramSize = 0;
	m_ramSize = RAM_SIZE;
	for(int i = 0; i < RAM_SIZE; i++)
		m_RAM[i] = 0;

	m_index = 0;
	m_errno = SUCCESS;

	m_rax = 0;
	m_rbx = 0;
	m_rcx = 0;
	m_rdx = 0;
	m_rex = 0;

	char str[45] = "";
	getDumpFileName(str);
	m_dumpFile = fopen(str, "w");
	if(errno != 0)
	{
		assert(0);
		m_errno = OPEN_ERR;
	}

	dumpProc("Processor created");
}


MyProcessor::~MyProcessor()
{
	dumpProc("Processor destroyed");
	fclose(m_dumpFile);
}


int MyProcessor::readFile(FILE *file, char **str, long int *pSize)
{
	struct stat tmp;
	fstat(fileno(file), &tmp);
	long int size = tmp.st_size;

	char *bigString = (char *)calloc(size, sizeof(char));
	if((errno != 0) || (bigString == nullptr))
		return ALLOC_ERR;
	
	int checkErr = fread(bigString, size, 1, file);
	if(checkErr != 1)
	{
		printf("size = %ld\n", size);
		printf("checkErr = %d\n", checkErr);
		return READ_ERR;
	}

	*str = bigString;
	*pSize = size;
	return SUCCESS;
}


int MyProcessor::proc_exec(FILE *binFile)
{
	#ifndef S_DOUBLE
	assert(0);
	#endif

	long int size;
	int checkErr = readFile(binFile, &m_code, &size);
	if(checkErr != SUCCESS)
		return checkErr;

	//m_RAM = (char *)calloc(10*size, sizeof(char));
	//if((errno != 0) || (m_RAM == nullptr))
	//	return ALLOC_ERR;
	//m_ramSize = 10*size;
	m_index = 0;
	m_errno = SUCCESS;

	while(m_index < size)
	{
		switch(m_code[m_index])
		{
			#define CMD_DEF(name, str, num, asm_code, disasm_code, proc_code) \
			case N_##name : proc_code; break;

			#include "CmdDef.hpp"

			#undef CMD_DEF

			default : printf("m_index = %d\n", m_index); return PARSE_ERR;
		}

		if(m_errno != SUCCESS)
		{
			printf("m_errno = %d\n", m_errno);
			fclose(m_dumpFile);
			m_stack.~MyStack();
			m_retStack.~MyStack();
			assert(0);
			return PARSE_ERR;
		}
	}


	free(m_code);
	//free(m_RAM);
	return SUCCESS;
}


int MyProcessor::readDouble(double *numb)
{
	#ifndef S_DOUBLE
	assert(0);
	#endif

	double d;
	char doubleStr[50];
	char *checkStr = fgets(doubleStr, 50, stdin);
	if((checkStr != doubleStr))
	{
		printf("readDouble error 1\n");	
		return READ_ERR;
	}

	char *pPosition = strchr(doubleStr, '\n');
	if(pPosition == nullptr)
	{
		printf("readDouble error 2\n");
		return READ_ERR;
	}

	d = strtod(doubleStr, &pPosition);

	if((errno != 0) || (pPosition == doubleStr) || (*pPosition != '\n'))
	{
		printf("error : pPos = %c = %d\nPrint double\n", *pPosition, *pPosition);
		return READ_ERR;
	}

	*numb = d;		

	return SUCCESS;
}


int MyProcessor::getNReg(unsigned index, data_t **pdata, char *pcReg)
{
	char tmps[2] = "";
	char cReg;
	data_t *data;

	#define REG_DEF(big_name, small_name, numb) 	\
	case N_R##big_name##X : data = &m_r##small_name##x; strcpy(tmps, #small_name); cReg = tmps[0]; break;

	switch(m_code[index])
	{
		REGS_DEF

		default : assert(0);
	}

	#undef REG_DEF

	*pcReg = cReg;
	*pdata = data;

	return SUCCESS;
}


void MyProcessor::getDumpFileName(char str[45]) const
{
	char str1[45] = "logs/procInfo[";
	char str3[6] = "].log";

	char str2[19] = "";
	sprintf(str2, "%p", this);

	strcat(str1, str2);
	strcat(str1, str3);
	strcpy(str, str1);
}


void MyProcessor::dumpProc(const char *str) const
{
	assert(m_dumpFile);
	fprintf(m_dumpFile, "%s\n", str);

	fprintf(m_dumpFile, "Processor[%p]\n{\n", this);
	fprintf(m_dumpFile, "\tm_index = %u\n", m_index);
	fprintf(m_dumpFile, "\tm_rax = %lg\n\tm_rbx = %lg\n\tm_rcx = %lg\n\tm_rdx = %lg\n\tm_rcx = %lg\n}\n\n", m_rax, m_rbx, m_rcx, m_rdx, m_rex);
	fprintf(m_dumpFile, "\tm_RAM[%ld]\n\t{\n", m_ramSize);
	for(int i = 0; i < m_ramSize; i++)
	{
		fprintf(m_dumpFile, "\t\t[%d] : %lg\n", i, m_RAM[i]);
	}
	fprintf(m_dumpFile, "\t}\n}\n\n");
}
