#include "../../include/stack/stack.h"
#include "../../include/recursion/recursion.h"
#include <stdlib.h> /* Used for malloc and free functions */

int main(void)
{
	int i = 0;
	node_t *tail, *head, *one;
	stack_t *my_stack;
	char str[] = {"shani"}, str2[] = {"shab elm to  sha "}, buffer[20];

	printf("--- Fibonacci ---\n");
	while (i < 20)
	{
		printf("%d \n", FibonacciRecursively(i));
		++i;
	}
	i = 0;
	while (i < 20)
	{
		printf("%d \n", FibonacciIteratively(i));
		++i;
	}

	printf("--- FlipList ---\n");
	tail = (node_t *)malloc(sizeof(size_t));
	head = (node_t *)malloc(sizeof(size_t));
	one = (node_t *)malloc(sizeof(size_t));
	if (NULL == head || NULL == tail || NULL == one)
	{
		return 1;
	}
	tail->next = NULL;
	head->next = one;
	one->next = tail;

	FlipList(head);
	if (tail->next == one && one->next == head && head->next == NULL)
	{
		printf("FlipList successfull\n");
	}
	free(head);
	free(tail);
	free(one);

	printf("--- StackSort ---\n");
	my_stack = StackCreate(5, sizeof(int));
	for (i = 0; i < 5; ++i)
	{
		printf("%d \n", i);
		StackPush(my_stack, &i);
	}
	printf("->->->->\n");
	SortStack(my_stack);
	for (i = 0; i < 5; ++i)
	{
		printf("%d \n", *(int *)StackPeek(my_stack));
		StackPop(my_stack);
	}
	StackDestroy(my_stack);

	printf("--- Strlen ---\n");
	printf("in the string %s there are %ld charachters\n", str, StrLenRecursive(str));

	printf("--- Strcmp ---\n");
	if ((strcmp(str, str2) > 0 && StrCmpRecursive(str, str2) > 0) ||
		(strcmp(str, str2) < 0 && StrCmpRecursive(str, str2) < 0) ||
		(strcmp(str, str2) == 0 && StrCmpRecursive(str, str2) == 0))
	{
		printf("success\n");
	}
	else
	{
		printf("fail\n");
	}

	printf("--- Strcpy ---\n");
	printf("%s \n", StrCpyRecursive(buffer, str2));

	printf("--- Strcat ---\n");
	printf("%s \n", StrCatRecursive(str2, str));

	printf("--- Strstr ---\n");
	StrCpyRecursive(buffer, StrStrRecursive(str2, str));
	printf("%s \n", buffer);

	return (0);
}
