#ifndef __VECTOR_H__CR4__
#define __VECTOR_H__CR4__

#include <stddef.h> /*for size_t*/

typedef struct vector vector_t;

/*return size of vector*/
vector_t *VectorCreate(size_t element_amount, size_t element_size);

/*return size of vector*/
void VectorDestroy(vector_t *vector);

/*return size of vector*/
int VectorPush(vector_t *vector, const void *data);

/*return size of vector*/
int VectorPop(vector_t *vector);

/*return size of vector*/
size_t VectorSize(vector_t  *vector);

/*vector size*/
int VectorRealloc(vector_t  *vector, size_t new_size);

/*return size of vector*/
void *VectorAcessIndex(vector_t *vector, size_t index);

 
 
 
#endif
