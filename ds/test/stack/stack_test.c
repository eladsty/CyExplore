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
	double arr_double[] = {11.187,33.1,4.1,5.98,77.115,26.123,14.342,51.233,87.622,123};
	stack_t *num_stack = StackCreate(10 ,sizeof(int));
 	stack_t *double_stack = StackCreate(10 ,sizeof(double));
 	
  	printf("stack  is empty should be 1: %d\n", StackIsEmpty(num_stack));   
  	printf("stack  is empty should be 1: %d\n", StackIsEmpty(double_stack));   
	
	for(i=0; i<5;++i)
	{
		StackPush(num_stack, &arr[i]);
		StackPush(double_stack, &arr_double[i]);
	}
 	  
  	printf("stack not empty should be 0: %d\n", StackIsEmpty(num_stack));   
  	printf("stack not empty should be 0: %d\n", StackIsEmpty(double_stack));   
 
  	printf("stack size is: %ld\n",  StackSize(num_stack));   
  	printf("stack size is: %ld\n",  StackSize(double_stack));   
  	
 	printf("%d\n",  *((int *)StackPeek(num_stack)));   
 	StackPop(num_stack);
	printf("%d\n",  *((int *)StackPeek(double_stack)));   
 	StackPop(double_stack);
 																 
  	printf("stack size is: %ld\n",  StackSize(num_stack)); 
  	printf("stack size is: %ld\n",  StackSize(double_stack));   
  	
   	  
 	printf("%d\n",  *((int *)StackPeek(num_stack)));   
 	printf("%ld\n",  StackCapacity(num_stack));   
 
  	printf("%f\n",  *((double *)StackPeek(double_stack)));   
 	printf("%ld\n",  StackCapacity(double_stack));  
 	
	StackDestroy(num_stack);
 	StackDestroy(double_stack);
 	return 0;
}
 
