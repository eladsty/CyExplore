#include <stddef.h>
#include <dlfcn.h>
#include <stdio.h>
#include "staticlib.h"

int main(void)
{
	char *handle = NULL;
	char *handle2 = NULL;
	void (*foofunc)(void);
	void (*foo2func)(void);


	PrintGlobalVariableAddress();
	handle = (char *)dlopen("./libdynamic1.so", RTLD_LAZY);
	if (NULL == handle)
	{
		printf("handle fail");
		return 1;
	}
	
	*(void**)(&foofunc) = dlsym(handle, "foo");
	if (NULL == foofunc)
	{
		printf("foo fail");
		return 1;
	}
	foofunc();
	dlclose(handle);
	
	handle2 = (char *)dlopen("./libdynamic2.so", RTLD_LAZY);
	if (NULL == handle)
	{
		printf("handle fail\n");
		return 1;
	}
	*(void**)(&foo2func) = dlsym(handle2, "foo2");
	if (NULL == foo2func)
	{
		printf("foo2 fail\n");
		return 1;
	}
	
	foo2func();
	
	
	dlclose(handle2);
	return 0;
}

