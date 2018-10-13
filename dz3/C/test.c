#include <stdio.h>
#include "stack.h"


int main()
{
	stack stack;
	stackCtor(&stack);
	stackPush(&stack, 9);
	stackPush(&stack, 10);
	printf("head = %d\n", stack.head->data);
	stackPop(&stack);
	printf("head = %d\n", stack.head->data);
	stackFree(&stack);

	printf("hello there\n");
	return 0;
}