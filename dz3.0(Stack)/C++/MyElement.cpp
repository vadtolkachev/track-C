#include "MyElement.hpp"


MyElement::MyElement(data_t data, MyElement *next)
{
	m_data = data;
	m_next = next;
}


data_t MyElement::getData() const
{
	return m_data;
}


MyElement *MyElement::getNext() const
{
	return m_next;
}