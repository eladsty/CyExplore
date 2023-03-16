#include <stdio.h>	/*printf*/
#include <assert.h> /*asserts*/
#include <stddef.h> /*size_t*/

#include "fsa.h" 

#define WORDSIZE sizeof(size_t)
#define ALIGNED_BLOCK(num) (WORDSIZE - ((size_t)memory_pool % 8))
 
 /*
struct fsa_block
{
    size_t next;
};
 */

struct fsa
{
	/*size_t element_count; */
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
	fsa_t *fsa_start_point = NULL;
	size_t avail_size = 0;
	size_t aligned_block_size = ALIGNED_BLOCK(block_size);
	size_t offset_from_0 = sizeof(fsa_t);
	short bytes_to_align = (WORDSIZE - ((size_t)memory_pool % 8));
	fsa_t *start_new_fsa = NULL;
	assert(NULL != memory_pool);
	
	if(bytes_to_align)
	{
		 memory_pool = (char *)memory_pool + bytes_to_align;
		 memory_size -= bytes_to_align;
	}
	start_new_fsa = (fsa_t *)((char *)memory_pool);
	start_new_fsa->next_free = sizeof(fsa_t);
	fsa_start_point = (fsa_t *)(char *)start_new_fsa + sizeof(fsa_t);
	
	while(memory_size >= aligned_block_size)
	{
		*((size_t *)fsa_start_point) = offset_from_0;
		offset_from_0 += aligned_block_size;
		fsa_start_point->next = offset_from_0;
		fsa_start_point = (char *)fsa_start_point + aligned_block_size;
		memory_size -= ALIGNED_BLOCK(block_size); 
	}
	fsa_start_point = (char *)fsa_start_point - aligned_block_size;
	fsa_start_point->next = 0;
	
	return start_new_fsa;
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

 
void *FSAAlooc(fsa_t *fsa)
{
	void *block_p = NULL;
 	size_t next_free_offset = fsa->next_free;
	if(NULL == fsa || 0 == next_free_offset)
	{
		return NULL;
	}
	
 	block_p = ((sizeof(fsa_t) + fsa->next_free));
 	
	fsa->element_count = fsa->element_count - 1;
	return (void *)((char *)fsa + offset_next_element);
}

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
	size_t next_free_block = fsa->next_free;
	*((size_t *)block) = next_free_block;
	/*using the variable to save the offset of the current freed block*/
	next_free_block = ((size_t)block - (size_t)fsa + sizeof(fsa_t));
	fsa->next_free = next_free_block;
}
 
 
