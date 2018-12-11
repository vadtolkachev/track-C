#include "VTreeParser.hpp"
#include <sys/stat.h>
#include <new>
#include <ctype.h>


VTreeParser::VTreeParser()
{
	m_buf = nullptr;
	m_size = 0;
	m_index = 0;
}


int VTreeParser::readText(FILE *file)
{
	if(!file)
		return NULLPTR_ERR;

	if(m_buf)
		return OVERFLOW_ERR;

	struct stat tmp;
	fstat(fileno(file), &tmp);
	long int size = tmp.st_size;

	char *bigString = new (std::nothrow) char[size + 1]();
	if(!bigString)
		return ALLOC_ERR;
	
	if(fread(bigString, size, 1, file) != 1)
		return READ_ERR;

	m_buf = bigString;
	m_size = size+1;
	
	return SUCCESS;
}



int VTreeParser::parseTree(const char *file_name, VTree *tree)
{
	if(!file_name)
		return NULLPTR_ERR;

	FILE *file = fopen(file_name, "r");
	if(errno)
		return OPEN_ERR;

	int checkErr = readText(file);
	CHECKERR();

	if(tree->getRoot())
		return OVERFLOW_ERR;

	checkErr = tree->createRoot();
	CHECKERR();

	checkErr = parseNode(tree->getRoot());
	CHECKERR();

	fclose(file);
	if(errno)
		return CLOSE_ERR;

	delete[] m_buf;
	m_buf = nullptr;
	m_size = 0;
	m_index = 0;

	return SUCCESS;
}


int VTreeParser::parseNode(VTreeNode *node)
{
	int checkErr;

	if(m_buf[m_index] != '(')
		return PARSE_ERR;
	m_index++;

	if(m_buf[m_index] == '(')
	{
		if(strncmp(&m_buf[m_index], "(nil)", 5))
		{
			checkErr = node->createLeft();
			CHECKERR();
			checkErr = parseNode(node->getLeft());
			CHECKERR();
		}
		else
			m_index += 5;

		checkErr = readNode(node);
		CHECKERR();

		if(strncmp(&m_buf[m_index], "(nil)", 5))
		{
			checkErr = node->createRight();
			CHECKERR();
			checkErr = parseNode(node->getRight());
			CHECKERR();
		}
		else
			m_index += 5;
	}
	else
	{
		checkErr = readNode(node);
		CHECKERR();
	}

	if(m_buf[m_index] != ')')
		return PARSE_ERR;
	m_index++;

	return SUCCESS;
}


int VTreeParser::readNode(VTreeNode *node)
{
	//printf("%c\n", m_buf[m_index]);
	if(((m_buf[m_index+1] == ')') || (m_buf[m_index+1] == '('))  && (m_buf[m_index] >= 'a') && (m_buf[m_index] <= 'z'))
	{
		node->setChar(m_buf[m_index]);
		m_index++;
		return SUCCESS;
	}

	if((isdigit(m_buf[m_index])) || (m_buf[m_index] == '-'))
	{
		int checkErr = readDouble(node);
		return checkErr;
	}

	#define FUNC_DEF(name, str, numb)				\
	/*printf("str = %s; strlen = %lu\n", #str, strlen(#str));*/	\
	if(!strncmp(&m_buf[m_index], #str, strlen(#str)))		\
	{								\
		node->setFunc(F_##name);				\
		m_index += strlen(#str);				\
		return SUCCESS;						\
	}

	FUNCS_DEF;

	#undef FUNC_DEF

	return PARSE_ERR;
}


int VTreeParser::readDouble(VTreeNode *node)
{
	double d;
	char *pPosition = strchr(&m_buf[m_index], '(');
	if(!pPosition)
	{
		pPosition = strchr(&m_buf[m_index], ')');
		if(!pPosition)
			return PARSE_ERR;
	}

	d = strtod(&m_buf[m_index], &pPosition);

	if((errno != 0) || (pPosition == &m_buf[m_index]) || ((*pPosition != '(') && (*pPosition != ')')))
	{
		printf("readNode error (double)\n");
		printf("&m_buf[m_index] = %p, pPosition = %p\n", &m_buf[m_index], pPosition);
		printf("pPos = %c = %d\n", *pPosition, *pPosition);
		return PARSE_ERR;
	}

	//printf("%lg\n", d);
	node->setDouble(d);

	int len = pPosition - &m_buf[m_index];
	//printf("len = %d\n", len);
	m_index += len;

	return SUCCESS;
}



