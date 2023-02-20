#include <stdio.h>
 
#include "g.h"


extern g_s = 3;
int main()
{
	printf("%d\n",g_s);
	foo();
	printf("%d\n",g_s);
	return 0;
}
