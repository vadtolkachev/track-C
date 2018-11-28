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
	int checkErr = checkEndl();
	if(checkErr != SUCCESS) 
		return checkErr;

	char *pPosition = strchr(m_buf, '{');
	if(pPosition)
	{
		tStrCpy(node, pPosition);
		readFile(file);

		pPosition = strchr(m_buf, '}');
		if(!pPosition)
		{
			pPosition = strchr(m_buf, '(');
			if(!pPosition)
			{
				node->createLeft();
				parseNode(file, node->getLeft());
			}
			else
				readFile(file);

			readFile(file);
			pPosition = strchr(m_buf, '(');
			if(!pPosition)
			{
				node->createRight();
				parseNode(file, node->getRight());
			}
			else
				readFile(file);

			readFile(file);
		}

		return SUCCESS;
	}

	return PARSE_ERR;
}


int VTreeParser::checkEndl()
{
	char *pPosition = strchr(m_buf, '\n');
	if(!pPosition)
	{
		if(m_buf[PARSER_BUF_SIZE-2])
			return OVERFLOW_ERR;

		return PARSE_ERR;
	}

	return SUCCESS;
}


void VTreeParser::readFile(FILE *file)
{
	memset(m_buf, 0, PARSER_BUF_SIZE);
	fgets(m_buf, PARSER_BUF_SIZE, file);
}


void VTreeParser::tStrCpy(VTreeNode *node, char *pPosition)
{
	int len = strlen(pPosition)-2;
	assert(len > 0);

	char *newStr = new char[len+1]();
	strncpy(newStr, pPosition+1, len);

	node->setStr(newStr);

	delete[] newStr;
}
