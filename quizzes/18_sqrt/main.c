#include <stdio.h>/* for printf*/

#define TOLERANCE 0.000000001
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

/*
double Sqrt(double number)
{
 
 	double int_part = TOLERANCE;
	double dec_part = 1;
	
	 
	while((int_part+1) * (int_part+1) <= number)
	{
		int_part += 1;
	}
	
	number -= (int_part * int_part);
	
	while(number > TOLERANCE)
	{
		if((dec_part) * (dec_part) > number)
		{
			dec_part /= 10;
		} 
		else
		{
			number -= dec_part;
		}
		
	}
	return (int_part + dec_part);
}
*/
int main()
{
	double d_num = 144.64;
	
	printf("Sqrt of %f is %f",d_num, Sqrt(d_num));
	
	return 0;
}
