#include "MyDisassembler.hpp"


int MyDisassembler::readFile(FILE *file, char **str, long int *pSize)
{
	struct stat tmp;
	fstat(fileno(file), &tmp);
	long int size = tmp.st_size;

	char *bigString = (char *)calloc(size, sizeof(char));
	if((errno != 0) || (bigString == nullptr))
		return ALLOC_ERR;
	
	if(fread(bigString, size, 1, file) != 1)
		return READ_ERR;

	*str = bigString;
	*pSize = size;
	return SUCCESS;
}
	

int MyDisassembler::disassemble(FILE *binFile, FILE *txtFile, FILE *asmFile)
{
	long int size;
	int checkErr = readFile(binFile, &m_buf, &size);
	if(checkErr != SUCCESS)
		return checkErr;

	m_index = 0;

	while(m_index < size)
	{
		switch(m_buf[m_index])
		{
			case N_PUSH : parsePush(txtFile, asmFile); break;
			case N_PUSH_R : parsePushR(txtFile, asmFile); break;
			case N_POP : parsePop(txtFile, asmFile); break;
			case N_POP_R : parsePopR(txtFile, asmFile); break;
			case N_ADD : parseAdd(txtFile, asmFile); break;
			case N_SUB : parseSub(txtFile, asmFile); break;
			case N_MUL : parseMul(txtFile, asmFile); break;
			case N_DIV : parseDiv(txtFile, asmFile); break;
			case N_SIN : parseSin(txtFile, asmFile); break;
			case N_COS : parseCos(txtFile, asmFile); break;
			case N_SQRT : parseSqrt(txtFile, asmFile); break;
			case N_IN : parseIn(txtFile, asmFile); break;
			case N_OUT : parseOut(txtFile, asmFile); break;
			case N_END : parseEnd(txtFile, asmFile); break;
	
			default : return PARSE_ERR;
		}
	}

	free(m_buf);
	return SUCCESS;
}


void MyDisassembler::parsePush(FILE *txtFile, FILE *asmFile)
{
	double *tmp = (double *)&m_buf[m_index+1];
	fprintf(txtFile, "%d %lg\n", N_PUSH, *tmp);
	fprintf(asmFile, "push %lg\n", *tmp);

	#ifdef S_DOUBLE
	m_index += 1 + sizeof(double);
	#else
	assert(0);
	#endif
}


void MyDisassembler::parsePushR(FILE *txtFile, FILE *asmFile)
{
	fprintf(txtFile, "%d ", N_PUSH_R);
	fprintf(asmFile, "push ");
	switch(m_buf[m_index+1])
	{
		case N_RAX : 
		fprintf(txtFile, "%d\n", N_RAX);
		fprintf(asmFile, "rax\n");
		break;
		
		case N_RBX : 
		fprintf(txtFile, "%d\n", N_RBX);
		fprintf(asmFile, "rbx\n");
		break;

		case N_RCX : 
		fprintf(txtFile, "%d\n", N_RCX);
		fprintf(asmFile, "rcx\n");
		break;

		case N_RDX : 
		fprintf(txtFile, "%d\n", N_RDX);
		fprintf(asmFile, "rdx\n");
		break;

		default : assert(0);
	}

	m_index += 2;
}


void  MyDisassembler::parsePop(FILE *txtFile, FILE *asmFile)
{
	fprintf(txtFile, "%d\n", N_POP);
	fprintf(asmFile, "pop\n");

	m_index++;
}


void MyDisassembler::parsePopR(FILE *txtFile, FILE *asmFile)
{
	fprintf(txtFile, "%d ", N_POP_R);
	fprintf(asmFile, "pop ");
	switch(m_buf[m_index+1])
	{
		case N_RAX : 
		fprintf(txtFile, "%d\n", N_RAX);
		fprintf(asmFile, "rax\n");
		break;
		
		case N_RBX : 
		fprintf(txtFile, "%d\n", N_RBX);
		fprintf(asmFile, "rbx\n");
		break;

		case N_RCX : 
		fprintf(txtFile, "%d\n", N_RCX);
		fprintf(asmFile, "rcx\n");
		break;

		case N_RDX : 
		fprintf(txtFile, "%d\n", N_RDX);
		fprintf(asmFile, "rdx\n");
		break;

		default : assert(0);
	}

	m_index += 2;
}


void  MyDisassembler::parseAdd(FILE *txtFile, FILE *asmFile)
{
	fprintf(txtFile, "%d\n", N_ADD);
	fprintf(asmFile, "add\n");

	m_index++;
}


void  MyDisassembler::parseSub(FILE *txtFile, FILE *asmFile)
{
	fprintf(txtFile, "%d\n", N_SUB);
	fprintf(asmFile, "sub\n");

	m_index++;
}


void  MyDisassembler::parseMul(FILE *txtFile, FILE *asmFile)
{
	fprintf(txtFile, "%d\n", N_MUL);
	fprintf(asmFile, "mul\n");

	m_index++;
}


void  MyDisassembler::parseDiv(FILE *txtFile, FILE *asmFile)
{
	fprintf(txtFile, "%d\n", N_DIV);
	fprintf(asmFile, "div\n");

	m_index++;
}


void  MyDisassembler::parseSin(FILE *txtFile, FILE *asmFile)
{
	fprintf(txtFile, "%d\n", N_SIN);
	fprintf(asmFile, "sin\n");

	m_index++;
}


void  MyDisassembler::parseCos(FILE *txtFile, FILE *asmFile)
{
	fprintf(txtFile, "%d\n", N_COS);
	fprintf(asmFile, "cos\n");

	m_index++;
}


void  MyDisassembler::parseSqrt(FILE *txtFile, FILE *asmFile)
{
	fprintf(txtFile, "%d\n", N_SQRT);
	fprintf(asmFile, "sqrt\n");

	m_index++;
}


void  MyDisassembler::parseIn(FILE *txtFile, FILE *asmFile)
{
	fprintf(txtFile, "%d\n", N_IN);
	fprintf(asmFile, "in\n");

	m_index++;
}


void  MyDisassembler::parseOut(FILE *txtFile, FILE *asmFile)
{
	fprintf(txtFile, "%d\n", N_OUT);
	fprintf(asmFile, "out\n");

	m_index++;
}


void  MyDisassembler::parseEnd(FILE *txtFile, FILE *asmFile)
{
	fprintf(txtFile, "%d\n", N_END);
	fprintf(asmFile, "end\n");

	m_index++;
}
