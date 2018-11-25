#include "VTTree.hpp"
#include "../dz4/defines.hpp"
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>


VTTree::VTTree()
{
	m_root = nullptr;
	m_canary = T_CANARY;
	m_errno = SUCCESS;
}


VTTree::VTTree(FILE *file)
{
	m_root = nullptr;
	m_canary = T_CANARY;

	struct stat tmp;
	fstat(fileno(file), &tmp);
	long int size = tmp.st_size;

	char *bigString = (char *)calloc(size, sizeof(char));
	if((!errno) && (bigString == nullptr))
		errno = ENOMEM;
	
	int checkErr = fread(bigString, size, 1, file);
	if(checkErr != 1)
	{
		printf("size = %ld\n", size);
		printf("checkErr = %d\n", checkErr);
		m_errno = READ_ERR;
		
	}

	parseTree(file, &m_root);

	free(bigString);
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
	if(m_canary == T_CANARY)
		return checkNode(m_root);
	
	return false;
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
	dumpNode(m_root, dotfile);
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
	pdumpNode(m_root, dotfile);
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


void VTTree::tdump(FILE *file)
{
	tdumpNode(file, m_root);
}


void VTTree::tdumpNode(FILE *file, VTTreeNode *node)
{
	fprintf(file, "(");

	if(!node)
		fprintf(file, "nil");
	else
	{
		fprintf(file, "%d", node->getNumb());
		if(node->getLeft() || node->getRight())
		{
			tdumpNode(file, node->getLeft());
			tdumpNode(file, node->getRight());
		}
	}

	fprintf(file, ")");
}


//TODO
void VTTree::parseTree(FILE *file, VTTreeNode **node)
{
	if(!(*node))
		return;

}
