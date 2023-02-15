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
		
	
	
 
	 
	 
	 
	return 0;
}
