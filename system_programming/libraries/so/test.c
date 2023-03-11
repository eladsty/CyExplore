#include <dlfcn.h>  /*for dlopen dlclose and dlsym*/
 

int main(void)
{
	void *handle;
    void (*foo_func)(int);
    handle = dlopen("/home/el/elad.shem-tov/c/libraries/so/mylib.so", RTLD_LAZY);
    foo_func = (void(*)(int))dlsym(handle, "Foo");
    foo_func(4);

    dlclose(handle);
    return 0;
}
 
