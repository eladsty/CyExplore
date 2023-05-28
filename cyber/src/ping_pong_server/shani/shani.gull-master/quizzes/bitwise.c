#include <stdio.h>
int couple(int n);
int Howmany(int n);
void swap1(int *x, int *y);
void swap2(int *x, int *y);
void swap3(int *x, int *y);

int main()
{
	int n = 15, m = 17, s = 48;
	int *np = &n, *mp = &m;
	printf("%d\n", Howmany(n));
	printf("n = %d m = %d\n", n, m);
	swap3(np, mp);
	printf("n = %d m = %d\n", n, m);
	
}

	
	
/* q.1 */	
int couple(int n)
{
	int count = 0;
	while (n > 1)
	{
		if ((n % 2 != 0) && ((n>>1) % 2 != 0))
		{
			++count;
			n >>= 1;
		}
		else
		{
			n >>= 1;
		}
	}
	return count;
}
/* q.2 */
void swap1(int *x, int *y)
{
	*x = *x ^ *y;
	*y = *x ^ *y;
	*x = *x ^ *y;
}
void swap2(int *x, int *y)
{
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}
void swap3(int *x, int *y)
{
	*x = *x + *y;
	*y = *x - *y;
	*x = *x - *y;
}
/* q.3 */
int Howmany(int n)
{
	int count = 0;
	while (n)
	{
		n = n & (n-1);
		++count;
	}
	return count;
}
