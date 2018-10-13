#pragma once

typedef int data_t;


class MyElement
{
public:
	MyElement(data_t data, MyElement *next);

	data_t getData() const;
	MyElement *getNext() const;
	
	void setData(data_t data);
	void setNext(MyElement *next);
	
private:
	data_t m_data;
	MyElement *m_next;
};