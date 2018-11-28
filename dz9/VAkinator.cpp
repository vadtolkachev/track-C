#include "VAkinator.hpp"


VAkinator::VAkinator(VTree *tree)
{
	m_tree = tree;
}


VTree *VAkinator::getTree() const
{
	return m_tree;
}


int VAkinator::search(VTreeNode *node)
{
	if((node->getRight() == nullptr) != (node->getLeft() == nullptr))
	{
		return NULLPTR_ERR;
	}

	printf("%s?\n", node->getStr());
	char ans = getchar();
	char check = getchar();
	assert(check == '\n');
	//printf("ak:ans = %c\n", ans);
	
	if(node->getRight())
	{
		if(ans == 'y')
		{
			search(node->getLeft());
		}
		else
		{
			search(node->getRight());
		}
	}
	else
	{
		if(ans == 'y')
			printf("я же говорил!\n");
		else
		{
			printf("кто это?\n");
			char buf[512] = "";
			fgets(buf, 511, stdin);
			char *p = strchr(buf, '\n');
			*p = 0;

			node->createLeft();
			node->createRight();

			node->getLeft()->setStr(buf);
			node->getRight()->setStr(node->getStr());

			printf("Чем %s отличается от %s?\n", buf, node->getStr());
			memset(buf, 0, 512);
			fgets(buf, 511, stdin);
			p = strchr(buf, '\n');
			*p = 0;

			node->setStr(buf);
		}
	}
	
	return SUCCESS;
}