#include "MyAssembler.hpp"


int MyAssembler::assemble(FILE *asmFile, FILE *txtFile, FILE *binFile)
{
	if((!asmFile) || (!txtFile) || (!binFile))
	{
		assert(0);
		return NULLPTR_ERR;
	}

	char *check;

	m_errno = SUCCESS;
	while((check = fgets(m_buf, ASM_BUF_SIZE, asmFile), check != nullptr))
	{
		parsePush(txtFile, binFile);
		parsePop(txtFile, binFile);
		parseAdd(txtFile, binFile);
		parseSub(txtFile, binFile);
		parseMul(txtFile, binFile);
		parseDiv(txtFile, binFile);
		parseSin(txtFile, binFile);
		parseCos(txtFile, binFile);
		parseSqrt(txtFile, binFile);
		parseIn(txtFile, binFile);
		parseOut(txtFile, binFile);
		parseEnd(txtFile, binFile);

		if(m_errno != SUCCESS)
		{
			assert(0);
			return m_errno;
		}
	}

	return SUCCESS;
}


void MyAssembler::parsePush(FILE *txtFile, FILE *binFile)
{	
	if(strncmp("push", m_buf, 4) == 0)
	{
		double d;
		char* pPosition = strchr(m_buf, '\n');
		if(pPosition == nullptr)
			assert(pPosition != nullptr);

		if((isdigit(m_buf[5])) || (m_buf[5] == '-'))
		{
			d = strtod(&m_buf[5], &pPosition);

			if((errno != 0) || (pPosition == &m_buf[5]) || (*pPosition != '\n'))
			{
				printf("pPos = %c = %d\n", *pPosition, *pPosition);
				m_errno = PARSE_ERR;
				assert(0);
				return;
			}

			char *tmp = (char *)&d;			
			fprintf(txtFile, "%d %lg\n", N_PUSH, d);
			fprintf(binFile, "%c", N_PUSH);
			for(int i = 0; i < (int)sizeof(double); i++)
				fprintf(binFile, "%c", tmp[i]);
		}
		else if(m_buf[5] == 'r')
		{
			if((m_buf[7] != 'x') || (m_buf[8] != '\n'))
				assert(0);			

			if((m_buf[6] != 'a') && (m_buf[6] != 'b') && (m_buf[6] != 'c') && (m_buf[6] != 'd'))
				assert(0);

			char nReg;

			if(m_buf[6] == 'a')
				nReg = N_RAX;
			if(m_buf[6] == 'b')
				nReg = N_RBX;
			if(m_buf[6] == 'c')
				nReg = N_RCX;
			if(m_buf[6] == 'd')
				nReg = N_RDX;

			fprintf(txtFile, "%d %d\n", N_PUSH_R, nReg);
			fprintf(binFile, "%c%c", N_PUSH_R, nReg);
		}
		else
		{
			printf("%spush error%s\n", RED, NORM);
			m_errno = PARSE_ERR;
			assert(0);
		}
	}
}


void MyAssembler::parsePop(FILE *txtFile, FILE *binFile)
{
	if(strncmp("pop", m_buf, 3) == 0)
	{
		if(m_buf[3] == '\n')
		{
			fprintf(txtFile, "%d\n", N_POP);
			fprintf(binFile, "%c", N_POP);	
		}
		else if(m_buf[4] == 'r')
		{
			if((m_buf[6] != 'x') || (m_buf[7] != '\n'))
				assert(0);			

			if((m_buf[5] != 'a') && (m_buf[5] != 'b') && (m_buf[5] != 'c') && (m_buf[5] != 'd'))
				assert(0);

			char nReg;

			if(m_buf[5] == 'a')
				nReg = N_RAX;
			if(m_buf[5] == 'b')
				nReg = N_RBX;
			if(m_buf[5] == 'c')
				nReg = N_RCX;
			if(m_buf[5] == 'd')
				nReg = N_RDX;

			fprintf(txtFile, "%d %d\n", N_POP_R, nReg);
			fprintf(binFile, "%c%c", N_POP_R, nReg);
			
		}
		else
		{
			printf("%spop error%s\n", RED, NORM);
			assert(0);
			m_errno = PARSE_ERR;
		}
	}
}


