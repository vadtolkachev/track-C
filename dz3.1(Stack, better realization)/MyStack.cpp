#include "MyStack.hpp"


MyStack::MyStack()
{
	m_stack = nullptr;
	m_size = 0;
	m_capacity = 0;
}


MyStack::~MyStack()
{
	free(m_stack);
}


int MyStack::getTop(data_t *res) const
{
	if(res == nullptr)
		return NULLPTR_ERR;
	
	if(!m_size)
		return EMPTY_ERR;

	*res = m_stack[m_size-1];
	return SUCCESS;
}


int MyStack::getSize() const
{
	return m_size;
}


int MyStack::getCapacity() const
{
	return m_capacity;
}


int MyStack::push(data_t data)
{
	if(m_capacity == m_size)
	{
		data_t *tmp;
		tmp = (data_t *) reallocarray(m_stack, m_capacity + BUF, sizeof(data_t));
		if(!tmp)
			return ALLOC_ERR;
		
		m_stack = tmp;		
		m_capacity += BUF;
		for(int i = m_size; i < m_capacity; i++)
			m_stack[i] = (data_t)POISON1;
	}
	
	m_stack[m_size++] = data;
	return SUCCESS;
}


int MyStack::pop()
{
	if(m_size == 0)
		return EMPTY_ERR;

	m_stack[--m_size] = POISON2;
	
	if(m_capacity == m_size + BUF)
	{
		data_t *tmp;
		tmp = (data_t *) reallocarray(m_stack, m_capacity - BUF, sizeof(data_t));
		if(!tmp)
			return ALLOC_ERR;

		m_stack = tmp;		
		m_capacity -= BUF;	
	
	}

	return SUCCESS;
}


bool MyStack::isEmpty() const
{
	if(m_size)
		return true;

	return false;
}