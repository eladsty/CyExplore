#include <stdio.h>/*printf*/


#include "stack.h"
/*
 struct car 
{
	size_t engine;
	size_t price;
};
typedef struct car car;

car Honda = {2000, 120000};
*/



int main()
{
	int i = 0;
	int arr[] = {11,33,4,5,77,26,14,51,87,123};
	stack_t *num_stack = StackCreate(10 ,4);
 
  	printf("stack  is empty should be 1: %d\n", StackIsEmpty(num_stack));   
	
	for(i=0; i<5;++i)
	{
		StackPush(num_stack, &arr[i]);
	}
 	 
  	printf("stack not empty should be 0: %d\n", StackIsEmpty(num_stack));   
  	
  	printf("stack size is: %ld\n",  StackSize(num_stack));   
  	
  	
 	printf("%d\n",  *((int *)StackPeek(num_stack)));   
 	StackPop(num_stack);
  	printf("stack size is: %ld\n",  StackSize(num_stack));   
 	printf("%d\n",  *((int *)StackPeek(num_stack)));   
 	printf("%ld\n",  StackCapacity(num_stack));   
 
	StackDestroy(num_stack);
 
 	return 0;
}
 
