#pragma once
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

typedef int data_t;


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