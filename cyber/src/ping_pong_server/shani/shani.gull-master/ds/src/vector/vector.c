#include <stddef.h> /* size_t */
#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <string.h> /* memcpy */
#include <malloc.h> /*  reallocarray and malloc */
#include "/home/shani/shani.gull/ds/include/vector/vector.h"



struct my_vector 
{
	size_t capacity; /* created by create or by resize */
	size_t curr_size; /* increases as the user req more memory */
	size_t elem_size;
	char *start;
};

/* #############################                    
status: approved          
reviewer: Michael A             
description: this func create a vector data structure 
return: ptr to struct containing vector or 0 if failed      
special notes: uses malloc twice         
#############################*/

vector_t *VectorCreate(const size_t elem_amount, const size_t elem_size)
{
	vector_t *vector = (vector_t *)malloc(sizeof(vector_t));
	if (NULL == vector)
	{
		return NULL;
	}
	vector->capacity = elem_amount;
	vector->curr_size = 0;
	vector->elem_size = elem_size;
	vector->start = (char *)malloc(elem_amount * elem_size);
	if (NULL == vector->start)
	{
		free(vector);
		vector = NULL;
		return NULL;
	}
	return vector;
}

/* #############################                    
status: approved          
reviewer: Michael A           
description: this func frees a pointer allocated to vector data structure 
return: void     
special notes:        
#############################*/

void VectorDestroy(vector_t *vector)
{
	assert(vector);
	free(vector->start);
	vector->start = NULL;
	free(vector);
	vector = NULL;
}

/* #############################                    
status: approved          
reviewer: Michael A           
description: this func adds element to end of vector data structure 
return: 1 for success or 0 for fail     
special notes:        
#############################*/

int VectorPushBack(vector_t *vector, const void *data)
{
	int boolean;
	assert(vector);
	assert(data);
	
	if (vector->capacity == vector->curr_size)
	{
		boolean = VectorResize(vector, ((vector->capacity * GROWTHFACTOR) + ROUNDUP));
		if (0 == boolean)
		{
			return 0;
		}
		vector->curr_size = vector->curr_size * SHRINKFACTOR + ROUNDUP;
	}
	
	
	memcpy((vector->start + ((vector->capacity - vector->curr_size - 1) * vector->elem_size)), 
		data, vector->elem_size);
	vector->curr_size += 1;
	return 1;
}

/* #############################                    
status: approved          
reviewer: Michael A           
description: this func removes element from end of vector data structure 
return: 1 for success or 0 for fail     
special notes:        
#############################*/

int VectorPopBack(vector_t *vector)
{
	int boolean;
	assert(vector);
	
	if (0 == vector->curr_size)
	{
		printf("no elements to pop");
		return 0;
	}

	vector->curr_size -= 1;

	if ((vector->capacity * SHRINKFACTOR + ROUNDUP) > vector->curr_size)
	{
		boolean = VectorResize(vector, (vector->capacity * SHRINKFACTOR + ROUNDUP));
		if (0 == boolean)
		{
			printf("realloc failed");
			return 0;
		}
	}
	return 1;
}

/* #############################                    
status: approved          
reviewer: Michael A           
description: this func returns number of used element of vector data structure 
return: 1 for success or 0 for fail     
special notes:        
#############################*/

size_t VectorSize(vector_t *vector)
{
	assert(vector);
	return vector->curr_size;
}

/* #############################                    
status: approved          
reviewer: Michael A           
description: this func resizes the capacity of vector data structure 
return: 1 for success or 0 for fail     
special notes:        
#############################*/

int VectorResize(vector_t *vector, size_t new_size)
{
	assert(vector);
	vector->start = (char *)realloc(vector->start, (new_size * vector->elem_size));
	if (NULL == vector->start)
	{
		printf("resize failed\n");
		return 0;
	}
	vector->curr_size = new_size;
	vector->capacity = new_size;
	return 1;
	
}

/* #############################                    
status: approved          
reviewer: Michael A           
description: this func returns pointer to element of vector data structure 
requested by the user
return: pointer to requested element     
special notes:        
#############################*/

void *VectorAccessIndex(vector_t *vector, size_t index)
{
	assert(vector);
	if (index > vector->curr_size)
	{
		printf("out of bounds of vector\n");
		return NULL;
	}
	return (vector->start + (vector->elem_size * (vector->capacity - index - 1)));
}
