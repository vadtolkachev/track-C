#include "MyStack.hpp"
#include <iostream>


const char GREEN[] = "\033[1;32m";
const char RED[] = "\033[1;31m";
const char WHITE[] = "\033[1;37m";
const char NORM[] = "\033[0m";


#define UNITTEST(what,op,ref)						\
{									\
	auto result = (what);						\
	auto comp = (ref);						\
									\
	std::cout << WHITE << __FILE__":" << __LINE__ << ": " 		\
		<< __PRETTY_FUNCTION__ << ": " << NORM;			\
	if(result op comp)						\
		std::cout << #what << GREEN << " [passed]\n" << NORM;	\
	else								\
		std::cout << #what << RED << " is "			\
			<< result << " but should be "			\
			<< #op" " << comp << NORM << std::endl;		\
}


int main()
{
	MyStack stack;
	data_t data = 0;	
	
	UNITTEST(stack.isEmpty(), !=, false); //test for UNITTEST

	UNITTEST(stack.pop(), ==, 0);
	UNITTEST(stack.getTop(&data), ==, 0);
	UNITTEST(stack.getTop(nullptr), ==, -1);

	UNITTEST(stack.push(6), ==, 1);	
	UNITTEST(stack.getCapacity(), == , 1);	
	UNITTEST(stack.getTop(&data), ==, 1);
	UNITTEST(data, ==, 6);

	UNITTEST(stack.push(7), ==, 1);
	UNITTEST(stack.getCapacity(), == , 2);	
	UNITTEST(stack.getTop(&data), ==, 1);
	UNITTEST(data, ==, 7);

	UNITTEST(stack.push(7), ==, 1);
	UNITTEST(stack.pop(), ==, 1);
	UNITTEST(stack.isEmpty(), !=, false);		
	
	return 0;
}