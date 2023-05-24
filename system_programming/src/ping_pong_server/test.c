#include <stdio.h>
int x = 10;

void foo()
{
	static int i = 5;
	x = 5;
}

int main(void)
{
	printf("hello!");
	foo();
	return 0;
}
