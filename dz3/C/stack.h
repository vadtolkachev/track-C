#pragma once
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

typedef int data_t;

#define ALLOC_ERR -2
//const int ALLOC_ERR = -2;
#define NULLPTR_ERR -1
#define EMPTY_ERR 0
#define SUCCESS 1


typedef struct stackElement
{
	data_t data;
	struct stackElement *next;
} stackElement;


typedef struct stack
{
	int count;
	stackElement *head;
} stack;


int stackCtor(stack *stack);
int stackDtor(stack *stack);
int stackPush(stack *stack, data_t data);
int stackPop(stack *stack);