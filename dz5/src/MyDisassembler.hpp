#pragma once
#include "../../dz4/defines.hpp"
#include "AsmCommands.hpp"
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <cstring>
#include <assert.h>
#include <ctype.h>
#include <stdio.h>


class MyDisassembler
{
public:
	int readFile(FILE *file, char **str, long int *pSize);
	int disassemble(FILE *binFile, FILE *txtFile, FILE *asmFile);

private:
	char *m_buf;
	int m_index;
};