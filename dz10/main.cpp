#include "VTree.hpp"
#include <stdio.h>


int main()
{
	VTree tree;
	tree.createRoot();
	tree.getRoot()->setChar('+');

	tree.getRoot()->createLeft();
	tree.getRoot()->getLeft()->setChar('*');
	tree.getRoot()->getLeft()->createRight();
	tree.getRoot()->getLeft()->createLeft();
	tree.getRoot()->getLeft()->getRight()->setDouble(6);
	tree.getRoot()->getLeft()->getLeft()->setChar('x');

	tree.getRoot()->createRight();
	tree.getRoot()->getRight()->setChar('*');
	tree.getRoot()->getRight()->createRight();
	tree.getRoot()->getRight()->createLeft();
	tree.getRoot()->getRight()->getRight()->setDouble(5);
	tree.getRoot()->getRight()->getLeft()->setDouble(3);
	tree.dump("dump/tree.dot");
	tree.pdump("dump/ptree.dot");
	tree.tdump("dump/tree.txt");
	return 0;
}