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
		return NOTNULLPTR_ERR;

	int checkErr = newTree->createRoot();
	CHECKERR();

	checkErr = derivateNode(oldTree->getRoot(), newTree->getRoot());
	
	return checkErr;
}


int VDerivator::derivateNode(VTreeNode *oldNode, VTreeNode *newNode)
{
	if(oldNode->getType() == VNumbType)
	{
		if(oldNode->getLeft() || oldNode->getRight())
			return NOTNULLPTR_ERR;

		newNode->setDouble(0);
	}

	if(oldNode->getType() == VVarType)
	{
		if(oldNode->getLeft() || oldNode->getRight())
			return NOTNULLPTR_ERR;

		newNode->setDouble(1);
	}

	int checkErr;

	if(oldNode->getType() == VFuncType)
	{
		if(!oldNode->getLeft())
			return NULLPTR_ERR;
		

		#define FUNC_DEF(name, str, numb, der_code)	\
		if(oldNode->getFunc() == F_##name) 		\
			der_code;

		FUNCS_DEF;

		#undef FUNC_DEF
	}


	return SUCCESS;
}

