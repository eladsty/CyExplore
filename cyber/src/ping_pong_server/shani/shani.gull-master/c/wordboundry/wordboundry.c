#include "wordboundry.h" /*linking */
#include <stdlib.h> /*sizeof */
#include <stddef.h> /* size_t */

/* #############################*/
/* # Ex.1                      #*/
/* # status: approved          #*/
/* # reviewer: Adi             #*/
/* # description: this func    #*/
/* # will set first n bytes as #*/
/* # char.                     #*/
/* # return: ptr to arr        #*/
/* # special notes:            #*/
/* #############################*/

void *MemSet(void *s, int c, size_t n)
{
	unsigned char word_c[sizeof(size_t)], *temp = (unsigned char*)s;
	unsigned int i = 0;
	
	
	/*now make word side buffer of my char */
	while (i < sizeof(size_t))
	{
		word_c[i] = (unsigned char)c;
		++i;
	}

	while (n)
	{
		if (n > sizeof(size_t) && ((unsigned long)temp % sizeof(size_t) != 0))
		{
			*(void**)s = *(void**)word_c;
			n -= sizeof(size_t);
			temp += sizeof(size_t);
		}
		else
		{
			*temp = (char)c;
			--n;
			++temp;
		}
	}
	return s;
}


/* #############################*/
/* # Ex.2                      #*/
/* # status: approved          #*/
/* # reviewer: Adi             #*/
/* # description: this func    #*/
/* # will set first n bytes as #*/
/* # of dest as source         #*/
/* # return: ptr to arr        #*/
/* # special notes:            #*/
/* #############################*/

void *MemCpy(void *dest, const void *src, size_t n)
{
	unsigned int i = 0;
	char *temp = dest, word_src[sizeof(size_t)];
	const char *free_src = src;

	/*now make word side buffer of my source */
	
	while (n)
	{	
		if (n > sizeof(size_t) && (((unsigned long)temp % sizeof(size_t)) == 0))
		{
			while (i < sizeof(size_t))
			{
				word_src[i] = *free_src;
				++i;
				++free_src;
			}
			i = 0;
			*(void**)dest = *(void**)word_src;
			n -= sizeof(size_t);
			temp += sizeof(size_t);
		}
		else
		{
			*temp = *(char*)free_src;
			--n;
			++temp, ++free_src;
		}
	}
	return dest;
}

/* #############################*/
/* # Ex.2                      #*/
/* # status: approved          #*/
/* # reviewer: Adi             #*/
/* # description: this func    #*/
/* # will set first n bytes as #*/
/* # of dest as source even    #*/
/* # when the two are          #*/ 
/* # overlaping                #*/
/* # return: ptr to arr        #*/
/* # special notes:            #*/
/* #############################*/

void *MemMove(void *dest, const void *src, size_t n)
{
	const char *free_src = src;
	char *temp = dest;
	
	/*take my pointers not the n byte of my source and dest */
	temp += (n-1);
	free_src += (n-1);
	
	if (dest < src || dest == src)
	{
		MemCpy(dest, src, n);
		return dest;
	}
	/* now copy each byte and go back a memory location */
	else
	{
		while (free_src != src)
		{
			*temp = *free_src;
			--free_src, --temp;
		}
		*temp = *free_src;
		return dest;
	}
}


