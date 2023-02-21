#include <assert.h> /*for asserts*/

#include "wordboundary.h"

void *MemSet(void *s, int c, size_t n) 
{
	char *p_char = NULL;
	char cCopy = (char)c;
    size_t i = 0;
    char buffer[sizeof(size_t)];
    
    assert(NULL != s); 
    
    p_char = (char *)s;
    
    
    
    while((0 != (size_t)p_char % 8) && (n > 0))
    {
    	*p_char = cCopy;
    	++p_char;
    	--n;
    }
    
    for(; i < sizeof(size_t); ++i)
    {
        buffer[i] = cCopy;
    }
   
    while(n >= sizeof(size_t))
    {
    	*(size_t *)p_char = *(size_t *)buffer;
    	p_char += 8;
    	n = n-8;
    }
   	
    while(n > 0)
    {
    	*p_char = cCopy;
    	++p_char;
	 	--n;
    }
    
    return s;
}    
 
 
 
void *MemCpy(void *dest, const void *src, size_t n)
{
 	void *start = dest;
	size_t i = 0;
	assert(NULL != dest && NULL != src); 
	
	
		while(n>8)
		{
			*((size_t *)dest + i) = *((size_t *)src + i);
			i+= 8;
			n = n - 8;
			
		}
	 while (0 < n)
	{	
		*((char *)dest + i) = *((char *)src + i);
		n = n - 1;
		++i;	
	}
	 
	return start;
}


void *MemMove(void *dest, const void *src, size_t n)
{
	void *dest_p = dest;
	size_t i = 0;
		
	assert(NULL != dest && NULL != src);
	
	if ((dest_p > src) && (((size_t)dest_p - (size_t)src) < n))
	{
		while (i < n)
		{
			*((char *)dest_p + (n - 1) - i) =
			*((char *)src + (n - 1) - i);
			++i;
		}
	}
	
	else
	{
		dest_p = MemCpy(dest_p , src, n);
	} 
	
	return dest;


}






















 
