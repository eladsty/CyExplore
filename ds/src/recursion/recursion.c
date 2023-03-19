
#include <stdio.h>

#include "recursion.h"
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

Node *FlipList(Node *node)
{
	
}