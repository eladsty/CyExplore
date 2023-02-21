#ifndef __WORDBOUNDARY_H__CR4__
#define __WORDBOUNDARY_H__CR4__

 

#include <stddef.h> /*for size t*/



/*
Status:
*description: fills the first n bytes of memory area pointed to by s with contant byte c and 
*returns: a pointer to the memory area s
*/

void *MemSet(void *s, int c, size_t n);


/*
Status:
*description: copies n bytes from memory area src to dest
*returns: a pointer to the memory area s
*/
void *MemCpy(void *dest, const void *src, size_t n);
 


 /*
Status:
*description: copies n bytes from memory area src to dest
*returns: a pointer to the memory area s
*/
void *MemMove(void *dest, const void *src, size_t n);


 


#endif
