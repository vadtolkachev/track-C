#pragma once
#include "defines.hpp"
#include "VTree.hpp"
#include <string.h>


const int PARSER_BUF_SIZE = 1024;


class VTreeParser
{
public:
	int parseTree(const char *file_name, VTree *tree);
	int parseNode(FILE *file, VTreeNode *node);
	int parseChildren(FILE *file, VTreeNode *node);
	int checkEndl(char **pRes);

	void readFile(FILE *file);

private:
	char m_buf[PARSER_BUF_SIZE] = "";
};