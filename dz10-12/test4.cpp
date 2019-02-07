#include "VTree.hpp"
#include <stdio.h>


#define TCHECK(str)			\
{					\
	checkErr = tree.checkError(); 	\
	if(checkErr != SUCCESS) 	\
		exitErr(str);		\
}


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

	checkErr = tree.derivate("dump/treeTex3.txt");
	if(checkErr != SUCCESS)
	{
		printf("err: %d\n", checkErr);
		exitErr("derivate");
	}

	
	tree.dump("dump/tree2.dot");
	TCHECK("dump2");

	tree.pdump("dump/ptree2.dot");
	TCHECK("pdump2");

	tree.tdump("dump/tree2.txt");
	TCHECK("tdump2");

	checkErr = tree.dumpTex("dump/treeTex2.txt");
	if(checkErr != SUCCESS)
	{
		printf("err = %d\n", checkErr);
		exitErr("dumpTex2");
	}

	printf("success\n");

	return 0;
}