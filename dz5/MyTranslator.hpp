#pragma once
#include "defines.hpp"
#include <stdio.h>


enum TrFormat
{
	INT_F,
	DOUBLE_F
};


enum rMode
{
	NUMB_R,
	REF_R
};


class MyTranslator
{
public:
	int translate(FILE *asmFile, FILE *txtFile, FILE *binFile, TrFormat format);
	int parseInt(char *asm_code, FILE *txtFile, FILE *binFile);
	int readInt(char *str, int *res, int *len);
	int parseText(char *asm_code, int *index, FILE *txtFile, FILE *binFile);
	int parsePush(char *asm_code, int *index, FILE *txtFile, FILE *binFile);
	int parsePop(char *asm_code, int *index, FILE *txtFile, FILE *binFile);
};