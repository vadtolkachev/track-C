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
	tree.createRoot();
	tree.getRoot()->setDouble(123);

	int checkErr;

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
	
	checkErr = tree.derivate();
	if(checkErr != SUCCESS)
	{
		printf("err: %d\n", checkErr);
		exitErr("derivate");
	}

	tree.dump("dump/tree2.dot");
	checkErr = tree.checkError();
	if(checkErr != SUCCESS)
		exitErr("dump2");

	tree.pdump("dump/ptree2.dot");
	checkErr = tree.checkError();
	if(checkErr != SUCCESS)
		exitErr("pdump2");

	tree.tdump("dump/tree2.txt");
	checkErr = tree.checkError();
	if(checkErr != SUCCESS)
		exitErr("tdump2");


	return 0;
}