

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


unsigned char ByteMirrorNoLoop(unsigned char b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}



























