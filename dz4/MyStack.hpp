#pragma once
#include "defines.hpp"
#include <new>
#include <stdlib.h>
#include <cstdint>
#include <iostream>
#include <assert.h>


class MyStack
{
public:
	MyStack();
	~MyStack();

	int checkFirstCanary() const;
	int checkSecondCanary() const;
	int checkThirdCanary() const;
	int checkFourthCanary() const;
	int checkSize() const;
	int checkCapacity() const;
	int checkPoison(data_t *data) const;
	int checkSum1(long *ref) const;
	int checkSum2(long *ref) const;
	int checkNullptr() const;

	int checkStack(data_t *data, long *ref) const;
	int checkStack_print(const char *file, int line, const char *func) const;

	int getTop(data_t *res) const;
	int getSize() const;
	int getCapacity() const;

	int push(data_t data);
	int pop();

	bool isEmpty() const;

	void printStack() const;
	void dumpStack() const;
	void printStackErr(const char *nErr, const char *file, int line, const char *func, int what, int format) const;
	void printStackErr(const char *nErr, const char *file, int line, const char *func, long what, int format) const;
	
	void calcSum1();
	void calcSum2();
	
private:
	long m_canary1;

	long m_sum1;
	long m_sum2;

	int m_size;
	int m_capacity;	
	data_t *m_stack;

	long m_canary2;
};