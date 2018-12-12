#include "VTree.hpp"
#include "VTreeParser.hpp"
#include "VDerivator.hpp"


VTree::VTree()
{
	m_root = nullptr;
	m_error = SUCCESS;
}


VTree::~VTree()
{
	freeMem(m_root);
	m_root = nullptr;
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


int VTree::copy(VTree *tree)
{
	if(!tree)
		return NULLPTR_ERR;

	if(m_root)
		return OVERFLOW_ERR;

	if(tree->getRoot())
	{
		int checkErr = createRoot();
		CHECKERR();
		checkErr = m_root->copy(tree->getRoot());
		return checkErr;
	}

	return SUCCESS;
}


int VTree::derivate()
{
	VDerivator derivator;
	int checkErr = derivator.derivate(this);

	return checkErr;
}


int VTree::derivate(const char *file_name)
{
	VDerivator derivator;
	int checkErr = derivator.derivate(this, file_name);

	return checkErr;
}


int VTree::dumpTex(const char *file_name)
{
	if(!file_name)
		return NULLPTR_ERR;

	FILE *file = fopen(file_name, "w");
	if(errno)
		return OPEN_ERR;

	fprintf(file, "$");
	int checkErr = dumpNodeTex(file, m_root);
	CHECKERR();
	fprintf(file, "$");

	fclose(file);
	if(errno)
		return CLOSE_ERR;

	return SUCCESS;
}


int VTree::dumpNodeTex(FILE *file, const VTreeNode *node)
{
	if(!node)
		return SUCCESS;

	if(node->getType() == VNumbType)
	{
		if(node->getLeft() || node->getRight())
			return NOTNULLPTR_ERR;
		if(node->getDouble() < 0)
			fprintf(file, "(");
		node->fprintData(file);
		if(node->getDouble() < 0)
			fprintf(file, ")");
	}
	else if(node->getType() == VFuncType)
	{
		char func = node->getFunc();
		if(func == F_ADD || func == F_SUB)
		{
			if(node != m_root)
				fprintf(file, "(");

			if(node->getLeft())
				dumpNodeTex(file, node->getLeft());

			node->fprintData(file);

			if(node->getRight())
				dumpNodeTex(file, node->getRight());

			if(node != m_root)	
				fprintf(file, ")");
		}
		else if(func == F_LOG)
		{
			//TODO
			if(node != m_root)
				fprintf(file, "(");

			if(node->getLeft())
				dumpNodeTex(file, node->getLeft());

			fprintf(file, "(");
			node->fprintData(file);
			fprintf(file, ")");

			if(node->getRight())
				dumpNodeTex(file, node->getRight());

			if(node != m_root)	
				fprintf(file, ")");
		}
		else if(func == F_LN || func == F_SIN || func == F_COS || func == F_TG ||  func == F_CTG)
		{
			node->fprintData(file);

			fprintf(file, "(");
			if(node->getLeft())
				dumpNodeTex(file, node->getLeft());
			fprintf(file, ")");		
		}
		else if(func == F_MUL)
		{
			if(node->getLeft())
				dumpNodeTex(file, node->getLeft());

			if(func == F_MUL)
				fprintf(file, " \\cdot ");
			else
				node->fprintData(file);

			if(node->getRight())
				dumpNodeTex(file, node->getRight());
		}
		else if(func == F_POW)
		{
			if(node->getLeft()->getType() == VFuncType)
				fprintf(file, "(");

			if(node->getLeft())
				dumpNodeTex(file, node->getLeft());

			if(node->getLeft()->getType() == VFuncType)
				fprintf(file, ")");

			node->fprintData(file);

			fprintf(file, "{");
			if(node->getRight())
				dumpNodeTex(file, node->getRight());
			fprintf(file, "}");		
		}
		else if(func == F_EXP)
		{
			fprintf(file, "e^{");
			if(node->getLeft())
				dumpNodeTex(file, node->getLeft());
			fprintf(file, "}");		
		}
		else if(func == F_DIV)
		{
			fprintf(file, "\\frac{");			
			
			if(node->getLeft())
				dumpNodeTex(file, node->getLeft());

			fprintf(file, "}{");	
			if(node->getRight())
				dumpNodeTex(file, node->getRight());
			fprintf(file, "}");
		}
		else
		{
			node->fprintData(file);

			if(node->getLeft())
				dumpNodeTex(file, node->getLeft());
		}
	}
	else
	{
		if(node->getLeft())
			dumpNodeTex(file, node->getLeft());

		node->fprintData(file);

		if(node->getRight())
			dumpNodeTex(file, node->getRight());
	}


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
		fprintf(dotfile, "\t%ld [label = \"", (long int)node);
		node->fprintData(dotfile);
		fprintf(dotfile, "\"]\n");

		if(node->getLeft())
			fprintf(dotfile, "\t%ld->%ld\n", (long int)node, (long int)node->getLeft());
		if(node->getRight())
			fprintf(dotfile, "\t%ld->%ld\n", (long int)node, (long int)node->getRight());

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

	fprintf(dotfile, "digraph structs\n{\nnode [shape=record];\n");
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
		fprintf(dotfile, "\t%ld [label = \"{%p|{", (long int)node, node);
		node->fprintData(dotfile);
		fprintf(dotfile, "|");
		node->fprintType(dotfile);
		fprintf(dotfile, "}}\"];\n");

		if(node->getLeft())
			fprintf(dotfile, "\t%ld->%ld [label = \"left\"]\n", (long int)node, (long int)node->getLeft());
		if(node->getRight())
			fprintf(dotfile, "\t%ld->%ld [label = \"right\"]\n", (long int)node, (long int)node->getRight());

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
		fprintf(file, "(nil)");
		return;
	}
	
	fprintf(file, "(");

	if(node->getLeft() || node->getRight())
	{

		tdumpNode(file, node->getLeft());
		node->fprintData(file);
		tdumpNode(file, node->getRight());

	}
	else
		node->fprintData(file);
	
	fprintf(file, ")");
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
