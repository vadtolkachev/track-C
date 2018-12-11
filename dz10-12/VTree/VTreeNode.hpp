#pragma once
#include "defines.hpp"
#include "FuncDef.hpp"
#include <string.h>
#include <new>
#include <stdio.h>


#define CHECKERR() if(checkErr != SUCCESS) return checkErr


enum VType : unsigned char
{
	VFuncType,
	VVarType,
	VNumbType
};


#define FUNC_DEF(name, str, numb, der_code) F_##name = numb,

enum VFunc : unsigned char
{
	FUNCS_DEF
};

#undef FUNC_DEF


class VTreeNode
{
public:
	VTreeNode();

	VType getType() const;
	VTreeNode *getLeft() const;
	VTreeNode *getRight() const;
	VFunc getFunc() const;
	double getDouble() const;
	char getChar() const;
	
	int createLeft();
	int createRight();
	int setChar(const char &c);
	int fprintData(FILE *file) const;
	int fprintType(FILE *file) const;
	int copy(VTreeNode *node);
	int copyNode(VTreeNode *nodeFrom, VTreeNode *nodeTo);

	void setFunc(VFunc func);
	void setDouble(const double &numb);

private:
	VType m_type;
	double m_data;
	VTreeNode *m_left;
	VTreeNode *m_right;
};