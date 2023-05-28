#include <stdio.h>


double Sqrt(double num)
{
	double sqrt = (num / 2), mid = 0;
	while (mid != sqrt)
	{
		mid = sqrt;
		sqrt = ((num / mid) + mid) / 2;
	}
	return sqrt;
}

int main()
{
	double num[] = {2.5, 1.1, 23.4, 11, 9};
	size_t i = 0;
	for (i = 0; i < 5; ++i)
	{
		printf("%f\n", Sqrt(num[i]));
	}
	return 0;
}