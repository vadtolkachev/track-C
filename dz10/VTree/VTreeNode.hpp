#pragma once
#include "defines.hpp"
#include <string.h>
#include <new>
#include <stdio.h>


enum VType : unsigned char
{
	VSign,
	VVar,
	VNumb
};


class VTreeNode
{
public:
	VTreeNode();

	VType getType() const;
	double getDouble() const;
	char getChar() const;
	VTreeNode *getLeft() const;
	VTreeNode *getRight() const;

	int createLeft();
	int createRight();
	int setChar(const char &c);
	int fprintData(FILE *file) const;
	void setDouble(const double &numb);

private:
	VType m_type;
	double m_data;
	VTreeNode *m_left;
	VTreeNode *m_right;
};