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


const int ASM_BUF_SIZE = 30;


class MyAssembler
{
public:
	int assemble(FILE *asmFile, FILE *txtFile, FILE *binFile);

	void parsePush(FILE *txtFile, FILE *binFile);
	void parsePop(FILE *txtFile, FILE *binFile);
	void parseAdd(FILE *txtFile, FILE *binFile);
	void parseSub(FILE *txtFile, FILE *binFile);
	void parseMul(FILE *txtFile, FILE *binFile);
	void parseDiv(FILE *txtFile, FILE *binFile);
	void parseSin(FILE *txtFile, FILE *binFile);
	void parseCos(FILE *txtFile, FILE *binFile);
	void parseSqrt(FILE *txtFile, FILE *binFile);
	void parseIn(FILE *txtFile, FILE *binFile);
	void parseOut(FILE *txtFile, FILE *binFile);
	void parseEnd(FILE *txtFile, FILE *binFile);

private:
	char m_buf[ASM_BUF_SIZE];
	int m_errno;	
};