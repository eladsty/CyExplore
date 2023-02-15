#include <assert.h> /*TO USE ASSERT*/
#include <stdio.h> /*to use print*/

#include "bitwise.h"



int main()
{
	unsigned i = 0;
	unsigned arr[] = {22, 20, 1414, 52, 78, 48, 56, 21};
	

	Pow2(3,4);
 
 	assert(1 == IsSquared(16));
	assert(0 == IsSquared(15));
  	assert(1 == IsSquaredNoLoop(16));
	assert(0 == IsSquaredNoLoop(15));
	assert(5 == AddOne(4));
	assert(6 == AddOne(5));
 	ThreeBitsOn(arr, 8);   
 	
 		 for(;i<8;++i)
	{
	printf("The mirror of the number is: %u \n", ByteMirror(arr[i]));
 
	}
	 
 
  	printf("if on print 1: %d \n", IsBothOn('%'));
	printf("if on print 1: %d \n", IsBothOn('g'));
	printf("if on print 1: %d \n", IsBothOn('G'));
	 
  	printf("if on print 1: %d \n", IsOneOn('%'));
	printf("if on print 1: %d \n", IsOneOn('g'));
	printf("if on print 1: %d \n", IsOneOn('G'));
	printf("if on print 1: %d \n", IsOneOn('H'));
	
	
	for(i=0; i<68 ;i+=4)
	{
		printf("the number is %u, closest one is: %u", Divisible16(i));
	
	}
	
	return 0;
}
