#include "VTree.hpp"
#include <stdio.h>


int main()
{
	VTree tree;
	tree.createRoot();
	tree.getRoot()->setFunc(F_ADD);

	tree.getRoot()->createLeft();
	tree.getRoot()->getLeft()->setFunc(F_MUL);
	tree.getRoot()->getLeft()->createRight();
	tree.getRoot()->getLeft()->createLeft();
	tree.getRoot()->getLeft()->getRight()->createLeft();
	tree.getRoot()->getLeft()->getRight()->setFunc(F_LOG);
	tree.getRoot()->getLeft()->getRight()->getLeft()->setDouble(1325.32);
	tree.getRoot()->getLeft()->getLeft()->setChar('x');

	tree.getRoot()->createRight();
	tree.getRoot()->getRight()->setFunc(F_ADD);
	tree.getRoot()->getRight()->createRight();
	tree.getRoot()->getRight()->createLeft();
	tree.getRoot()->getRight()->getRight()->setDouble(5);
	tree.getRoot()->getRight()->getLeft()->setDouble(3);

	tree.dump("dump/tree.dot");
	tree.pdump("dump/ptree.dot");
	tree.tdump("dump/tree.txt");

	VTree tree2;
	tree2.parseTree("dump/tree.txt");
	tree2.dump("dump/tree2.dot");
	tree2.pdump("dump/ptree2.dot");
	tree2.tdump("dump/tree2.txt");


	return 0;
}