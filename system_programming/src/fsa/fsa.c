#include <stdio.h>	/*printf*/
#include <assert.h> /*asserts*/
#include <stddef.h> /*size_t*/

#include "fsa.h" 

#define WORDSIZE sizeof(size_t)
#define ALIGNED_BLOCK(num) (num = (((num >> 3) << 3) + WORDSIZE))

 
struct fsa
{
	size_t element_count;
	size_t next_free;
};

/*--------------------------------------------------------*/
/* Status : 
 * Reviewer : 
 * Description : recieve the requested block size and number of blocks requires by user, and outputs the number of consecutive memory blocks needed for this module.
 * Arguments : user requested block size and blocks amount.
 * Return : size of memory needed for this module in bytes.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 */
 
 size_t FSASuggestSize(size_t block_size, size_t block_count)
{
	return ((ALIGNED_BLOCK(block_size) * block_count) + sizeof(fsa_t));  
}


/*--------------------------------------------------------*/
/* Status : 
 * Reviewer : 
 * Description : recieves memory block, initiates free list and returns pointer to pool.	
 * Arguments : recieves a pointer to allocated memory by user, block size and the total amount of allocated memory in bytes.
 * Return : pointer to pool.
 * Time Complexity - O(n).
 * Space Complexity - O(1). 
 */
 
fsa_t *FSAInit(void *memory_pool, size_t memory_size, size_t block_size)
{
	fsa_t *new_fsa = NULL;
	assert(NULL != memory_pool);
	
	/*
	
	ALIGNED_BLOCK(memory_pool);
	
	*/ 
	new_fsa = (fsa_t *)((char *)memory_pool);
	new_fsa->next_free = sizeof(fsa_t);
	new_fsa->element_count = ((memory_size - sizeof(fsa_t)) / ALIGNED_BLOCK(block_size));
	
	return new_fsa;
}
 
 
/*--------------------------------------------------------*/
/* Status : 
 * Reviewer : 
 * Description : allocates one block to user.
 * Arguments : fsa_pool pointer.
 * Return : void pointer to block start. NULL if pool is empty.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 */
 
 /*
void *FSAAlooc(fsa_t *fsa)
{
	size_t offset_next_element = fsa->next_free;
	void *block_p = NULL;
 
	if(0 == fsa->element_count || NULL == fsa)
	{
		return NULL;
	}
 	block_p = (sizeof(fsa_t) + fsa->next_free));
 	
	fsa->element_count = fsa->element_count - 1;
	return (void *)((char *)fsa + offset_next_element);
}
*/

/*--------------------------------------------------------*/
/* Status : 
 * Reviewer : 
 * Description : frees one block from user.
	
 * Arguments : void pointer to block and pool pointer.
	
 * Return : void.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 */
void FSAFree(void *block, fsa_t *fsa)
{
 
}

 
