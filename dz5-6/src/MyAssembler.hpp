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
const int ASM_LABELS_SIZE = 30;
const int MAX_LABEL_LEN = 15;


struct AsmLabel
{
	int m_numb = -1;
	char m_name[MAX_LABEL_LEN] = "";
};


class MyAssembler
{
public:
	int assemble(FILE *asmFile, FILE *txtFile, FILE *binFile);
	void findLabel(FILE *txtFile, FILE *binFile, char *label, char n_command);

	int getNReg(int index, char *nReg);

private:
	char m_buf[ASM_BUF_SIZE];
	int m_errno;
	int m_index;
	AsmLabel m_labels[ASM_LABELS_SIZE];
};