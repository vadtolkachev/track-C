#pragma once
#include <string.h>
#include <new>
#include "defines.hpp"


class VTreeNode
{
public:
	VTreeNode();
	~VTreeNode();

	char *getStr() const;
	VTreeNode *getLeft() const;
	VTreeNode *getRight() const;

	int createLeft();
	int createRight();
	
	void setStr(const char *str);

private:
	char *m_str;
	VTreeNode *m_left;
	VTreeNode *m_right;
};