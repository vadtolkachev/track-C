#include <stdio.h>
#include <limits>
#include "SolveSquare.hpp"


int main()
{
	double x1, x2;
	double max = std::numeric_limits<double>::max();
	
	solveSquare(0, 0, 0, &x1, &x2);
	solveSquare(0, 0, 1, &x1, &x2);
	solveSquare(0, 1, 0, &x1, &x2);
	solveSquare(1, 0, 0, &x1, &x2);
	solveSquare(1, 1, 1, &x1, &x2);
	solveSquare(1, 2, 1, &x1, &x2);
	solveSquare(1, 3, 1, &x1, &x2);
	solveSquare(1, 0, 2*max, &x1, &x2);
	solveSquare(0, 0.5, max, &x1, &x2);
	solveSquare(1, max, 1, &x1, &x2);
	solveSquare(NAN, 1, 1, &x1, &x2);
	solveSquare(1, 3, 1, nullptr, &x2);
	solveSquare(1, 3, 1, &x1, nullptr);
	solveSquare(0, 0, 0, &x1, &x1);
	solveLinear(1, 1, nullptr);
	solveLinear(NAN, 1, &x1);	
	
	return 0;
}