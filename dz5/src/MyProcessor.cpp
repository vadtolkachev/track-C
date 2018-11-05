#include "MyProcessor.hpp"
#include <stdio.h>


MyProcessor::MyProcessor()
{
	m_code = nullptr;
	m_RAM = nullptr;
	m_ramSize = 0;
	m_index = 0;
	m_errno = SUCCESS;

	m_rax = 0;
	m_rbx = 0;
	m_rcx = 0;
	m_rdx = 0;

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
	long int size;
	int checkErr = readFile(binFile, &m_code, &size);
	if(checkErr != SUCCESS)
		return checkErr;

	m_RAM = (char *)calloc(10*size, sizeof(char));
	if((errno != 0) || (m_RAM == nullptr))
		return ALLOC_ERR;
	
	m_ramSize = 10*size;
	m_index = 0;
	m_errno = SUCCESS;
	double *pTmp;

	while(m_index < size)
	{
		switch(m_code[m_index])
		{
			case N_PUSH : 
			pTmp = (double *)&m_code[m_index+1];
			push(*pTmp);
			break;

			case N_PUSH_R : pushR(m_code[m_index+1]); break;
			case N_POP : pop(nullptr); break;
			case N_POP_R : popR(m_code[m_index+1]); break;
			case N_ADD : add(); break;
			case N_SUB : sub(); break;
			case N_MUL : mul(); break;
			case N_DIV : div(); break;
			case N_SIN : pr_sin(); break;
			case N_COS : pr_cos(); break;
			case N_SQRT : pr_sqrt(); break;
			case N_IN : in(); break;
			case N_OUT : out(); break;
			case N_END : m_index = size; dumpProc("Proc end"); break;
	
			default : return PARSE_ERR;
		}

		if(m_errno != SUCCESS)
		{
			printf("m_errno = %d\n", m_errno);
			fclose(m_dumpFile);
			m_stack.~MyStack();
			assert(0);
			return PARSE_ERR;
		}
	}


	free(m_code);
	free(m_RAM);
	return SUCCESS;
}


int MyProcessor::push(data_t data)
{
	int checkErr = m_stack.push(data);
	assert(checkErr == SUCCESS);

	char str[30] = "";

	#ifdef S_DOUBLE
	m_index += 1 + sizeof(double);
	sprintf(str, "Proc push %lg", data);
	#else
	m_errno = TYPE_ERR;
	return TYPE_ERR;
	assert(0);
	#endif

	dumpProc(str);
	m_errno = checkErr;
	return checkErr;
}


int MyProcessor::pushR(char nReg)
{
	data_t data;
	char dumpStr[20];

	switch(nReg)
	{
		case N_RAX : data = m_rax; sprintf(dumpStr, "Proc push rax"); break;
		case N_RBX : data = m_rbx; sprintf(dumpStr, "Proc push rbx"); break;
		case N_RCX : data = m_rcx; sprintf(dumpStr, "Proc push rcx"); break;
		case N_RDX : data = m_rdx; sprintf(dumpStr, "Proc push rdx"); break;

		default : assert(0);
	}
		

	int checkErr = m_stack.push(data);
	assert(checkErr == SUCCESS);

	dumpProc(dumpStr);
	m_index += 2;
	m_errno = checkErr;
	return checkErr;
}


int MyProcessor::pop(data_t *data)
{	
	int checkErr;

	if(data)
	{
		checkErr = m_stack.getTop(data);

		if(checkErr != SUCCESS)
		{
			assert(0);
			m_errno = checkErr;
			return checkErr;
		}
	}
	
	checkErr = m_stack.pop();

	assert(checkErr == SUCCESS);
	m_index++;
	dumpProc("Proc pop");
	m_errno = checkErr;
	return checkErr;
}


int MyProcessor::popR(char nReg)
{
	if(m_stack.getSize() == 0)
		return EMPTY_ERR;

	data_t *data;
	char dumpStr[20];

	switch(nReg)
	{
		case N_RAX : data = &m_rax; sprintf(dumpStr, "Proc pop rax"); break;
		case N_RBX : data = &m_rbx; sprintf(dumpStr, "Proc pop rbx"); break;
		case N_RCX : data = &m_rcx; sprintf(dumpStr, "Proc pop rcx"); break;
		case N_RDX : data = &m_rdx; sprintf(dumpStr, "Proc pop rdx"); break;

		default : assert(0);
	}
		
	m_stack.getTop(data);
	int checkErr = m_stack.pop();
	assert(checkErr == SUCCESS);

	dumpProc(dumpStr);
	m_index += 2;
	m_errno = checkErr;
	return checkErr;
}


