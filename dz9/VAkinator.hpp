#pragma once
#include "VTree.hpp"


class VAkinator
{
public:
	VAkinator(VTree *tree);
	VTree *getTree() const;

	int search(VTreeNode *node);

private:
	VTree *m_tree;
};