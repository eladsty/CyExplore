

#include <stdio.h> /* printf*/
#include <string.h> /*strcat*/



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
 * Description: check if n is power of 2
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
 * Description:  check if n is power of 2 wihtout a loop
 * Return : int.
 */

int IsSquaredNoLoop(unsigned int n)
{
	return (0 == (n & (n-1))? 1 : 0);
}




/* Status: READY;
 * Reviewer: shlomi
 * Description: add one with bitwise  
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
 * Description: print from array only numbers that have 3 1's.
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




/* Status: READY;
 * Reviewer: Amir
 * Description:  find mirror representation of a binary with loop
 * Return :   
 */
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




/* Status: In development;
 * Reviewer:   Amir 
 * Description:  find mirror representation of a binary without loop
 * Return :   
 */
unsigned int ByteMirrorNoLoop(unsigned int n) 
{
    n = (n & 0x55555555) <<  1 | (n & 0xAAAAAAAA) >>  1; 
    n = (n & 0x33333333) <<  2 | (n & 0xCCCCCCCC) >>  2; 
    n = (n & 0x0F0F0F0F) <<  4 | (n & 0xF0F0F0F0) >>  4; 
    n = (n & 0x00FF00FF) <<  8 | (n & 0xFF00FF00) >>  8; 
    n = (n & 0x0000FFFF) << 16 | (n & 0xFFFF0000) >> 16;
    return n;
}




/* Status: READY;
 * Reviewer:  Amir
 * Description:  check if both the second and the 6th bit is on (1)
 * Return :   
 */
unsigned IsBothOn(unsigned char c)
{
	return ((c>>1)&1 && (c>>5)&1);
}



/* Status: READY;
 * Reviewer:  Amir
 * Description:  check if at least one is 1 between 2 and 6 
 * Return :   
 */
unsigned IsOneOn(unsigned char c)
{
	return ((c>>1)&1 || (c>>5)&1);
}



/* Status: READY;
 * Reviewer:  Amir
 * Description:  swap between the 3rd and 5th bits and return new number
 * Return :   
 */
unsigned SwapBits(unsigned num)
{
 	unsigned char third = (num >> 2) & 1;
 	unsigned char fifth = (num >> 4) & 1;
 	unsigned char similarity = third ^ fifth;
 	
 	similarity = (similarity << 2) | (similarity << 4);
	
	return (num ^ similarity);	
}



/* Status: READY;
 * Reviewer:  Amir
 * Description: swap between two variables. 
 * Return :   
 */
void Swap(int *x, int *y)
{
 	if(x != y)
 	{
 		*x ^= *y;
 		*y ^= *x;
 		*x ^= *y;
 	}
}



/* Status: READY;
 * Reviewer:  Amir
 * Description:  closest smaller number that is devisible by 16 without remainder
 * Return :   
 */
unsigned Divisible16(unsigned num)
{
	 return ((num >> 4) << 4);
}




/* Status: READY;
 * Reviewer:  Amir
 * Description:  count bits set to 1 
 * Return :   
 */
unsigned CountSetBits(unsigned num)
{
	unsigned cnt = 0;
	
	while(num)
	{
		if(num & 1)
		{
			++cnt;
		}
		
		num >>= 1;
	}
	
	return cnt;
}



/* Status: READY;
* Reviewer:  Amir
* Description:  count bit without loop
* Return :   
*/
int CountSetBitsNoLoop(unsigned int x)
{
	x = x - ((x >> 1) & 0x55555555);
	x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
	x = (x + (x >> 4)) & 0x0F0F0F0F;
	x = x + (x >> 8);
	x = x + (x >> 16);
	return x & 0x0000003F;
}


 



/* Status: reasearch;
* Reviewer:  Amir
* Description: receive float and print it's bits  
* Return :   
  */
void FloatAnalysis(float *f)
{
 	unsigned int *p1 = (void*)(f);
 	printf("%b\n",*p1);
 	
}


 











