#include "stack.h"


int stackCtor(stack *stack)
{
	if(stack == NULL)
		return -1;

	stack->count = 0;
	stack->head = NULL;
		
	return 1;
}


int stackDtor(stack *stack)
{
	if(stack == NULL)
		return -1;
	
	if(stack->count == 0)
		return 0;

	while(stack->count != 0)
		stackPop(stack);
	
	return 1;
}


int stackPush(stack *stack, data_t data)
{
	if(stack == NULL)
		return -1;

	stackElement *element = (stackElement *)calloc(1, sizeof(stackElement));
	if(errno != 0)
	{
		perror("Cannot allocate memory");
		return -2;
	}
	
	element->next = stack->head;
	element->data = data;
	stack->head = element;
	stack->count++;
	
	return 1;
}


int stackPop(stack *stack)
{
	if(stack == NULL)
		return -1;
	
	if(stack->count == 0)
		return 0;

	stackElement *tmp = stack->head; 
	stack->head = tmp->next;
	free(tmp);
	stack->count--;	
	
	return 1;
}