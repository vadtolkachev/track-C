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

	void parsePush(FILE *txtFile, FILE *asmFile);
	void parsePushR(FILE *txtFile, FILE *asmFile);
	void parsePop(FILE *txtFile, FILE *asmFile);
	void parsePopR(FILE *txtFile, FILE *asmFile);
	void parseAdd(FILE *txtFile, FILE *asmFile);
	void parseSub(FILE *txtFile, FILE *asmFile);
	void parseMul(FILE *txtFile, FILE *asmFile);
	void parseDiv(FILE *txtFile, FILE *asmFile);
	void parseSin(FILE *txtFile, FILE *asmFile);
	void parseCos(FILE *txtFile, FILE *asmFile);
	void parseSqrt(FILE *txtFile, FILE *asmFile);
	void parseIn(FILE *txtFile, FILE *asmFile);
	void parseOut(FILE *txtFile, FILE *asmFile);
	void parseEnd(FILE *txtFile, FILE *asmFile);


private:
	char *m_buf;
	unsigned m_index;
};