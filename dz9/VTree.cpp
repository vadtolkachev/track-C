#include "VTree.hpp"
#include <stdlib.h>
#include <errno.h>


VTree::VTree(VTreeNode *root)
{
	m_root = root;
	m_error = SUCCESS;
}


VTreeNode *VTree::getRoot() const
{
	return m_root;
}


int VTree::checkError() const
{
	return m_error;
}


void VTree::setRoot(VTreeNode *node)
{
	m_root = node;
}


void VTree::dump(const char *str)
{
	if(!str)
	{
		m_error = NULLPTR_ERR;
		return;
	}

	FILE *dotfile = fopen(str, "w");
	if(errno != 0)
	{
		m_error = OPEN_ERR;
		return;
	}

	fprintf(dotfile, "digraph G\n{\n");
	dumpNode(m_root, dotfile);
	fprintf(dotfile, "}");

	system("dot -T jpg -o dumps/tree1.jpg dumps/tree1.dot &");

	fclose(dotfile);
	if(errno != 0)
	{
		m_error = CLOSE_ERR;
		return;
	}
}


void VTree::dumpNode(VTreeNode *node, FILE *dotfile)
{
	if(node)
	{
		fprintf(dotfile, "\t\"%s\"\n", node->m_str);
		if(node->m_left)
			fprintf(dotfile, "\t\"%s\"->\"%s\"\n", node->m_str, node->m_left->m_str);
		if(node->m_right)
			fprintf(dotfile, "\t\"%s\"->\"%s\"\n", node->m_str, node->m_right->m_str);

		dumpNode(node->m_left, dotfile);
		dumpNode(node->m_right, dotfile);
	}
}


void VTree::pdump(const char *str)
{	
	if(!str)
	{
		m_error = NULLPTR_ERR;
		return;
	}

	FILE *dotfile = fopen(str, "w");
	if(errno != 0)
	{
		m_error = OPEN_ERR;
		return;
	}

	fprintf(dotfile, "digraph G\n{\n");
	pdumpNode(m_root, dotfile);
	fprintf(dotfile, "}");

	system("dot -T jpg -o dumps/tree1.jpg dumps/tree1.dot &");

	fclose(dotfile);
	if(errno != 0)
	{
		m_error = CLOSE_ERR;
		return;
	}
}


void VTree::pdumpNode(VTreeNode *node, FILE *dotfile)
{
	if(node)
	{
		fprintf(dotfile, "\t\"%s [%p]\"\n", node->m_str, node);
		if(node->m_left)
			fprintf(dotfile, "\t\"%s [%p]\"->\"%s [%p]\"\n", node->m_str, node, node->m_left->m_str, node->m_left);
		if(node->m_right)
			fprintf(dotfile, "\t\"%s [%p]\"->\"%s [%p]\"\n", node->m_str, node, node->m_right->m_str, node->m_right);

		pdumpNode(node->m_left, dotfile);
		pdumpNode(node->m_right, dotfile);
	}
}


void VTree::tdump(const char *str)
{
	if(!str)
	{
		m_error = NULLPTR_ERR;
		return;
	}

	FILE *file = fopen(str, "w");
	if(errno != 0)
	{
		m_error = OPEN_ERR;
		return;
	}

	tdumpNode(file, m_root);

	fclose(file);
	if(errno != 0)
	{
		m_error = CLOSE_ERR;
		return;
	}
}


void VTree::tdumpNode(FILE *file, VTreeNode *node)
{
	static int indent = -1; indent++;
	fprintf(file, "%*s{", indent*4, "");
	
	if(!node)
		fprintf(file, "nil");
	else
	{
		fprintf(file, "%s\n", node->m_str);
		if(node->m_left || node->m_right)
		{
			tdumpNode(file, node->m_left);
			tdumpNode(file, node->m_right);
		}
	}

	fprintf(file, "%*s}\n", indent*4, "");
	indent--;
}

/*
void VTree::parseTree(FILE *file, VTreeNode **node)
{
	if(!(*node))
		return;

}
*/