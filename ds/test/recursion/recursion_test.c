#include <stdio.h>
#include <stdlib.h>

#include "recursion.h"

struct stack 
{
	size_t element_size;
	size_t capacity;
	size_t current_size;
	void *start;
};

/*
	status:approved
	description: create new stack and return pointer to it (if not NULL)
	Reviewer: Nimrod
	Return: stack_t pointer

*/
 void *ReturnStart(stack_t *stack)
{
	return stack->start;
}

stack_t *StackCreate(size_t size, size_t elemsize)
{
	stack_t *new_stack = (stack_t *)malloc(sizeof(stack_t));
	if(NULL == new_stack)
	{
		return NULL;
	}
	
	new_stack->element_size = elemsize;
	new_stack->capacity = size*elemsize;
	new_stack->current_size = 0;
	new_stack->start = malloc(size*elemsize);
	
	if(NULL == new_stack->start)
	{
		return NULL;
	}
	return new_stack;
}


/*
	status:approved
	description:  free a stack from memory
	Reviewer: Nimrod
	Return:  none

*/
void StackDestroy(stack_t *stack)
{
	free((char *)stack->start - stack->element_size * stack->current_size);
	stack->start = NULL;
	free(stack);
	stack = NULL;
}

/*
	status:approved
	description: add new data to the stack
	Reviewer: Nimrod
	Return: none

*/
void StackPush(stack_t *p_stack, void *data)
{
	if(p_stack->current_size >= p_stack->capacity)
	{
		return;
	}
	
	p_stack->current_size = p_stack->current_size + 1;
 	p_stack->start = p_stack->element_size + (char *)p_stack->start;
	memcpy(p_stack->start, data, p_stack->element_size);
}

/*
	status:approved
	description: remove item from the stack.
	Reviewer: Nimrod
	Return: none

*/
void StackPop(stack_t *stack)
{
	if (0 == stack->current_size)
	{
		return;
	}	
	
	stack->start = ((char*)stack->start - stack->element_size);
	stack->current_size = stack->current_size - 1;; 
}

/*
	status:approved
	description: check the top item on the stack
	Reviewer: Nimrod
	Return: void pointer

*/

void *StackPeek(stack_t *stack)
{
	return stack->start;
}


/*
	status:approved
	description: check if stack is empty, if it does return 1 else 0
	Reviewer: Nimrod
	Return: int

*/
int StackIsEmpty(stack_t *stack)
{
	if(0 == stack->current_size) 
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

/*
	status:approved
	description: number of items on the stack
	Reviewer: Nimrod
	Return: size_t 

*/
size_t StackSize(stack_t *stack)
{
	return stack->current_size;
}

/*
	status:approved
	description: check stack capactiy
	Reviewer: Nimrod
	Return: size_t

*/
size_t StackCapacity(stack_t *stack)
{
	return stack->capacity;
}
void PrintStack(stack_t *stack)
{
        size_t i = 0;
        void *curr_data = NULL;
        void *arr[10] = {NULL};
        while (!StackIsEmpty(stack))
        {
                curr_data = StackPeek(stack);
                printf("%d --> ", *((int *)curr_data));
                StackPop(stack);
                arr[i] = curr_data;
                ++i;
        }
        while (i)
        {
                StackPush(stack, arr[i - 1]);
                --i;
        }
        printf(" END OF STACK\n");
}

  
int main()
{
 	Node *n1 = (Node *)malloc(sizeof(Node));
 	Node *n2 = (Node *)malloc(sizeof(Node));
 	Node *n3 = (Node *)malloc(sizeof(Node));
	Node *n4 = (Node *)malloc(sizeof(Node));

	char dest[] = {"helo"};
    char needle[] = "lo";
	char copy[40] = "" ;
	char copy2[40] = "hello " ;
	char source[] = "elad" ;
	char source2[] = "elad" ;
		int i = 0;

	int arr[] = {11,33,-4,5,77,26,14,51,87,123};

	stack_t *num_stack = NULL;
	num_stack = StackCreate(10 ,sizeof(int)); 
	for(i = 0; i<7; ++i)
	{
		printf("for %d, iterative fibonannci : %d\n",i,FibonacciIteratively(i));
		printf("for %d, recursive fibonannci: %d\n",i,FibonacciRecursively(i));
	}
	
	n1->next = n2;
	n2->next = n3;
	n3->next = n4;
	n4->next = NULL;
 	printf("should be null %p,\n, this: %p should be the same as: %p \n",n3->next, n1->next, n2);
	FlipList(n1); 
	printf("should be null %p,\n, this: %p should be the same as: %p \n",n1->next, n3->next ,  n2);

	printf("*******\nshould be null %p,\n, this: %p should be the same as: %p \n",n1->next, n4->next ,  n3);
	printf("**ererere*\nshould be null %p,\n, this: %p should be the same as: %p \n",n1->next, n3->next ,  n2);


	for(i=0; i<7;++i)
	{
		StackPush(num_stack, &arr[i]);
	}
	SortStack(num_stack);
	PrintStack(num_stack);
	
 

 	 printf("size of string is 5: %ld\n", StrLenRecursive("hello"));  
 	 printf("compare 2 strings should be 0: %d\n", StrCmpRecursive("hello","hello"));  
 	 printf("compare 2 strings should be non 0: %d\n", StrCmpRecursive("hello4","hello"));  
 	 printf("Should print Recursion: %s\n", StrCpyRecursive(copy,source));  
  	 printf("StrCat(source is Recursion): %s\n",  StrCatRecursive(copy2,source2));  
 	 printf("strstr %s \n", StrStrRecursive(dest, needle)); 

	 free(num_stack); 
	 num_stack = NULL; 

	free(n1);
	free(n2);
	free(n3);
	free(n4);
 	n4 = NULL;
 	n1 = NULL;
	n2 = NULL;
	n3 = NULL;
	
	return 0;
}	
