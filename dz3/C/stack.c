#include "stack.h"


int stackCtor(stack *stack)
{
	if(stack == NULL)
		return NULLPTR_ERR;

	stack->count = 0;
	stack->head = NULL;
		
	return SUCCESS;
}


int stackDtor(stack *stack)
{
	if(stack == NULL)
		return NULLPTR_ERR;
	
	if(stack->count == 0)
		return EMPTY_ERR;

	while(stack->count != 0)
		stackPop(stack);
	
	return SUCCESS;
}


int stackPush(stack *stack, data_t data)
{
	if(stack == NULL)
		return NULLPTR_ERR;

	stackElement *element = (stackElement *)calloc(1, sizeof(stackElement));
	if(errno != 0)
	{
		perror("Cannot allocate memory");
		return ALLOC_ERR;
	}
	
	element->next = stack->head;
	element->data = data;
	stack->head = element;
	stack->count++;
	
	return SUCCESS;
}


int stackPop(stack *stack)
{
	if(stack == NULL)
		return NULLPTR_ERR;
	
	if(stack->count == 0)
		return EMPTY_ERR;

	stackElement *tmp = stack->head; 
	stack->head = tmp->next;
	free(tmp);
	stack->count--;	
	
	return SUCCESS;
}