#include <stdio.h>
#include <stdlib.h>
#include "../ds/include/stack/stack.h"

typedef struct queue
{
	stack_t *input;
	stack_t *output;
}queue_t;

queue_t *Create(size_t num_elements, size_t elem_size)
{
	queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
	if (NULL == queue)
	{
		return NULL;
	}
	queue->input = StackCreate(num_elements, elem_size);
	queue->output = StackCreate(num_elements, elem_size);
	if (NULL == queue->input || NULL == queue->output)
	{
		StackDestroy(queue->input);
		StackDestroy(queue->output);
		free(queue);
		queue = NULL;
		return NULL;
	}
	return queue;
}

void EnQueue(void *data, queue_t *queue)
{
	StackPush(queue->input, data);
	return;
}

void Transfer(stack_t *from, stack_t *to)
{
	while (StackSize(from))
	{
		StackPush(to, StackPeek(from));
		StackPop(from);
	}
	return;
}
void *DeQueue(queue_t *queue)
{
	void *data = NULL;
	Transfer(queue->input, queue->output);
	data = StackPeek(queue->output);
	StackPop(queue->output);
	Transfer(queue->output, queue->input);
	return data;
}

int main()
{
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	size_t i = 0;
	queue_t *queue = Create(10, sizeof(int));
	for (i = 0; i < 10; ++i)
	{
		EnQueue(&arr[i], queue);
	}
	for (i = 0; i < 10; ++i)
	{
		printf("%ld number is %d\n", i, *(int *)DeQueue(queue));
	}
	StackDestroy(queue->input);
	StackDestroy(queue->output);
	free(queue);
	queue = NULL;
	return 0;
}