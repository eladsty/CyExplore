#include <stddef.h>
#include <assert.h>
#include <stdio.h>

void *MemCpy(void *dest, const void *src, size_t n)
{
 	void *start = dest;
	
	assert(NULL != dest && NULL != src); 

		while(n > sizeof(size_t))
		{
			*((size_t *)dest) = *((size_t *)src);
			
			dest = (size_t *)dest + 1;
			src = (size_t *)src + 1;  
			n-= sizeof(size_t);
		}
		
	 while(n > 0)
	{	
		*((char*)dest)  = *((char *)src);
		src = (char *)src + 1;
		dest = (char *)dest + 1;
		--n;
	}
	return start;
}

int main(void)
{
	char src[] = "12345678912345 werwerwer werwgqwe";
	char cpy[30];
	MemCpy(cpy, src,10);
	printf("the string that was copy: %s", cpy);
	
	return 0;
}
