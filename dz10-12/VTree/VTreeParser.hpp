#pragma once
#include "defines.hpp"
#include "VTree.hpp"
#include <string.h>


class VTreeParser
{
public:
	VTreeParser();

	int readText(FILE *file);
	int parseTree(const char *file_name, VTree *tree);
	int parseNode(VTreeNode *node);
	int readNode(VTreeNode *node);
	int readDouble(VTreeNode *node);

private:
	char *m_buf;
	int m_size;
	int m_index;
};