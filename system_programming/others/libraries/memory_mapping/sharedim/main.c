#include <dlfcn.h> /* Used for dlopen, dlsym, dlclose */
#include <stdio.h> /* Used for prints */
#include <stddef.h> /* Used for NULL definition */

int main(int argc, char *argv[], char **envp)
{
	void *handle = NULL;
	void (*func)(int);
 
 	
	printf("dlopen is below\n");
	
	handle = dlopen("libmemory.so", RTLD_LOCAL | RTLD_LAZY);
	if(!handle)
	{
		printf("ERROR %s\n", dlerror());
		printf("Use \'export LD_LIBRARY_PATH=<.so location>:$LD_LIBRARY_PATH\'\n");
		return 1;
	}
	
	*(void **)&func = dlsym(handle, "ExternFunc");
	if(dlerror())
	{
		printf("Failed to retrieve symbol \'ExternFunc\'\n");
		return 1;
	}
 
	
	(*func)(15);
	dlclose(handle);
	
	(void)argc;
	(void)argv;
	(void)envp;
	
	return (0);
}


