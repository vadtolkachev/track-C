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
		fprintf(dotfile, "\t\"%s\"\n", node->getStr());
		if(node->getLeft())
			fprintf(dotfile, "\t\"%s\"->\"%s\"[label = \"yes\"]\n", node->getStr(), node->getLeft()->getStr());
		if(node->getRight())
			fprintf(dotfile, "\t\"%s\"->\"%s\"[label = \"no\"]\n", node->getStr(), node->getRight()->getStr());

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
		fprintf(dotfile, "\t\"%s [%p]\"\n", node->getStr(), node);
		if(node->getLeft())
			fprintf(dotfile, "\t\"%s [%p]\"->\"%s [%p]\"\n", node->getStr(), node, node->getLeft()->getStr(), node->getLeft());
		if(node->getRight())
			fprintf(dotfile, "\t\"%s [%p]\"->\"%s [%p]\"\n", node->getStr(), node, node->getRight()->getStr(), node->getRight());

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
	static int indent = -1; indent++;
	fprintf(file, "%*s{", indent*4, "");
	
	if(!node)
		fprintf(file, "(nil)\n");
	else
	{
		fprintf(file, "%s\n", node->getStr());
		if(node->getLeft() || node->getRight())
		{
			tdumpNode(file, node->getLeft());
			tdumpNode(file, node->getRight());
		}
	}

	fprintf(file, "%*s}\n", indent*4, "");
	indent--;
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