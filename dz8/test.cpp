#include "VTTree.hpp"
#include <stdio.h>
#include <stdlib.h>


int main()
{
	VTTree tmpTree;
	tmpTree.push(6);

	tmpTree.push(7);
	tmpTree.push(9);
	tmpTree.push(4);
	tmpTree.push(8);
	tmpTree.push(20);
	tmpTree.push(3);
	tmpTree.push(4);
	tmpTree.push(4);
	tmpTree.push(5);
	tmpTree.push(1);
	tmpTree.push(-1);
	tmpTree.push(2);

	printf("%d\n", tmpTree.getRoot()->getNumb());
	printf("%d\n", tmpTree.getRoot()->getRight()->getNumb());
	printf("%d\n", tmpTree.getRoot()->getRight()->getRight()->getNumb());
	printf("%d\n", tmpTree.getRoot()->getLeft()->getNumb());
	printf("%d\n", tmpTree.getRoot()->getRight()->getRight()->getLeft()->getNumb());

	bool bTmp = tmpTree.isOK();
	printf("bTmp = %d\n", bTmp);

	FILE *file1 = fopen("dumps/tree1.dot", "w");
	tmpTree.dump(file1);
	system("dot -T jpg -o dumps/tree1.jpg dumps/tree1.dot &");

	FILE *file2 = fopen("dumps/tree2.dot", "w");
	tmpTree.pdump(file2);
	system("dot -T jpg -o dumps/tree2.jpg dumps/tree2.dot &");

	return 0;
}