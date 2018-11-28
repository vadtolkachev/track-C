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
	char check;
	while(ans == 'y')
	{
		ak.search();
		printf("ещё раз?\n");
		ans = getchar();
		check = getchar();
		assert(check == '\n');
	}


	tree.dump("dumps/aktree.dot");
	int checkErr = tree.checkError();
	if(checkErr != SUCCESS)
		exitErr("dump");

	return 0;
}