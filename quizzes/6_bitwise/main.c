#include <stdio.h>

int SetBitCouples(char c)
{
	int cnt = 0;
	while(c)
	{
		if(3 == (c & 3))
		{
			++cnt;
		}
		c >>=1;
	}

	return cnt;
}
void SwapWTemp(int *n1, int *n2)
{
	int temp = *n1;
 	*n1 = *n2;
 	*n2 = temp;
}


void SwapWBitwise(int *n1, int *n2)
{
	if(*n1 != *n2)
	{
		*n1 ^= *n2;
		*n2 ^= *n1;
		*n1 ^= *n2; 
	}
}
void SwapWArit(int *n1, int *n2)
{
	*n1 += *n2;
	*n2 = *n1 - *n2;
	*n1 = *n1 - *n2;
}

int CountSetBits(int n)
{
	int cnt;
	while(0 != n)
	{
		n = n & (n-1);
		++cnt;
	}
	return cnt;
}
int main()
{
	int x = 2, y = 6;
	printf("should be 3: %d\n",SetBitCouples(118)); 
	SwapWBitwise(&x,&y);
	printf("bitwise swap:x is %d, y is %d\n",x,y); 
	SwapWArit(&x,&y);
	printf("Arti swap : x is %d, y is %d\n",x,y); 
	SwapWTemp(&x,&y);
	printf("temp swap: x is %d, y is %d\n",x,y); 
	printf("should be 5 set bits: %d\n", CountSetBits(118)); 
	return 0;
}
