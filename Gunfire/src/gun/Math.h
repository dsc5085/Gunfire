#ifndef GUN_MATH_H
#define GUN_MATH_H

namespace gun
{
	class Math
	{
	public:
		static double Max(double a, double b);
		static int Wrap(int x, int lower, int upper);
		static double Random(double min, double max);
	};
}

#endif