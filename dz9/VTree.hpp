#pragma once
#include "../dz4/defines.hpp"
#include <assert.h>
#include <stdio.h>


struct VTreeNode
{	
	char *m_str = nullptr;
	VTreeNode *m_left = nullptr;
	VTreeNode *m_right = nullptr;
};


class VTree
{
public:
	VTree(VTreeNode *root);

	VTreeNode *getRoot() const;
	int checkError() const;

	void setRoot(VTreeNode *node);
	
	void dump(const char *str);
	void dumpNode(VTreeNode *node, FILE *dotfile);

	void pdump(const char *str);
	void pdumpNode(VTreeNode *node, FILE *dotfile);

	void tdump(const char *str);
	void tdumpNode(FILE *file, VTreeNode *node);

	void parseTree(FILE *file, VTreeNode **node);

private:
	VTreeNode *m_root;
	int m_error;
};