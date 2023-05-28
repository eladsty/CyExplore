#include <stdlib.h> /* malloc */
#include <stddef.h> /* NULL size_t */
#include <stdio.h> /*printf */
#include <string.h> /* memcpy */
#include <assert.h> /* assert */
#include "../../include/stack/stack.h"


struct stack
{
	size_t size;
	size_t used;
	size_t elem_size;
	char *head;
};

/* #############################                    
status: approved          
reviewer: Adi            
description: this func create a stack 
return: ptr to stack or 0 if failed      
special notes: uses malloc          
#############################*/

stack_t *StackCreate(const size_t size, const size_t elem_size)
{
	stack_t *user_stack = malloc(sizeof(stack_t) + (size * elem_size));
	if (NULL == user_stack)
	{
		return 0;	
	}
	assert(size && elem_size);
	user_stack->head = (char *)(user_stack + (sizeof(stack_t)));
	user_stack->size = size;
	user_stack->used = 0;
	user_stack->elem_size = elem_size;
	return user_stack;
}

/* #############################                    
status: approved          
reviewer: Adi            
description: this func frees a dynamicly allocated stack pointer 
return: nothing     
special notes:        
#############################*/

void StackDestroy(stack_t *stack_p)
{
	assert (stack_p);
	free(stack_p);
	stack_p = NULL;
	
}

/* #############################                    
status: approved          
reviewer: Adi            
description: this func adds a data value to the stack        
return: nothing     
special notes:          
#############################*/

void StackPush(stack_t *stack_p, const void *data)
{
	assert (stack_p);
	assert (data);
	if (stack_p->used < stack_p->size)
	{
		memcpy((stack_p->head + (stack_p->used * stack_p->elem_size)), 
		(char *)data, stack_p->elem_size);
		stack_p->used += 1;
	}
	else
	{
		printf("stack is full");
	}
}

/* #############################                    
status: approved          
reviewer: Adi            
description: this func removes a data value from the stack        
return: nothing     
special notes:          
#############################*/

void StackPop(stack_t *stack_p)
{
	assert (stack_p);
	if (stack_p->used > 0)
	{
		--stack_p->used;
	}
	else
	{
		printf("stack is empty\n");
	}
}

/* #############################                    
status: approved          
reviewer: Adi            
description: this func returns a pointer to the most 
recently pushed data value on the stack        
return: pointer to the recent push value, assert if input is NULL    
special notes:          
#############################*/

void *StackPeek(const stack_t *stack_p)
{
	assert (stack_p);
	return (stack_p->head + ((stack_p->used - 1) * stack_p->elem_size));
}

/* #############################                    
status: approved          
reviewer: Adi            
description: this func determines if stack is empty      
return: 1 = empty, 0 = not empty   
special notes:          
#############################*/

int StackIsEmpty(stack_t *stack_p)
{
	assert (stack_p);
	return (!(stack_p->used)) ? 1 : 0;
}

/* #############################                    
status: approved          
reviewer: Adi            
description: this func returns stack size   
return: 1 = empty, 0 = not empty   
special notes:          
#############################*/

size_t StackSize(stack_t *stack_p)
{
	assert (stack_p);
	return stack_p->used;
}

/* #############################                    
status: approved          
reviewer: Adi            
description: this func returns stack capacity   
return: 1 = empty, 0 = not empty   
special notes:          
#############################*/

size_t StackCapacity(stack_t *stack_p)
{
	assert (stack_p);
	return stack_p->size * stack_p->elem_size;
}
