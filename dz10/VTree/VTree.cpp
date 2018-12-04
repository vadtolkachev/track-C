#include "VTree.hpp"
#include "VTreeParser.hpp"


VTree::VTree()
{
	m_root = nullptr;
	m_error = SUCCESS;
}


VTree::~VTree()
{
	freeMem(m_root);
}


VTreeNode *VTree::getRoot() const
{
	return m_root;
}


int VTree::checkError() const
{
	return m_error;
}


int VTree::createRoot()
{
	if(m_root)
		return OVERFLOW_ERR;

	m_root = new (std::nothrow) VTreeNode();
	
	if(!m_root)
		return ALLOC_ERR;

	return SUCCESS;
}


int VTree::setRoot(VTreeNode *node)
{
	if(m_root)
		return OVERFLOW_ERR;

	m_root = node;
	return SUCCESS;
}


void VTree::dump(const char *file_name)
{
	if(!file_name)
	{
		m_error = NULLPTR_ERR;
		return;
	}

	FILE *dotfile = fopen(file_name, "w");
	if(errno)
	{
		m_error = OPEN_ERR;
		return;
	}

	fprintf(dotfile, "digraph G\n{\n");
	dumpNode(m_root, dotfile);
	fprintf(dotfile, "}");

	char str[512] = "";
	sprintf(str, "dot -T jpg -o %s.jpg %s &", file_name, file_name);
	system(str);

	fclose(dotfile);
	if(errno)
	{
		m_error = CLOSE_ERR;
		return;
	}
}


void VTree::dumpNode(const VTreeNode *node, FILE *dotfile)
{
	if(node)
	{
		fprintf(dotfile, "\t\"");
		node->fprintData(dotfile);
		fprintf(dotfile, "\"\n");
		if(node->getLeft())
		{
			fprintf(dotfile, "\t\"");
			node->fprintData(dotfile);
			fprintf(dotfile, "\"->\"");
			node->getLeft()->fprintData(dotfile);
			fprintf(dotfile, "\"\n");
		}
		if(node->getRight())
		{
			fprintf(dotfile, "\t\"");
			node->fprintData(dotfile);
			fprintf(dotfile, "\"->\"");
			node->getRight()->fprintData(dotfile);
			fprintf(dotfile, "\"\n");
		}

		dumpNode(node->getLeft(), dotfile);
		dumpNode(node->getRight(), dotfile);
	}
}


void VTree::pdump(const char *file_name)
{	
	if(!file_name)
	{
		m_error = NULLPTR_ERR;
		return;
	}

	FILE *dotfile = fopen(file_name, "w");
	if(errno)
	{
		m_error = OPEN_ERR;
		return;
	}

	fprintf(dotfile, "digraph G\n{\n");
	pdumpNode(m_root, dotfile);
	fprintf(dotfile, "}");

	char str[512] = "";
	sprintf(str, "dot -T jpg -o %s.jpg %s &", file_name, file_name);
	system(str);

	fclose(dotfile);
	if(errno)
	{
		m_error = CLOSE_ERR;
		return;
	}
}


void VTree::pdumpNode(const VTreeNode *node, FILE *dotfile)
{
	if(node)
	{
		fprintf(dotfile, "\t\"");
		node->fprintData(dotfile);		
		fprintf(dotfile, " [%p]\"\n", node);
		if(node->getLeft())
		{
			fprintf(dotfile, "\t\"");
			node->fprintData(dotfile);
			fprintf(dotfile, " [%p]\"->\"", node);
			node->getLeft()->fprintData(dotfile);
			fprintf(dotfile, " [%p]\"\n", node->getLeft());
		}
		if(node->getRight())
		{
			fprintf(dotfile, "\t\"");
			node->fprintData(dotfile);
			fprintf(dotfile, " [%p]\"->\"", node);
			node->getRight()->fprintData(dotfile);
			fprintf(dotfile, " [%p]\"\n", node->getRight());
		}

		pdumpNode(node->getLeft(), dotfile);
		pdumpNode(node->getRight(), dotfile);
	}
}


void VTree::tdump(const char *file_name)
{
	if(!file_name)
	{
		m_error = NULLPTR_ERR;
		return;
	}

	FILE *file = fopen(file_name, "w");
	if(errno)
	{
		m_error = OPEN_ERR;
		return;
	}

	tdumpNode(file, m_root);

	fclose(file);
	if(errno)
	{
		m_error = CLOSE_ERR;
		return;
	}
}


void VTree::tdumpNode(FILE *file, const VTreeNode *node)
{
	if(!node)
	{
		fprintf(file, "(nil)\n");
		return;
	}
	

	if(node->getLeft() || node->getRight())
	{
		fprintf(file, "(");
		tdumpNode(file, node->getLeft());
		node->fprintData(file);
		tdumpNode(file, node->getRight());
		fprintf(file, ")");
	}
	else
		node->fprintData(file);
}



void VTree::parseTree(const char *file_name)
{	
	VTreeParser parser;
	int checkErr = parser.parseTree(file_name, this);
	m_error = checkErr;
}


void VTree::freeMem(VTreeNode *node)
{
	if(node)
	{
		freeMem(node->getLeft());
		freeMem(node->getRight());
		delete node;
	}
}
