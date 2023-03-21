#include <stdio.h>	/*printf*/
#include <assert.h> /*asserts*/
#include <stddef.h> /*size_t*/

#include "fsa.h" 

#define WORDSIZE sizeof(size_t)                       
#define ALIGNED_BLOCK(num) (( (0 == num % 8) ? num : ((num >> 3) << 3) + WORDSIZE))
 
struct fsa
{
	size_t next_free;
};
 
/*--------------------------------------------------------*/
/* Status : 
 * Reviewer : Michael Evanov
 * Description : recieve the requested block size and number of blocks requires by user, and outputs the number of consecutive memory blocks needed for this module.
 * Arguments : user requested block size and blocks amount.
 * Return : size of memory needed for this module in bytes.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 */
 
 size_t FSASuggestSize(size_t block_size, size_t block_count)
{
	return (((ALIGNED_BLOCK(block_size) * block_count) + sizeof(fsa_t)) + 8);  
}


/*--------------------------------------------------------*/
/* Status : Approved
 * Reviewer : Hen 
 * Description : recieves memory block, initiates free list and returns pointer to pool.	
 * Arguments : recieves a pointer to allocated memory by user, block size and the total amount of allocated memory in bytes.
 * Return : pointer to pool.
 * Time Complexity - O(n).
 * Space Complexity - O(1). 
 */
 
fsa_t *FSAInit(void *memory_pool, size_t memory_size, size_t block_size)
{
	fsa_t *new_list = (fsa_t *)ALIGNED_BLOCK((size_t)memory_pool);
	size_t offset = 0;
	block_size = ALIGNED_BLOCK(block_size);
	new_list->next_free = sizeof(fsa_t);
 	
 	for(offset = new_list->next_free; offset < (memory_size - block_size); offset += block_size)
 	{
 		*(size_t *)((char *)new_list + offset) = offset + block_size;
 	}
	*(size_t *)((char *)new_list + offset) = 0;
	
	return new_list;
}
 

/*--------------------------------------------------------*/
/*  Status : Approved
 * Reviewer : Hen
 * Description : allocates one block to user.
 * Arguments : fsa_pool pointer.
 * Return : void pointer to block start. NULL if pool is empty.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 */


 
void *FSAAlloc(fsa_t *fsa)
{
 	void *offset = (void *)((char *)fsa + fsa->next_free);
 	if(0 == *(size_t *)offset)
 	{
 		return NULL;
 	}
 	fsa->next_free = *(size_t *)offset;
	return offset;
}

/*--------------------------------------------------------*/
/* Status : Approved
 * Reviewer : Hen
 * Description : frees one block from user.
	
 * Arguments : void pointer to block and pool pointer.
	
 * Return : void.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 */
void FSAFree(void *block, fsa_t *fsa)
{
	size_t offset = (char *)block-(char *)fsa;
	*(size_t *)block = fsa->next_free;
	fsa->next_free = offset;
}
 
 
 /*--------------------------------------------------------*/
/* Status : Approved
 * Reviewer : Hen
 * Description : frees one block from user.
	
 * Arguments : void pointer to block and pool pointer.
	
 * Return : void.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 */
 /*iterate through the pool, starting from the next free*/
size_t FSACountFree(const fsa_t *fsa_pool)
{
	size_t cnt = 0;
	size_t *ptr = NULL;
	for(ptr = (size_t *)((char *)fsa_pool + fsa_pool->next_free); 0 != *ptr ; ptr = (size_t *)((char *)fsa_pool + *ptr))
	{
		++cnt;
	}
	return cnt;
}

