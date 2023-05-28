#include <stdlib.h>  /* bitwise operators*/
#include <stdio.h> /* printf */



/* #############################*/
/* # Ex.1                      #*/
/* # status: approved          #*/
/* # reviewer: Shlomi          #*/
/* # description: this command #*/
/* # will provide the sum of x #*/
/* # times 2 power of y        #*/
/* # special notes:            #*/
/* #############################*/
long pow2(unsigned int x, unsigned int y)
{
	long result = 0, pow_two = 2;
	
	while (y)
	{
		pow_two <<= 1;
		--y;
	}
	while (pow_two)
	{
		if (pow_two & 1)
		{
			result += x;
		}
		x <<= 1;
		pow_two >>= 1;;
	}
	return result;
}

/* #############################*/
/* # Ex.2                      #*/
/* # status: approved          #*/
/* # reviewer: Shlomi          #*/
/* # description: this command #*/
/* # will check if n is a power#*/
/* # of 2                      #*/
/* # return value: 1 if is     #*/
/* # true, 0 if not.           #*/
/* # special notes: implementef#*/
/* # with(out) loop            #*/
/* #############################*/
int IsSquaredNoLoop(unsigned int n)
{
	if (n == 0)
	{
		return 0;
	}
	return ((n != 1) && (n & (n-1))) ? 0 : 1;
}

int IsSquared(unsigned int n)
{
	if (n == 0)
	{
		return 0;
	}
	while (n > 2)
	{
		n >>= 1;
	}
	return (n == 1) ? 0 : 1;
}

/* #############################*/
/* # Ex.3                      #*/
/* # status: approved          #*/
/* # reviewer: Shlomi          #*/
/* # description: this command #*/
/* # will increase n by 1      #*/
/* # return value: n+1         #*/
/* # special notes:            #*/
/* #############################*/

int AddOne(int n)
{
	int temp = 1;
	
	while (n & temp)
	{
		n ^= temp;
		temp <<= 1;
	}
	
	n ^= temp;
	return n;
}


/* #############################*/
/* # Ex.4                      #*/
/* # status: approved          #*/
/* # reviewer: Shlomi          #*/
/* # description: this command #*/
/* # will increase n by 1      #*/
/* # return value: n+1         #*/
/* # special notes:            #*/
/* #############################*/

int ThreeBitsOn(unsigned int *arr, int size)
{
	int i = 0, count = 0, temp;
	
	while (i < size)
	{
		temp = *arr;
		while (temp)
		{
			count++;
			temp &= (temp - 1);
		}
		if (count == 3)
		{
			printf("%d\n", *arr);
		}
		++i;
		++arr;
		count = 0;
	}
	return 0;
}

/* #############################*/
/* # Ex.5                      #*/
/* # status: approved          #*/
/* # reviewer: Shlomi          #*/
/* # description: this command #*/
/* # will give you the mirror  #*/
/* # byte of your number using #*/
/* # 8 bits                    #*/
/* # return value: mirror of   #*/
/* # number in bits            #*/
/* # special notes: w+wo loop  #*/
/* #############################*/

int ByteMirror(unsigned int n)
{
	unsigned int i = 0, reversed = 0;
	while (i < 8)
	{
		if (n & (1 << i))
		{
			reversed |= (1 << (7 - i));
		}
		++i;
	}
	return reversed;
}


int ByteMirrorNoLoop(unsigned int n)
{
	n = (((n & 170) >> 1 | ((n & 85) << 1)));
	n = (((n & 204) >> 2 | ((n & 51) << 2)));
	n = (((n & 240) >> 4 | ((n & 15) << 4)));
	return n;
}

/* #############################*/
/* # Ex.6.1+2                  #*/
/* # status: approved          #*/
/* # reviewer: Shlomi          #*/
/* # description: this command #*/
/* # will give you the mirror  #*/
/* # byte of your number using #*/
/* # 8 bits                    #*/
/* # return value: true/false  #*/
/* # special notes:            #*/
/* #############################*/

int IsBothOn(unsigned char c)
{
	return ((c & 34) == 34);
}
int IsOneOn(unsigned char c)
{
	return (((c & 2) == 2) || ((c & 32) == 32));
}
/* #############################*/
/* # Ex.6.3                    #*/
/* # status: approved          #*/
/* # reviewer: Nave            #*/
/* # description: this command #*/
/* # will swap the3 and 5 bits #*/
/* # return value: new char    #*/
/* # special notes:            #*/
/* #############################*/
int SwapBits(unsigned char c)
{
	while (((c & 20) == 20) || (((c & 16) == 0) && ((c & 4) == 0))) /* while 3+5=on || 3+5=off */
	{
		return c;
	}
	while ((c & 4) == 0)
	{
		return ((c ^ 16) | 4);
	}
	return ((c ^ 4) | 16);
}

/* #############################*/
/* # Ex.7                      #*/
/* # status: approved          #*/
/* # reviewer: Nave            #*/
/* # description: this command #*/
/* # will find the prior num   #*/
/* # devisible by 16           #*/
/* # return value: num/16=0    #*/
/* # special notes:            #*/
/* #############################*/

int Divisible16(unsigned int n)
{
	return (n & 65520);
}

/* #############################*/
/* # Ex. 8                     #*/
/* # status: approved          #*/
/* # reviewer: Nave            #*/
/* # description: this command #*/
/* # will swap 2 variables     #*/
/* # return value: none        #*/
/* # special notes:            #*/
/* #############################*/

int Swap(int *x, int *y)
{
	if (x != y)
	{
		return 0;
	}
	*x = *x ^ *y;
	*y = *y ^ *x;
	*x = *x ^ *y;
	return 1;
}

/* #############################*/
/* # Ex. 9                     #*/
/* # status: approved          #*/
/* # reviewer: Nave            #*/
/* # description: this command #*/
/* # will return num of set    #*/
/* # bits                      #*/
/* # return value: count       #*/
/* # special notes:            #*/
/* #############################*/

int CountSetBits(int n)
{
	unsigned int i = 0, count = 0;
		
		while (i < sizeof(n))
		{
			while (n)
			{
				count++;
				n &= (n - 1);
			}
			++i;
		}
	return count;
}
	
int CountSetBitsNoLoop(int n)
{
	int count = 0, flag = 1;
	if (n)
	{
		n &= (n - 1);
		count = flag + CountSetBitsNoLoop(n);
	}
	
	return count;
}

/* #############################*/
/* # Ex. 10                    #*/
/* # status:                   #*/
/* # reviewer:                 #*/
/* # description: this command #*/
/* # will recieve a float and  #*/
/* # print it's bits           #*/
/* # return value: binary      #*/
/* # special notes:            #*/
/* #############################*/

int FloatAnalysis(float f)
{
	unsigned int *i = (void*)&f;
	printf("%b\n", *i);
	return 0;
}


