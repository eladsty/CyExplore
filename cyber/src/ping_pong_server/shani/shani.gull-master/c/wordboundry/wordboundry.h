#ifndef __WORDBOUNDRY_H_CR4__ 
#define __WORDBOUNDRY_H_CR4__ 
#include "wordboundry.h" /*linking */
#include <stdlib.h> /*sizeof */
#include <stddef.h> /* size_t */

void *MemSet(void *s, int c, size_t n);
void *MemCpy(void *dest, const void *src, size_t n);
void *MemMove(void *dest, const void *src, size_t n);

#endif /* __WORDBOUNDRY_H_CR4__ */
