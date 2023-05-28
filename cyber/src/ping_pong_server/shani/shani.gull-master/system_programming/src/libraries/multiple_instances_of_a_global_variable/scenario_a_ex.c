#include <stddef.h>
#include <stdio.h>
#include <dlfcn.h>
#include "scenario_a.h"

int x;

int main()
{
	char *handle = NULL;
	void (*foofunc)(void);

	printf("%p\n", &x);
	handle = (char *)dlopen("./libscenario_a.so", RTLD_LAZY);
	if (NULL == handle)
	{
		printf("handle fail");
		return 1;
	}
	
	*(void**)(&foofunc) = dlsym(handle, "PrintGlobalVariableAddress");
	
	if (NULL == foofunc)
	{
		printf("foo fail");
		return 1;
	}
	
	foofunc();
	
	dlclose(handle);

	return 0;
}
