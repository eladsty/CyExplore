#include <assert.h> /*TO USE ASSERT*/
#include <stdio.h> /*to use print*/

#include "bitwise.h"



int main()
{
	unsigned i = 0;
	unsigned arr[] = {22, 20, 1414, 52, 78, 48, 56, 21, 14987, 67, 8, 0};
	int x = 9873, y = 1507;

 	
 	
 	
 	assert(1 == IsSquared(16));
	assert(0 == IsSquared(15));
  	assert(1 == IsSquaredNoLoop(16));
	assert(0 == IsSquaredNoLoop(15));
	assert(5 == AddOne(4));
	assert(6 == AddOne(5));
 	ThreeBitsOn(arr, 8);   
 	
 		 for(;i<12 ;++i)
	{
	printf("The mirror of the number is: %u \n", ByteMirror(arr[i]));
	printf("the closes divisible number(in 16) below %d is: %d \n", arr[i], Divisible16(arr[i]));
	}
	 
 
  	printf("if on print 1: %d \n", IsBothOn('%'));
	printf("if on print 1: %d \n", IsBothOn('g'));
	printf("if on print 1: %d \n", IsBothOn('G'));
	 
  	printf("if on print 1: %d \n", IsOneOn('%'));
	printf("if on print 1: %d \n", IsOneOn('g'));
	printf("if on print 1: %d \n", IsOneOn('G'));
	printf("if on print 1: %d \n", IsOneOn('H'));
 
 
	assert(3 == ByteMirror(12));
	assert(313 == ByteMirror(1252));
	
	/*byte mirror no loop*/

	
	assert(112 == SwapBits(100));
  	assert(4 == SwapBits(16));
  
  	assert(3 == CountSetBits(200));
   	assert(7 == CountSetBits(5005));
 
 	Swap(&x,&y);
   	assert(9873 == y);
   	assert(1507 == x);
   	
   	
   	
		 
	return 0;
}