int MyProcessor::add()
{
	if(m_stack.getSize() < 2)
	{
		m_errno = EMPTY_ERR;
		return EMPTY_ERR;
	}

	data_t data1;
	data_t data2;
	
	m_stack.getTop(&data1);
	m_stack.pop();
	m_stack.getTop(&data2);
	m_stack.pop();

	
	int checkErr = m_stack.push(data1 + data2);

	dumpProc("Proc add");
	m_index++;
	m_errno = checkErr;
	return checkErr;
}


int MyProcessor::sub()
{
	if(m_stack.getSize() < 2)
	{
		m_errno = EMPTY_ERR;
		return EMPTY_ERR;
	}

	data_t data1;
	data_t data2;
	
	m_stack.getTop(&data1);
	m_stack.pop();
	m_stack.getTop(&data2);
	m_stack.pop();

	
	int checkErr = m_stack.push(data1 - data2);

	dumpProc("Proc sub");
	m_index++;
	m_errno = checkErr;
	return checkErr;
}


int MyProcessor::mul()
{
	if(m_stack.getSize() < 2)
	{
		m_errno = EMPTY_ERR;
		return EMPTY_ERR;
	}

	data_t data1;
	data_t data2;
	
	m_stack.getTop(&data1);
	m_stack.pop();
	m_stack.getTop(&data2);
	m_stack.pop();

	
	int checkErr = m_stack.push(data1 * data2);

	dumpProc("Proc mul");
	m_index++;
	m_errno = checkErr;
	return checkErr;
}


int MyProcessor::div()
{
	if(m_stack.getSize() < 2)
	{
		m_errno = EMPTY_ERR;
		return EMPTY_ERR;
	}

	data_t data1;
	data_t data2;
	
	m_stack.getTop(&data1);
	m_stack.pop();
	m_stack.getTop(&data2);
	m_stack.pop();


	dumpProc("Proc div");
	m_index++;	
	#ifdef S_DOUBLE
	int checkErr = m_stack.push(data1/data2);

	m_errno = checkErr;
	return checkErr;
	#else
	m_errno = TYPE_ERR;
	return TYPE_ERR;
	#endif
}


int MyProcessor::pr_sin()
{
	if(m_stack.getSize() < 1)
	{
		m_errno = EMPTY_ERR;
		return EMPTY_ERR;
	}

	data_t data;
	m_stack.getTop(&data);
	m_stack.pop();


	dumpProc("Proc sin");
	m_index++;
	#ifdef S_DOUBLE
	int checkErr = m_stack.push(sin(data));

	m_errno = checkErr;
	return checkErr;
	#else
	m_errno = TYPE_ERR;
	return TYPE_ERR;
	#endif
}


int MyProcessor::pr_cos()
{
	if(m_stack.getSize() < 1)
	{
		m_errno = EMPTY_ERR;
		return EMPTY_ERR;
	}

	data_t data;
	m_stack.getTop(&data);
	m_stack.pop();

	dumpProc("Proc cos");	
	m_index++;
	#ifdef S_DOUBLE
	int checkErr = m_stack.push(cos(data));

	m_errno = checkErr;
	return checkErr;
	#else
	m_errno = TYPE_ERR;
	return TYPE_ERR;
	#endif
}


int MyProcessor::pr_sqrt()
{
	if(m_stack.getSize() < 1)
	{
		m_errno = EMPTY_ERR;
		return EMPTY_ERR;
	}

	data_t data;
	m_stack.getTop(&data);
	m_stack.pop();

	dumpProc("Proc sqrt");	
	m_index++;
	#ifdef S_DOUBLE
	int checkErr = m_stack.push(sqrt(data));

	m_errno = checkErr;
	return checkErr;
	#else
	m_errno = TYPE_ERR;
	return TYPE_ERR;
	#endif
}


int MyProcessor::in()
{
	dumpProc("Proc in");
	m_index++;
	return SUCCESS;
}


int MyProcessor::out()
{
	if(m_stack.getSize() < 1)
	{
		m_errno = EMPTY_ERR;
		return EMPTY_ERR;
	}

	data_t data;
	m_stack.getTop(&data);
	m_stack.pop();

	dumpProc("Proc out");
	m_index++;
	#ifdef S_DOUBLE
	printf("Proc out : %lg\n", data);
	return SUCCESS;
	#else
	m_errno = TYPE_ERR;
	return TYPE_ERR;
	#endif
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

	/*fprintf(m_dumpFile, "Processor[%p]\n{\n", this);
	fprintf(m_dumpFile, "\tm_index = %u\n", m_index);
	fprintf(m_dumpFile, "\tm_rax = %lg\n\tm_rbx = %lg\n\tm_rcx = %lg\n\tm_rdx = %lg\n}\n\n", m_rax, m_rbx, m_rcx, m_rdx);
	*/
}
