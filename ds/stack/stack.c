#include <stddef.h> /*size_t*/
#include <stdlib.h>/*malloc*/
#include <string.h>/*memcpy*/
#include <stdio.h>/*printf*/

#include "stack.h"

struct stack 
{
	size_t element_size;
	size_t capacity;
	size_t current_size;
	void *start;
};

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

void StackDestroy(stack_t *stack)
{
	free((char *)stack->start - stack->element_size * stack->current_size);
	stack->start = NULL;
	free(stack);
	stack = NULL;
}

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


void StackPop(stack_t *stack)
{
	if (0 == stack->current_size)
	{
		return;
	}	
	
	stack->start = ((char*)stack->start - stack->element_size);
	stack->current_size = stack->current_size - 1;; 
}

void *StackPeek(stack_t *stack)
{
	return stack->start;
}



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


size_t StackSize(stack_t *stack)
{
	return stack->current_size;
}


size_t StackCapacity(stack_t *stack)
{
	return stack->capacity;
}




