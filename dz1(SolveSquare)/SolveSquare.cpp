#include "SolveSquare.hpp"


int solveLinear(double b, double c, double *x)
{	
	if((std::isfinite(b) == 0) || (std::isfinite(c) == 0)) 
		return -1;

	if(x == nullptr)
		return -1;

	if(b == 0)
	{
		if(c == 0)
			return 3;

		return 0;	
	}
	
	*x = -c/b;	
	
	if(std::isfinite(*x) == 0)
		return -1;

	return 1;
}


int solveSquare(double a, double b, double c, double *x1, double *x2)
{
	if((std::isfinite(a) == 0) || (std::isfinite(b) == 0) || (std::isfinite(c) == 0)) 
		return -1;

	if((x1 == nullptr) || (x2 == nullptr))
		return -1;

	if(x1 == x2)
		return -1;

	if(a == 0)
	{
		int res = solveLinear(b, c, x1);
		if(res == 1)		
			*x2 = *x1;
		return res;
	}
	
	double d = b*b - 4*a*c;
	if(d < 0)
		return 0;

	if(d == 0)
	{
		*x1 = -b/(2*a);
		if(std::isfinite(*x1) == 0)
			return -1;
		
		*x2 = *x1; 		
		return 1;
	}	

	*x1 = (-b + sqrt(d))/(2*a);
	*x2 = (-b - sqrt(d))/(2*a);

	if((std::isfinite(*x1) == 0) || (std::isfinite(*x2) == 0)) 
		return -1;

	return 2;
}
