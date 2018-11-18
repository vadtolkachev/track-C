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

			#define CMD_DEF(name, str, num, asm_code, disasm_code, proc_code) \
			case N_##name : disasm_code; break;

			#include "CmdDef.hpp"

			#undef CMD_DEF
	
			default : return PARSE_ERR;
		}
	}

	free(m_buf);
	return SUCCESS;
}

