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
	int checkErr;
	VTree tree;
	tree.createRoot();

	tree.getRoot()->setFunc(F_POW);
	tree.getRoot()->createLeft();
	tree.getRoot()->createRight();
	tree.getRoot()->getLeft()->setDouble(2);
	tree.getRoot()->getRight()->setFunc(F_CTG);
	tree.getRoot()->getRight()->createLeft();
	//tree.getRoot()->getRight()->createRight();
	tree.getRoot()->getRight()->getLeft()->setChar('x');
	//tree.getRoot()->getRight()->getRight()->setChar('x');

	/*tree.getRoot()->setFunc(F_DIV);
	tree.getRoot()->createLeft();
	tree.getRoot()->getLeft()->setChar('y');
	tree.getRoot()->createRight();
	tree.getRoot()->getRight()->createRight();
	tree.getRoot()->getRight()->createLeft();
	tree.getRoot()->getRight()->setFunc(F_ADD);
	tree.getRoot()->getRight()->getLeft()->setChar('x');
	tree.getRoot()->getRight()->getRight()->setDouble(45);*/


	tree.dump("dump/tree.dot");
	TCHECK("dump");

	tree.pdump("dump/ptree.dot");
	TCHECK("pdump");

	tree.tdump("dump/tree.txt");
	TCHECK("tdump");

	checkErr = tree.dumpTex("dump/treeTex.txt");
	if(checkErr != SUCCESS)
	{
		printf("err = %d\n", checkErr);
		exitErr("dumpTex");
	}
	
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

	return 0;
}