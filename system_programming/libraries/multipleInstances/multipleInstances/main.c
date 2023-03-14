#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "memhead.h"

int main()
{
	void *handle_foo = NULL;
 	void *handle_foo2 = NULL;
	void (*func)();
	void (*func2)();
		
 	PrintGlobalVariableAddress();
 		
	handle_foo = dlopen("dynamic_foo/lib_dynamic.so", RTLD_LOCAL | RTLD_LAZY);
	if(!handle_foo)
	{
		printf("ERROR %s\n", dlerror());
		printf("Use \'export LD_LIBRARY_PATH=<.so location>:$LD_LIBRARY_PATH\'\n");
		return 1;
	}
	
	*(void **)&func = dlsym(handle_foo, "Foo");
	if(dlerror())
	{
		printf("Failed to retrieve symbol \'Foo\'\n");
		return 1;
	}
	
	(*func)();
	dlclose(handle_foo);

	handle_foo2 = dlopen("dynamic_foo2/lib_dynamic2.so", RTLD_LOCAL | RTLD_LAZY);
	if(!handle_foo)
	{
		printf("ERROR %s\n", dlerror());
		printf("Use \'export LD_LIBRARY_PATH=<.so location>:$LD_LIBRARY_PATH\'\n");
		return 1;
	}
	
	*(void **)&func2 = dlsym(handle_foo2, "Foo2");
	if(dlerror())
	{
		printf("Failed to retrieve symbol \'Foo2\'\n");
		return 1;
	}
	
	(*func2)();
	dlclose(handle_foo2);
 	
    return 0;
}

