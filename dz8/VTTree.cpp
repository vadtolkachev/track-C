#include "VTTree.hpp"
#include <stdio.h>


VTTree::VTTree()
{
	m_root = nullptr;
	m_canary = T_CANARY;
}


VTTree::~VTTree()
{
	freeMem(m_root);
}


VTTreeNode *VTTree::getRoot() const
{
	return m_root;
}


VTTreeNode *VTTree::addNode(const int &numb, VTTreeNode **node)
{
	VTTreeNode *tmp;
	if(!*node)
	{
		tmp = new (std::nothrow) VTTreeNode(numb);
		if(!tmp && !errno)
			errno = ENOMEM;
		*node = tmp;
	}
	else
	{
		if (numb < (*node)->getNumb())
		{
			tmp = (*node)->getLeft();
			(*node)->setLeft(addNode(numb, &tmp));
		}
		else
		{
			tmp = (*node)->getRight();
			(*node)->setRight(addNode(numb, &tmp));
		}
	}
	return(*node);
}


int VTTree::push(const int &numb)
{
	addNode(numb, &m_root);
	assert(!errno);
	return errno;
}


bool VTTree::isOK()
{
	return checkNode(m_root);
}


bool VTTree::checkNode(VTTreeNode *node)
{
	if(!node)
		return true;
	
	if((node->getLeft()) && (node->getNumb() < node->getLeft()->getNumb()))
		return false;

	if((node->getRight()) && (node->getNumb() > node->getRight()->getNumb()))
		return false;

	if(!checkNode(node->getLeft()) || !checkNode(node->getRight()))
		return false;

	return true;
}


void VTTree::freeMem(VTTreeNode *node)
{
	if (node)
	{
		freeMem(node->getLeft());
		freeMem(node->getRight());
		delete node;
	}
}


void VTTree::dump(FILE *dotfile)
{
	fprintf(dotfile, "digraph G\n{\n");
	puts("1");
	pdumpNode(m_root, dotfile);
	fprintf(dotfile, "}");
}


void VTTree::dumpNode(VTTreeNode *node, FILE *dotfile)
{
	if(node)
	{
		fprintf(dotfile, "\t%d\n", node->getNumb());
		if(node->getLeft())
			fprintf(dotfile, "\t%d->%d\n", node->getNumb(), node->getLeft()->getNumb());
		if(node->getRight())
			fprintf(dotfile, "\t%d->%d\n", node->getNumb(), node->getRight()->getNumb());

		dumpNode(node->getLeft(), dotfile);
		dumpNode(node->getRight(), dotfile);
	}
}


void VTTree::pdump(FILE *dotfile)
{
	fprintf(dotfile, "digraph G\n{\n");
	puts("1");
	dumpNode(m_root, dotfile);
	fprintf(dotfile, "}");
}


void VTTree::pdumpNode(VTTreeNode *node, FILE *dotfile)
{
	if(node)
	{
		fprintf(dotfile, "\t\"%d [%p]\"\n", node->getNumb(), node);
		if(node->getLeft())
			fprintf(dotfile, "\t\"%d [%p]\"->\"%d [%p]\"\n", node->getNumb(), node, node->getLeft()->getNumb(), node->getLeft());
		if(node->getRight())
			fprintf(dotfile, "\t\"%d [%p]\"->\"%d [%p]\"\n", node->getNumb(), node, node->getRight()->getNumb(), node->getRight());

		pdumpNode(node->getLeft(), dotfile);
		pdumpNode(node->getRight(), dotfile);
	}
}
