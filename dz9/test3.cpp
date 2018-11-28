#include "VAkinator.hpp"
#include <iostream>


void exitErr(const char *str)
{
	printf("Exit with error: %s\n", str);
	exit(EXIT_FAILURE);
}


int main()
{
	VTree tree;
	tree.parseTree("data/aktree.txt");

	VAkinator ak(&tree);
	char ans = 'y';
	while(ans == 'y')
	{
		ak.search(tree.getRoot());
		printf("ещё раз?\n");
		ans = getchar();
		getchar();
		//printf("main:ans = %c\n", ans);
	}

	tree.dump("dumps/aktree.dot");
	int checkErr = tree.checkError();
	if(checkErr != SUCCESS)
		exitErr("dump");

	return 0;
}