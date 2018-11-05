#pragma once
#define S_DEBUG
#include "../../dz4/MyStack.hpp"
#include "../../dz4/defines.hpp"
#include "AsmCommands.hpp"
#include <math.h>
#include <sys/stat.h>


class MyProcessor
{
public:
	MyProcessor();
	~MyProcessor();

	int readFile(FILE *file, char **str, long int *pSize);
	int proc_exec(FILE *binFile);

	int push(data_t data);
	int pushR(char nReg);
	int pop(data_t *data);
	int popR(char nReg);
	int add();
	int sub();
	int mul();
	int div();
	int pr_sin();
	int pr_cos();
	int pr_sqrt();
	int in();
	int out();

	int solveSquare();

	void getDumpFileName(char str[45]) const;
	void dumpProc(const char *str) const;


private:
	MyStack m_stack;
	char *m_code;
	char *m_RAM;
	long int m_ramSize;
	unsigned m_index;
	int m_errno;
	FILE *m_dumpFile;

	data_t m_rax;
	data_t m_rbx;
	data_t m_rcx;
	data_t m_rdx;
};