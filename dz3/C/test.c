#include "stack.h"


const char GREEN[8] = "\033[1;32m";
const char RED[8] = "\033[1;31m";
const char WHITE[8] = "\033[1;37m";
const char NORM[5] = "\033[0m";


#define UNITTEST(what,op,ref, type)				\
{								\
	type result = (what);					\
	type comp = (ref);					\
								\
	printf("%s%s:%d: %s: %s", WHITE, __FILE__, __LINE__, 	\
		__PRETTY_FUNCTION__, NORM);			\
	if(result op comp)					\
		printf(#what"%s [passed]\n%s", GREEN, NORM);	\
	else							\
	{							\
		printf(#what"%s is ", RED);			\
		print_##type(result);				\
		printf(" but should be "#op" ");		\
		print_##type(comp);				\
		printf("%s\n", NORM);				\
	}							\
}


int print_int(int n)
{
	return printf("%d", n);
}


int print_double(double d)
{
	return printf("%lg", d);
}


int main()
{
	stack stack;
	stackCtor(&stack);

	double a = 2, b = 3;
	UNITTEST(a, ==, b, double); //test for UNITTEST
	UNITTEST(stack.count, !=, 0, int); //test for UNITTEST

	UNITTEST(stackCtor(NULL), ==, -1, int);
	UNITTEST(stackDtor(NULL), ==, -1, int);
	UNITTEST(stackPush(NULL, 1), ==, -1, int);
	UNITTEST(stackPop(NULL), ==, -1, int);
	UNITTEST(stackDtor(&stack), ==, 0, int);
	UNITTEST(stackPop(&stack), ==, 0, int);
	UNITTEST(stackPush(&stack, 7), ==, 1, int);
	UNITTEST(stack.count, ==, 1, int);
	UNITTEST(stack.head->data, ==, 7, int);

	stackDtor(&stack);

	return 0;
}