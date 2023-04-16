#include <stdio.h>/* printf */
#include <stdlib.h>/* malloc */
#include "/home/elad/elad.shem-tov/ds/include/stack.h"

struct queue
{
   stack_t *stack1;
   stack_t *stack2;
};
typedef struct queue queue_t;

 
void Enqueue(queue_t *queue, void *data)
{
   StackPush(queue->stack1, data);   
}

void *Dequeue(queue_t *queue)
{
   void *data = StackPeek(queue->stack1);
   unsigned size = 0;
   size = StackSize(queue->stack1);
   while(size > 1 )
   {
      StackPush( queue->stack2, StackPeek(queue->stack1));
      StackPop( queue->stack1 );
      --size;
   }

   data = StackPeek(queue->stack1);
   StackPop(queue->stack1);
   size = StackSize(queue->stack2);
   while( size > 0)
   {
      StackPush( queue->stack1, StackPeek(queue->stack2) );
      StackPop(queue->stack2);
      --size;
   }

   return data;
}


int main()
{
   int arr[] = {1,2,3,4,5,6};
   stack_t *main_stack = StackCreate(6, sizeof(int));  
   stack_t *stack2 = StackCreate(6, sizeof(int));  
 
   unsigned i = 0;
   queue_t *new_queue = (queue_t *)malloc(sizeof(queue_t));
   
   new_queue->stack1 = main_stack;
   new_queue->stack2 = stack2;

    for(i = 0; i < 6; ++i)
   {
      Enqueue(new_queue, &arr[i]);
   }

   for(i = 0; i < 1; ++i)
   {
      Dequeue(new_queue);
   }

 
   while( StackSize(new_queue->stack1) > 0 )
   {
      printf("%d \n", *(int *)StackPeek(new_queue->stack1));
      StackPop(new_queue->stack1);
   }

   StackDestroy(main_stack);
 
   
   free(new_queue);
   free(stack2);
   new_queue = NULL;

   return 0;
}

