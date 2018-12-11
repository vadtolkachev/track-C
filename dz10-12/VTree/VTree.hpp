#pragma once
#include "VTreeNode.hpp"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


#define CHECKERR() if(checkErr != SUCCESS) return checkErr


class VTree
{
public:
	VTree();
	~VTree();

	VTreeNode *getRoot() const;
	int checkError() const;
	int createRoot();
	int setRoot(VTreeNode *node);
	int copy(VTree *tree);
	int copyNode(VTreeNode *nodeFrom, VTreeNode *nodeTo);
	int derivate();
	
	void dump(const char *file_name);
	void dumpNode(const VTreeNode *node, FILE *dotfile);

	void pdump(const char *file_name);
	void pdumpNode(const VTreeNode *node, FILE *dotfile);

	void tdump(const char *file_name);
	void tdumpNode(FILE *file, const VTreeNode *node);

	void parseTree(const char *file_name);

	void freeMem(VTreeNode *node);

private:
	VTreeNode *m_root;
	int m_error;
};
