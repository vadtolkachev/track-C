#include "VTree.hpp"
#include <stdio.h>


void exitErr(const char *str)
{
	printf("Exit with error: %s\n", str);
	exit(EXIT_FAILURE);
}


int main()
{
	VTree tree;
	tree.parseTree("1.txt");
	int checkErr = tree.checkError();
	if(checkErr != SUCCESS)
	{
		printf("err: %d\n", checkErr);
		exitErr("parseTree");
	}

	tree.dump("dump/tree.dot");
	checkErr = tree.checkError();
	if(checkErr != SUCCESS)
		exitErr("dump");

	tree.pdump("dump/ptree.dot");
	checkErr = tree.checkError();
	if(checkErr != SUCCESS)
		exitErr("pdump");

	tree.tdump("dump/tree.txt");
	checkErr = tree.checkError();
	if(checkErr != SUCCESS)
		exitErr("tdump");

	printf("success\n");

	return 0;
}