void MyAssembler::parseAdd(FILE *txtFile, FILE *binFile)
{
	if(strncmp("add", m_buf, 3) == 0)
	{
		if(m_buf[3] != '\n')
		{
			assert(0);
			m_errno = PARSE_ERR;
		}

		fprintf(txtFile, "%d\n", N_ADD);
		fprintf(binFile, "%c", N_ADD);		
	}
}


void MyAssembler::parseSub(FILE *txtFile, FILE *binFile)
{
	if(strncmp("sub", m_buf, 3) == 0)
	{
		if(m_buf[3] != '\n')
		{
			assert(0);
			m_errno = PARSE_ERR;
		}

		fprintf(txtFile, "%d\n", N_SUB);
		fprintf(binFile, "%c", N_SUB);		
	}
}


void MyAssembler::parseMul(FILE *txtFile, FILE *binFile)
{
	if(strncmp("mul", m_buf, 3) == 0)
	{
		if(m_buf[3] != '\n')
		{
			assert(0);
			m_errno = PARSE_ERR;
		}

		fprintf(txtFile, "%d\n", N_MUL);
		fprintf(binFile, "%c", N_MUL);		
	}
}


void MyAssembler::parseDiv(FILE *txtFile, FILE *binFile)
{
	if(strncmp("div", m_buf, 3) == 0)
	{
		if(m_buf[3] != '\n')
		{
			assert(0);
			m_errno = PARSE_ERR;
		}

		fprintf(txtFile, "%d\n", N_DIV);
		fprintf(binFile, "%c", N_DIV);		
	}
}


void MyAssembler::parseSin(FILE *txtFile, FILE *binFile)
{
	if(strncmp("sin", m_buf, 3) == 0)
	{
		if(m_buf[3] != '\n')
		{
			assert(0);
			m_errno = PARSE_ERR;
		}

		fprintf(txtFile, "%d\n", N_SIN);
		fprintf(binFile, "%c", N_SIN);		
	}
}


void MyAssembler::parseCos(FILE *txtFile, FILE *binFile)
{
	if(strncmp("cos", m_buf, 3) == 0)
	{
		if(m_buf[3] != '\n')
		{
			assert(0);
			m_errno = PARSE_ERR;
		}

		fprintf(txtFile, "%d\n", N_COS);
		fprintf(binFile, "%c", N_COS);		
	}
}


void MyAssembler::parseSqrt(FILE *txtFile, FILE *binFile)
{
	if(strncmp("sqrt", m_buf, 4) == 0)
	{
		if(m_buf[4] != '\n')
		{
			assert(0);
			m_errno = PARSE_ERR;
		}

		fprintf(txtFile, "%d\n", N_SQRT);
		fprintf(binFile, "%c", N_SQRT);		
	}
}


void MyAssembler::parseIn(FILE *txtFile, FILE *binFile)
{
	if(strncmp("in", m_buf, 2) == 0)
	{
		if(m_buf[2] != '\n')
		{
			assert(0);
			m_errno = PARSE_ERR;
		}

		fprintf(txtFile, "%d\n", N_IN);
		fprintf(binFile, "%c", N_IN);		
	}
}


void MyAssembler::parseOut(FILE *txtFile, FILE *binFile)
{
	if(strncmp("out", m_buf, 3) == 0)
	{
		if(m_buf[3] != '\n')
		{
			assert(0);
			m_errno = PARSE_ERR;
		}

		fprintf(txtFile, "%d\n", N_OUT);
		fprintf(binFile, "%c", N_OUT);		
	}
}


void MyAssembler::parseEnd(FILE *txtFile, FILE *binFile)
{
	if(strncmp("end", m_buf, 3) == 0)
	{
		if(m_buf[3] != '\n')
		{
			assert(0);
			m_errno = PARSE_ERR;
		}

		fprintf(txtFile, "%d\n", N_END);
		fprintf(binFile, "%c", N_END);		
	}
}

