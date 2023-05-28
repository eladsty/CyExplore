#include "g.h"
#include <stdio.h>
#include "a.c"

int main()
{

	printf("%d\n", g_s);
	foo(g_s);
	printf("%d\n", g_s);

	return 0;
}
