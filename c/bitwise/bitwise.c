

#include <stdio.h> /* printf*/



/* Status: READY;
 * Reviewer: shlomi
 * Description: return x*(2^y).
 * Return : long.
 */
long Pow2(unsigned int x, unsigned int y)
{
	printf("x*(2^y) is: %u\n",x<<y);
	return x << y;
}


/* Status: READY;
 * Reviewer: shlomi
 * Description: check if squared.
 * Return : int.
 */
int IsSquared(unsigned int n)
{
	unsigned int i = 0;
	
	while((2 << i) < n)
	{
		++i;
	}
 	
	return ((2 << i == n)? 1 : 0);
}
/* Status: READY;
 * Reviewer: shlomi
 * Description: add one.
 * Return : int.
 */

int IsSquaredNoLoop(unsigned int n)
{
	return (0 == (n & (n-1))? 1 : 0);
}

/* Status: READY;
 * Reviewer: shlomi
 * Description: add one.
 * Return : int.
 */
int AddOne(int x)
{
    int n = 1;
    
    while(x & n)
    {
        x = x ^ n;
        n <<= 1;
    }
     
    x = x ^ n;
    return x;
}

/* Status: READY;
 * Reviewer: Hen
 * Description: print only number that have 3 one's.
 * Return :  none.
 */

void ThreeBitsOn(const unsigned *arr, unsigned n)
{
	unsigned i = 0;
	unsigned temp = 0;
    unsigned cnt = 0;	
	
	while (i < n)
	{
		temp = arr[i];
 
		while (temp)
		{
			cnt += (temp & 1);	
			temp >>= 1;
			
			if(cnt > 3)
			{
				break;
			}
		}
 
		if(3 == cnt)
		{
			printf("%d\n", arr[i]);
		}
		
		cnt = 0;
		++i;
	}
	
}

unsigned ByteMirror(unsigned N)
{
	unsigned MirrorN = 0;
	
	while (N)
	{
		MirrorN <<= 1;
		if(N & 1)
		{
			MirrorN ^= 1;
		}
		
		N >>= 1;
	}
	
	return MirrorN;
}


unsigned int ByteMirrorNoLoop(unsigned int c) 
{
	c = ((c & 0xf0) >> 4) | ((c & 0x0f) << 4);
	c = ((c & 0xcc) >> 2) | ((c & 0x33) << 2);
	c = ((c & 0xaa) >> 1) | ((c & 0x55) << 1);
	
   return c;
}


unsigned IsBothOn(unsigned char c)
{
	return ((c>>1)&1 && (c>>5)&1);
}


unsigned IsOneOn(unsigned char c)
{
	return ((c>>1)&1 || (c>>5)&1);
}

unsigned SwapBits(unsigned num)
{
	

	
}

unsigned Divisible16(unsigned num)
{
	 return (n & 65520);
	
	return 0;
}


















