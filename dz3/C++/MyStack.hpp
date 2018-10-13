#pragma once
#include "MyElement.hpp"
#include <new>


class MyStack
{
public:
	MyStack();
	~MyStack();

	MyElement *getHead() const;
	int getCapacity() const;
	int push(data_t data);
	int pop();	
	
private:
	MyElement *m_head;
	int m_capacity;
};