#include "MyStack.hpp"


MyStack::MyStack()
{
	m_capacity = 0;
	m_head = nullptr;
}


MyStack::~MyStack()
{
	while(m_capacity != 0)
		pop();
}


MyElement *MyStack::getHead() const
{
	return m_head;
}


int MyStack::getTop(data_t *res) const
{
	if(res == nullptr)
		return -1;
	
	if(getHead() == nullptr)
		return 0;

	*res = getHead()->getData();
	return 1;
}


int MyStack::getCapacity() const
{
	return m_capacity;
}


int MyStack::push(data_t data)
{
	MyElement *element = new (std::nothrow) MyElement(data, m_head);
	if(!element)
		return -1;
	
	m_head = element;
	m_capacity++;
	
	return 1;
}


int MyStack::pop()
{
	if(m_capacity == 0)
		return 0;

	MyElement *tmp = m_head; 
	m_head = tmp->getNext();
	delete tmp;
	m_capacity--;	
	
	return 1;
}


bool MyStack::isEmpty() const
{
	if(getCapacity())
		return true;

	return false;
}