#pragma once

typedef int data_t;


class MyElement
{
public:
	MyElement(data_t data, MyElement *next);

	data_t getData() const;
	MyElement *getNext() const;
	
private:
	data_t m_data;
	MyElement *m_next;
};