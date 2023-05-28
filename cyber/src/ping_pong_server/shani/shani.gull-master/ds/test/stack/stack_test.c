#include "../../include/stack/stack.h"
#include <stdio.h>
#include <assert.h>

int main() 
{
	struct test
 	{
    		int i;
    		float f;
  	}test1 ,test2 ,test3 ,test4;
  	int i = 0;
  	
  	stack_t *my_stack = StackCreate(8 ,10);
  	printf("STACK CAPACITY: %lu\n" , StackCapacity(my_stack));
  	printf("STACK SIZE: %lu\n" , StackSize(my_stack));
  	StackIsEmpty(my_stack) ? printf("STACK IS EMPTY\n") : printf("STACK OCCUPIED\n");
  	if(!my_stack)
  	{
    		printf("Failed in creating stack");
    		return 1;
  	}
  	test1.i = 1;
  	test1.f = 1.1;
  	test2.i = 2;
  	test2.f = 2.2;
  	test3.i = 3;
  	test3.f = 3.3;
  	test4.i = 4;
  	test4.f = 4.4;
  	StackPush(my_stack ,(void *)&test1);
  	StackPush(my_stack ,(void *)&test2);
  	StackPush(my_stack ,(void *)&test3);
  	StackPush(my_stack,(void *)&test4);
  	StackIsEmpty(my_stack) ? printf("STACK IS EMPTY\n") : printf("STACK OCCUPIED\n");
  	printf("STACK SIZE: %lu\n" , StackSize(my_stack));
  
  	for(; i < 4; ++i)
  	{
    		struct test *test100 = (struct test *)StackPeek(my_stack);
    		printf("int: %d , float : %f\n" , test100->i , test100->f);
    		StackPop(my_stack);
  	}



    	StackDestroy(my_stack);

    return 0;
}




