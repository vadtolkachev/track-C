#pragma once
#include "MyElement.hpp"
#include <new>


const int ALLOC_ERR = -2;
const int NULLPTR_ERR = -1;
const int EMPTY_ERR = 0;
const int SUCCESS = 1;


class MyStack
{
public:
	MyStack();
	~MyStack();

	MyElement *getHead() const;
	int getTop(data_t *res) const;
	int getCapacity() const;
	int push(data_t data);
	int pop();

	bool isEmpty() const;
	
private:
	MyElement *m_head;
	int m_capacity;
};