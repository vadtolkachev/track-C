#include "VAkinator.hpp"
#include <stdio.h>
#include <stdlib.h>


void exitErr(const char *str)
{
	printf("Exit with error: %s\n", str);
	exit(EXIT_FAILURE);
}


int main()
{
	VTreeNode node;
	char str[512] = "Привет мир";
	node.m_str = str;
	VTree tmpTree(&node);
	
	tmpTree.dump("dumps/tree1.dot");
	int checkErr = tmpTree.checkError();
	if(checkErr != SUCCESS)
		exitErr("dump");

	puts("hello world");

	return 0;
}