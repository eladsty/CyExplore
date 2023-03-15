#include <stdio.h>

#include "memhead.h"

int x;

void PrintGlobalVariableAddress()
{
	printf("the address of x is: %p\n", &x);
}
