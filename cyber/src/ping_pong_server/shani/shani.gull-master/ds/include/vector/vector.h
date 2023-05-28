#ifndef __VECTOR_H_CR4__ 
#define __VECTOR_H_CR4__ 
#include <stddef.h> /* size_t */
#include <stdio.h> /* printf */
#include <stdlib.h> /* reallocarray */
#include <assert.h> /* assert */

#define GROWTHFACTOR 1.25
#define SHRINKFACTOR (1 / GROWTHFACTOR)
#define ROUNDUP 0.75
typedef struct my_vector vector_t;

vector_t *VectorCreate(const size_t elem_amount, const size_t elem_size);
void VectorDestroy(vector_t *vector);
int VectorPushBack(vector_t *vector, const void *data);
int VectorPopBack(vector_t *vector);
size_t VectorSize(vector_t *vector);
int VectorResize(vector_t *vector, size_t new_size);
void *VectorAccessIndex(vector_t *vector, size_t index);


#endif /* __VECTOR_H_CR4__ */
