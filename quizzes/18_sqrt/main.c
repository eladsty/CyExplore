#include <stdio.h>/* for printf*/

 
/*
double Sqrt(double number)
{
	double int_part = 0;
	double dec_part = 0;
	
	while((int_part+1) * (int_part+1) <= number)
	{
		int_part += 1;
	}
	
	number -= (int_part * int_part);
	
	while((dec_part + 0.00001) * (dec_part + 0.00001) <= number)
	{
		dec_part += 0.00001;
	}
	return (int_part + dec_part);
}
*/


double Sqrt(double number)
{
 
 	int start = 0, end = number, i = 0 ;
 	double mid, answer = 0, dec_part = 0.1;
   
	while(start <= end)
	{
		mid = (start + end) / 2;
		if(mid * mid == number)
		{
			answer = mid;
			break;
		}
		if(mid * mid < number)
		{
			answer = start;
			start = mid + 1;
		}
		else
		{
			end = mid - 1;
		}
	}
	
	for( i = 0; i < 10; ++i)
	{
		while(answer * answer <= number)
		{
			answer += dec_part;
		}
		answer -= dec_part;
		dec_part /= 10;
	}
	return answer;
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
