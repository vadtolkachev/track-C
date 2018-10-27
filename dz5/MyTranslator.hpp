#pragma once
#include "defines.hpp"
#include <stdio.h>


enum TrFormat
{
	INT_F,
	DOUBLE_F
};


class MyTranslator
{
public:
	int translate(FILE *asmFile, FILE *txtFile, FILE *binFile, TrFormat format);
	int parseInt(char *asm_code, FILE *txtFile, FILE *binFile);
	int readInt(char *str, int *res, int *numb);

};