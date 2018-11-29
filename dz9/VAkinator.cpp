#include "VAkinator.hpp"


VAkinator::VAkinator(VTree *tree)
{
	m_tree = tree;
}


VTree *VAkinator::getTree() const
{
	return m_tree;
}


int VAkinator::search()
{
	return search(m_tree->getRoot());
}


int VAkinator::search(VTreeNode *node)
{
	if((node->getRight() == nullptr) != (node->getLeft() == nullptr))
		return NULLPTR_ERR;

	printf("%s?\n", node->getStr());
	char ans = getchar();
	char check = getchar();
	assert(check == '\n');
	
	if(node->getRight())
	{
		if(ans == 'y')
			search(node->getLeft());
		else
			search(node->getRight());
	}
	else
	{
		if(ans == 'y')
			printf("я же говорил!\n");
		else
		{
			int checkErr = create(node);
			if(checkErr != SUCCESS)
				return checkErr;
		}
	}
	
	return SUCCESS;
}


int VAkinator::create(VTreeNode *node)
{
	printf("кто это?\n");
	char buf[512] = "";
	fgets(buf, 511, stdin);
	char *p = strchr(buf, '\n');
	*p = 0;

	int checkErr = node->createLeft();
	if(checkErr != SUCCESS)
		return checkErr;

	checkErr = node->createRight();
	if(checkErr != SUCCESS)
		return checkErr;

	checkErr = node->getLeft()->setStr(buf);
	if(checkErr != SUCCESS)
		return checkErr;

	checkErr = node->getRight()->setStr(node->getStr());
	if(checkErr != SUCCESS)
		return checkErr;

	printf("Чем %s отличается от %s?\n", buf, node->getStr());
	memset(buf, 0, 512);
	fgets(buf, 511, stdin);
	p = strchr(buf, '\n');
	*p = 0;

	checkErr = node->setStr(buf);
	if(checkErr != SUCCESS)
		return checkErr;

	return SUCCESS;
}

