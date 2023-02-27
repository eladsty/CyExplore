 #include <stddef.h> /*size_t*/
 
 
typedef struct stack stack_t;

/* create stack*/
stack_t *StackCreate(size_t size, size_t elemsize);

/* remove stack*/
void StackDestroy(stack_t *p_stack);

/* add element to stack*/
void StackPush(stack_t *p_stack, void *data);
 
/* pop element from stack*/
void StackPop(stack_t *stack);

/* check what is the last element*/
void *StackPeek(stack_t *stack);

/* check if string is empty */
int StackIsEmpty(stack_t *stack);

/* check stack size*/
size_t StackSize(stack_t *stack);

/* return capacity*/
size_t StackCapacity(stack_t *stack);
