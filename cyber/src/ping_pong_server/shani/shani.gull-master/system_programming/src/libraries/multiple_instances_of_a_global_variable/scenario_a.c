#include "scenario_a.h"
#include <stdio.h>

int x;

void PrintGlobalVariableAddress(void)
{
	printf("%p\n", &x);
}
