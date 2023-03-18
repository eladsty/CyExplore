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

int main(void)
{
 	
	size_t block_size = BSIZE, block_count = AMOUNT, 
			memory_size = 0 ,i = 0 , count = 0;
	void *memory_p = NULL;
	char *blocks[AMOUNT];
	char strings[8][40] = {"123123123", "234234234", "345345345","456456456", 
					"567567567", "zxczxczc", "asdasdasd", "qweqweqwe"};
	
	char *action = "  BOOM!!";
	
	fsa_t *flist = NULL;
	memory_size = FSASuggestSize(block_size, block_count);
	
	memory_p = malloc(memory_size);
	if (NULL == memory_p)
	{
		printf("malloc failed\n");
		return 1;
	}
	
	flist = FSAInit(memory_p, memory_size, block_size);
	
	printf("user block count is %ld\npool block count is %ld\n", 
				block_count, FSACountFree(flist));
	
	count = FSACountFree(flist);			
	for (i = 0; i < count; ++i)
	{
		blocks[i] = (char *)FSAAlloc(flist);
		memcpy(blocks[i], strings[i], BSIZE);
	}	
	
	
	printf("\n\n");
	for (i = 0; i < block_count; ++i)
	{
		printf("%s\n", blocks[i]);
	}
	
	
	printf("\n\nuser block count after full allocation is: %ld\n", FSACountFree(flist));	
	
	FSAFree(blocks[3], flist);
	FSAFree(blocks[5], flist);
	printf("\n\nuser block count after 2 free is %ld\n", FSACountFree(flist));	
	blocks[3] = (char *)FSAAlloc(flist);
	strcpy(blocks[3], action);
	blocks[5] = (char *)FSAAlloc(flist);
	strcpy(blocks[5], action);

	printf("\n\nboth freed blocks were allocated to --> %s \n", action);	
	printf("\n\nuser block count after full allocation is: %ld\n\n", FSACountFree(flist));	
	for (i = 0; i < block_count; ++i)
	{
		printf("%s\n", blocks[i]);
	}
	
	
	free(memory_p);

	return 0;
}

