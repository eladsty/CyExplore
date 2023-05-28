#include <stdio.h>
#include "staticlib.h"

int x;

void PrintGlobalVariableAddress(void)
{
	printf("%p\n", &x);
}
