#include <stdio.h>
#include <assert.h>
#define __Cexercises_H__


/* function calls */
void SayHello();
double GivePower(double n);
int FlipDigits(int n);
void SwapValues(int *var1, int *var2);
int main()
{
	SayHello();
	GivePower(3);
	printf("%d", FlipDigits(-345));
	return 0;
}

	
/* q3 */
void SayHello()
{
	char hello_world[15] = {0x22, 0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x57, 
		0x6F, 0x72, 0x6C, 0x64, 0x21, 0x22, 0x0};
	printf("%s\n", hello_world);
}


/* q4 */
double GivePower(double n)
{
	int i = 0;
	double result = 1, base = 10;
	if (n < 0)
	{
		base = 1/base;
		n *= -1;
	}
	while ( i < n)
	{
		result *= base;
		i++;
	}
	return result;
}


/* q5 */
int FlipDigits(int n)
{
	int revers = 0;
	while (n != 0)
	{
		revers *= 10;
		revers += n % 10;
		n = n / 10;
	}
	return revers;
}


/* q6 */
void SwapValues(int *var1, int *var2)
{
	int temp = *var1;
	assert (var1 && var2);
	*var1 = *var2;
	*var2 = temp;
}

