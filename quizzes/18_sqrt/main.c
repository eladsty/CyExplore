#include <stdio.h>/* for printf*/


double Sqrt(double num)
{
	double sqrt = num / 2, mid = 0;
	while(mid  != sqrt)
	{
		mid = sqrt;
		sqrt = ((num / mid) + mid) / 2;
	}
	return sqrt;
}

 
int main()
{
	int i = 0;
	double arr[] = {0, 0.8,10,5,4.5,24};
	for(i=0; i < 6 ; ++i)
	{
		printf("Sqrt of %f is %f\n",arr[i], Sqrt(arr[i]));
	}
 
	 
	return 0;
}
