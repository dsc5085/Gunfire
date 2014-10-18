#include <random>

#include "Math.h"

double gun::Math::Max(double a, double b)
{
	if (a >= b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

int gun::Math::Wrap(int x, int lower, int upper)
{
	int wrapped = x;
	if (x > upper)
	{
		wrapped = lower;
	}
	else if (x < lower)
	{
		wrapped = upper;
	}
	return wrapped;
}

double gun::Math::Random(double min, double max)
{
	double rand_d = ((double)rand()) / (double)RAND_MAX;
    double diff = max - min;
    return min + rand_d * diff;
}