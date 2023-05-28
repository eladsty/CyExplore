#include <stdio.h>
#include <stdlib.h>
#include "lib.h"
static int boo(void);
static float glob = 3.5;
extern int bar(void)

{
	return 0;
}

void foo(int num)
{
	printf("%d\n", num);
	boo();
	glob +=1;
	int a = 5;
	void *j = malloc(sizeof(int));
	char local[1] = {2};
	static int n = 3;
	char *lit = "I'm not sure about this exercise";
	const char localconst[1] = {2};
	static const int nconst = 3;
	const char *lit_const = "I'm not sure about this exercise";
	
	bar();
	free(j);
	j = NULL;
}

static int boo(void)
{
	return '1';
}

