#ifndef __STACK_H_CR4__ 
#define __STACK_H_CR4__ 

#include <stddef.h> /* size_t */


typedef struct stack stack_t;
stack_t *StackCreate(const size_t size, const size_t elem_size); 
void StackDestroy(stack_t *stack_p); 
void StackPush(stack_t *stack_p, const void *data);
void StackPop(stack_t *stack_p); 
void *StackPeek(const stack_t *stack_p); 
int StackIsEmpty(stack_t *stack_p); 
size_t StackSize(stack_t *stack_p); 
size_t StackCapacity(stack_t *stack_p);



#endif /* __STACK_H_CR4__ */
