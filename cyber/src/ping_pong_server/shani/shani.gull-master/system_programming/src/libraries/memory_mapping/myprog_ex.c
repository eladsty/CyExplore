#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>


int main(int argc, char *argv[], char *envp[])
{
	int a = 5, gl;
	void *handle;
	void (*func)(int);
	int (*barc)(void);
	void *j = malloc(sizeof(int));
	char local[1] = {2};
	static int n = 3;
	char *lit = "I'm not sure about this exercise";

	const char localconst[1] = {2};
	static const int nconst = 3;
	const char *lit_const = "I'm not sure about this exercise";
	char **env = envp;
	const char **env_const = envp;
	handle = dlopen("./libfoo.so", RTLD_LAZY);
	if (NULL == handle)
	{
		printf("handle fail");
	}
	*(void**)(&func) = dlsym(handle, "foo");
	if (NULL == func)
	{
		printf("func fail");
	}
	func(a);
	gl = dlsym(handle, "global");
	*(int**)(&barc) = dlsym(handle, "bar");
	barc();
	dlclose(handle);
	


	
	free(j);

	j = NULL;

	return 0;
}
