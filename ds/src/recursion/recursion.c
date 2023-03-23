
#include <stdio.h>/*to use stacks*/
#include <string.h>
#include <stdlib.h>/* malloc*/
#include <assert.h>

 #include "recursion.h"

 
 /* status: 
reviewer: 
description:  
return :  
*/
int FibonacciIteratively(int element_index)
{
	int n1 = 0, n2 = 1, n3 = 1, i = 0;
	if(element_index == 0)
	{
		return 0;
	}
	if(element_index == 1)
	{
		return 1;
	}
	n3 = n1 + n2;
	for(i = 1; i < element_index; ++i)
	{
		n3 = n1 + n2;
		n1 = n2;
		n2 = n3;
	}
	return n3;
}
/* status: 
reviewer:  
description: 
return :  
*/
int FibonacciRecursively(int element_index)
{
	if(element_index == 0)
	{
		return 0;
	}
	else if(element_index == 1)
	{
		return 1;
	}
	else
	{
		return (FibonacciRecursively(element_index - 1) + FibonacciRecursively(element_index - 2));
	}
		
}
/* status: 
reviewer:  
description:  
return :  
*/
 Node *FlipList(Node *node)
{ 
	if(NULL == node->next || NULL == node)
	{
		printf("this is the last node:  %p \n",node);
		return node;
	}
	FlipList(node->next);
	node->next->next = node;
	node->next = NULL;
}

/* status: 
reviewer:   
description:   
return :  
*/
size_t StrLenRecursive(const char *str)
{
	if('\0' == *str)
	{
		return  0;
	}
	return (1 + StrLenRecursive(str+1));
}
/* status: 
reviewer:   
description:  
return : 
*/
int  StrCmpRecursive(char *str1, char *str2)
{
	if('\0' == *str1 || *str1 != *str2)
	{
		return *str1-*str2;
	}
	return StrCmpRecursive(++str1,++str2);

}

/* status: 
reviewer:   
description:  
return : 
*/
char *StrCpyRecursive(char *dest, const char *src)
{
	char *dest_start = dest;
	if('\0' == *src)
	{
		*dest_start = '\0';
		return dest_start;
	}
	
	*dest = *src;
	dest = StrCpyRecursive(++dest, ++src);
	return dest_start;
 }

/* status: 
reviewer:  
description: 
return :  
*/
 char *StrCatRecursive(char *destination, const char *source)
 {
	if('\0' != *destination)
	{
		++destination;
		StrCatRecursive(destination, source);
	}
	else if ('\0' != *source)
	{
		StrCpyRecursive(destination, source);
	}
	--destination;
	return destination;
 }

/* status: 
reviewer:   
description:  
return :  
*/
char *StrStrRecursive(const char *haystack, const char *needle)
{
	if(0 == *needle)
	{
		return (char *)haystack;
	}
	if(0 == *haystack)
	{
		return NULL;
	}
	if(0 == strncmp(haystack, needle, StrLenRecursive(needle)))
	{
		return (char *)haystack;
	}
	
	return StrStrRecursive(++haystack, needle);

}
/* status: 
reviewer:   
description: 
return : 
*/

void *InsertSorted(struct stack *stack, void *item)
{
	void *head = StackPeek(stack);
	int temp_head = *(int *)head;
	if(StackIsEmpty(stack) || *(int *)item < *(int *)head)
	{
			StackPush(stack, item);
			return (head);
	}
	else
	{
			StackPop(stack);
			InsertSorted(stack, item);
			StackPush(stack, head);
			*(int *)StackPeek(stack) = temp_head;
	}
}
/* status: 
reviewer:   
description: 
return : 
*/
void SortStack(stack_t *stack)
{
	if(!StackIsEmpty(stack))
	{
			void *head = StackPeek(stack);
			StackPop(stack);
			SortStack(stack);
			InsertSorted(stack, head);
	}

}


 
