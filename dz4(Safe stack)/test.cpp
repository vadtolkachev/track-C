#define S_DEBUG

#include "MyStack.hpp"
#include "unittest.hpp"


int main()
{	
	MyStack stack = MyStack();
	data_t data = 0;
	
	UNITTEST(stack.isEmpty(), !=, true); 
	UNITTEST(stack.pop(), ==, EMPTY_ERR);
	UNITTEST(stack.getTop(&data), ==, EMPTY_ERR);
	UNITTEST(stack.getTop(nullptr), ==, NULLPTR_ERR);

	UNITTEST(stack.getSize(), ==, 0);
	UNITTEST(stack.getCapacity(), ==, 0);
	UNITTEST(stack.push(6), ==, SUCCESS);	
	
	UNITTEST(stack.getSize(), ==, SUCCESS);	
	UNITTEST(stack.getCapacity(), == , BUF);	
	UNITTEST(stack.getTop(&data), ==, SUCCESS);
	UNITTEST(data, ==, 6);

	UNITTEST(stack.push(7), ==, SUCCESS);
	UNITTEST(stack.getSize(), == , 2);
	UNITTEST(stack.getCapacity(), == , BUF);
	UNITTEST(stack.getTop(&data), ==, SUCCESS);
	UNITTEST(data, ==, 7);
	UNITTEST(stack.push(7), ==, SUCCESS);
	UNITTEST(stack.push(7), ==, SUCCESS);
	UNITTEST(stack.getSize(), == , 4);
	UNITTEST(stack.getCapacity(), == , 2*BUF);

	UNITTEST(stack.pop(), ==, SUCCESS);
	UNITTEST(stack.getSize(), == , 3);
	UNITTEST(stack.getCapacity(), == , 2*BUF);
	
	UNITTEST(stack.isEmpty(), !=, false);

	UNITTEST(stack.push(7), ==, SUCCESS);
	UNITTEST(stack.push(7), ==, SUCCESS);
	UNITTEST(stack.pop(), ==, SUCCESS);
	
	stack.push(5);

	MyStack stack2;
	stack2.push(7);	

	for(int i = 1; i < 100; i++)
		stack.push(i);

	MyStack *pStack = new MyStack();
	delete pStack;

	return 0;
}