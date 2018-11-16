#define S_DEBUG
#include "MyStack.hpp"
#include <iostream>

int main()
{
	MyStack stack;
	data_t data;
	stack.push(7);
	stack.push(2);
	stack.push(7132456);
	stack.getTop(&data);
	std::cout << data << "\n";
	stack.pop();
	stack.getTop(&data);
	std::cout << data << "\n";
	stack.pop();
	stack.getTop(&data);
	std::cout << data << "\n";
	stack.pop();
	int err = stack.pop();

	if(err == EMPTY_ERR)
		std::cout << "empty err\n";

	err = stack.push(NAN);
	if(err == INF_ERR)
		std::cout << "inf err\n";



	return 0;
}