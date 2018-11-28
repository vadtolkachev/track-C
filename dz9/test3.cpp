#include "VTree.hpp"


void exitErr(const char *str)
{
	printf("Exit with error: %s\n", str);
	exit(EXIT_FAILURE);
}


int main()
{
	VTree tree2;
	VTreeNode node1;
	VTreeNode node2;
	VTreeNode node3;
	VTreeNode node4;
	node1.setStr("1");
	node2.setStr("2");
	node3.setStr("3");
	node4.setStr("4");
	tree2.setRoot(&node1);
	tree2.getRoot()->setLeft(&node2);
	tree2.getRoot()->setRight(&node3);
	tree2.getRoot()->getRight()->setRight(&node4);

	return 0;
}