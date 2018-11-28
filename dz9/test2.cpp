#include "VTree.hpp"


void exitErr(const char *str)
{
	printf("Exit with error: %s\n", str);
	exit(EXIT_FAILURE);
}


int main()
{
	VTree tree;
	VTree tree2;
	VTreeNode node1;
	VTreeNode node2;
	VTreeNode node3;
	VTreeNode node4;
	node1.setStr("1");
	node2.setStr("2");
	node3.setStr("3");
	node4.setStr("4");

	tree2.createRoot();
	tree2.getRoot()->setStr("1");

	tree2.getRoot()->createLeft();
	tree2.getRoot()->getLeft()->setStr("2");

	tree2.getRoot()->createRight();
	tree2.getRoot()->getRight()->setStr("3");

	tree2.getRoot()->getRight()->createRight();
	tree2.getRoot()->getRight()->getRight()->setStr("4");

	tree2.tdump("tree2.txt");

	tree.parseTree("tree2.txt");

	tree.dump("dumps/tree3.dot");
	int checkErr = tree.checkError();
	if(checkErr != SUCCESS)
		exitErr("dump");

	printf("success\n");

	return 0;
}