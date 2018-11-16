#pragma once
#include <new>
#include <stdlib.h>


typedef int data_t;

const int ALLOC_ERR = -2;
const int NULLPTR_ERR = -1;
const int EMPTY_ERR = 0;
const int SUCCESS = 1;

const int BUF = 2;
const int POISON1 = 666;
const int POISON2 = 667;
//const int POISON3 = 668;


class MyStack
{
public:
	MyStack();
	~MyStack();

	int getTop(data_t *res) const;
	int getSize() const;
	int getCapacity() const;

	int push(data_t data);
	int pop();

	bool isEmpty() const;
	
private:
	data_t *m_stack;
	int m_size;
	int m_capacity;
};