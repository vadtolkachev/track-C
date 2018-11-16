#pragma once
#define S_DEBUG
#include "../../dz4/MyStack.hpp"
#include "../../dz4/defines.hpp"
#include "AsmCommands.hpp"
#include <math.h>
#include <sys/stat.h>


const long int RAM_SIZE = 10;


class MyProcessor
{
public:
	MyProcessor();
	~MyProcessor();

	int readFile(FILE *file, char **str, long int *pSize);
	int proc_exec(FILE *binFile);

	void getDumpFileName(char str[45]) const;
	void dumpProc(const char *str) const;


private:
	MyStack m_stack;
	MyStack m_retStack;
	char *m_code;
	double m_RAM[RAM_SIZE];
	long int m_ramSize;
	unsigned m_index;
	int m_errno;
	FILE *m_dumpFile;

	data_t m_rax;
	data_t m_rbx;
	data_t m_rcx;
	data_t m_rdx;
	data_t m_rex;
};