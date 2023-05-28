#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

int main(int argc, char *argv[], char *envp[])
{
	int a = 5;
	void *j = malloc(sizeof(int));
	char local[1] = {2};
	static int n = 3;
	char *lit = "I'm not sure about this exercise";
	const char localconst[1] = {2};
	static const int nconst = 3;
	const char *lit_const = "I'm not sure about this exercise";
	char **env = envp;
	const char **env_const = envp;


	bar();
	foo(a);
	free(j);
	j = NULL;
	return 0;
}



