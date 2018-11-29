#include "VTreeParser.hpp"


int VTreeParser::parseTree(const char *file_name, VTree *tree)
{
	if(!file_name)
		return NULLPTR_ERR;

	FILE *file = fopen(file_name, "r");
	if(errno)
		return OPEN_ERR;

	char *check = fgets(m_buf, PARSER_BUF_SIZE, file);
	if(!check)
		return EMPTY_ERR;

	if(tree->getRoot())
		return OVERFLOW_ERR;

	tree->createRoot();

	int checkErr = parseNode(file, tree->getRoot());
	
	fclose(file);
	if(errno)
		return CLOSE_ERR;

	return checkErr;
}


int VTreeParser::parseNode(FILE *file, VTreeNode *node)
{
	char *pEnd;
	int checkErr = checkEndl(&pEnd);
	if(checkErr != SUCCESS) 
		return checkErr;

	char *pPosition = strchr(m_buf, '{');
	if(pPosition)
	{
		*pEnd = 0;
		checkErr = node->setStr(pPosition+1);
		if(checkErr != SUCCESS)
			return checkErr;

		readFile(file);

		pPosition = strchr(m_buf, '}');
		if(!pPosition)
		{
			checkErr = parseChildren(file, node);
			if(checkErr != SUCCESS)
				return checkErr;
		}

		return SUCCESS;
	}

	return PARSE_ERR;
}


	
int VTreeParser::parseChildren(FILE *file, VTreeNode *node)
{
	int checkErr;
	char *pPosition = strchr(m_buf, '(');
	if(!pPosition)
	{
		checkErr = node->createLeft();
		if(checkErr != SUCCESS) 
			return checkErr;

		checkErr = parseNode(file, node->getLeft());
		if(checkErr != SUCCESS)
			return checkErr;
	}
	else
		readFile(file);

	readFile(file);
	pPosition = strchr(m_buf, '(');
	if(!pPosition)
	{
		checkErr = node->createRight();
		if(checkErr != SUCCESS)
			return checkErr;

		checkErr = parseNode(file, node->getRight());
		if(checkErr != SUCCESS)
			return checkErr;
	}
	else
		readFile(file);

	readFile(file);

	return SUCCESS;
}


int VTreeParser::checkEndl(char **pRes)
{
	char *pPosition = strchr(m_buf, '\n');
	if(!pPosition)
	{
		if(m_buf[PARSER_BUF_SIZE-2])
			return OVERFLOW_ERR;

		return PARSE_ERR;
	}

	*pRes = pPosition;
	return SUCCESS;
}


void VTreeParser::readFile(FILE *file)
{
	memset(m_buf, 0, PARSER_BUF_SIZE);
	fgets(m_buf, PARSER_BUF_SIZE, file);
}

