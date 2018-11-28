#include "VTree.hpp"


void exitErr(const char *str)
{
	printf("Exit with error: %s\n", str);
	exit(EXIT_FAILURE);
}


int main()
{
	VTree tree;
	tree.parseTree("tree3.txt");

	tree.dump("dumps/tree3.dot");
	int checkErr = tree.checkError();
	if(checkErr != SUCCESS)
		exitErr("dump");

	return 0;
}