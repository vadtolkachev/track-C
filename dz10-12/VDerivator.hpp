#pragma once
#include "VTree.hpp"


class VDerivator
{
public:
	int derivate(VTree *tree);
	int derivate(VTree *oldTree, VTree *newTree);
	int derivateNode(VTreeNode *oldNode, VTreeNode *newNode);

	VTree *getTree() const;
	void setTree(VTree *tree);

private:
	VTree *m_tree;
};