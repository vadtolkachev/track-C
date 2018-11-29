#pragma once
#include "VTree.hpp"


class VAkinator
{
public:
	VAkinator(VTree *tree);
	VTree *getTree() const;

	int search();
	int search(VTreeNode *node);
	int create(VTreeNode *node);

private:
	VTree *m_tree;
};