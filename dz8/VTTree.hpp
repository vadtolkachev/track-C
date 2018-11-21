#pragma once
#include "VTTreeNode.hpp"
#include <new>
#include <errno.h>
#include <assert.h>
#include <stdio.h>


const int T_CANARY = 0xDEADBEEF;


class VTTree
{
public:
	VTTree();
	~VTTree();

	VTTreeNode *getRoot() const;
	VTTreeNode *addNode(const int &numb, VTTreeNode **node);
	int push(const int &numb);

	bool isOK();
	bool checkNode(VTTreeNode *node);
	
	void freeMem(VTTreeNode *node);
	void dump(FILE *dotfile);
	void dumpNode(VTTreeNode *node, FILE *dotfile);

	void pdump(FILE *dotfile);
	void pdumpNode(VTTreeNode *node, FILE *dotfile);

	void tdump(FILE *file);
	void tdumpNode(FILE *file, VTTreeNode *node);

private:
	int m_canary;
	VTTreeNode *m_root;
};