#include "VDerivator.hpp"


int VDerivator::derivate(VTree *tree)
{
	if(!tree || !tree->getRoot())
		return NULLPTR_ERR;

	VTree newTree;

	int checkErr = derivate(tree, &newTree);
	CHECKERR();

	tree->~VTree();
	checkErr = tree->copy(&newTree);
	CHECKERR();

	return SUCCESS;
}


int VDerivator::derivate(VTree *oldTree, VTree *newTree)
{
	if(!oldTree || !oldTree->getRoot() || !newTree)
		return NULLPTR_ERR;

	if(newTree->getRoot())
		return OVERFLOW_ERR;

	int checkErr = newTree->createRoot();
	CHECKERR();

	checkErr = derivateNode(oldTree->getRoot(), newTree->getRoot());
	
	return checkErr;
}


int VDerivator::derivateNode(VTreeNode *oldNode, VTreeNode *newNode)
{
	if(oldNode->getType() == VNumbType)
		newNode->setDouble(0);

	return SUCCESS;
}


VTree *VDerivator::getTree() const
{
	return m_tree;
}


void VDerivator::setTree(VTree *tree)
{
	m_tree = tree;
}