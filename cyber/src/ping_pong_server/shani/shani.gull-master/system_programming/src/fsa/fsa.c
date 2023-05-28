#include "../../include/fsa/fsa.h"

#define WORDSIZE sizeof(size_t)
#define FSASIZE sizeof(fsa_t)
#define ALLIGN(x) (size_t)x % WORDSIZE

static size_t AmendedBlockSize(size_t bloke_size);


struct fsa
{
	size_t next;
};



/*--------------------------------------------------------*/
/* Status : approved
 * Reviewer : Amir
 * Description : recieve the requested block size and number of blocks requires by user, 
 				 and outputs the number of consecutive memory blocks needed for this module.
 * Arguments : user requested block size and blocks amount.
 * Return : size of memory needed for this module in bytes.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 */
size_t FSASuggestSize(size_t block_size, size_t block_count)
{
	block_size = AmendedBlockSize(block_size);
	return (block_count * block_size + FSASIZE + WORDSIZE);
}



/*--------------------------------------------------------*/
/* Status : approved
 * Reviewer : Amir
 * Description : recieves memory block, initiates free list and returns pointer to pool.
 * Arguments : recieves a pointer to allocated memory by user, block size and the total 
 			   amount of allocated memory in bytes.
 * Special notes : user must make sure void pointer is word alligned.
 * Return : pointer to pool.
 * Time Complexity - O(n).
 * Space Complexity - O(1). 
 */
fsa_t *FSAInit(void *memory_p, size_t memory_size, size_t block_size)
{
	unsigned char *memory_p_tmp = (unsigned char *)memory_p;
	fsa_t *my_list = NULL;
	size_t offset = 0;
	memory_size -= WORDSIZE;
	block_size = AmendedBlockSize(block_size);
	offset = memory_size - block_size;
	
	if (0 != ALLIGN(memory_p_tmp))
	{
		memory_p_tmp = memory_p_tmp + (WORDSIZE - ALLIGN(memory_p_tmp));
	}

	my_list = (fsa_t *)memory_p_tmp;
	my_list->next = offset;
	
	/* division due to my_list size and pointer arithmetics */
	my_list += (my_list->next / WORDSIZE);
	
	/* init all blocks */
	while (FSASIZE != offset)
	{
		offset -= block_size;
		my_list->next = offset;
		my_list -= block_size / WORDSIZE;
	}
	my_list->next = 0;
	return my_list;
}


/*--------------------------------------------------------*/
/* Status : approved
 * Reviewer : Amir
 * Description : allocates one block to user.
 * Arguments : fsa_pool pointer.
 * Return : void pointer to block start. NULL if pool is empty.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 */
void *FSAAlloc(fsa_t *fsa)
{
	void *actual = NULL;
	
	fsa -= 1; /* go to start of struct */
	
	if (0 == fsa->next)
	{
		return NULL;
	}
	
	actual = (void *)(fsa + (fsa->next / WORDSIZE));
	fsa->next = *(size_t *)actual;
	
	return actual;
}


/*--------------------------------------------------------*/
/* Status : approved
 * Reviewer : Amir
 * Description : frees one block from user.
	
 * Arguments : void pointer to block and pool pointer.
	
 * Return : void.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 */
void FSAFree(void *block, fsa_t *fsa)
{
	fsa -= 1; /* go to start of struct */
	
	*(size_t *)block = fsa->next;
	
	fsa->next = ((size_t)block - (size_t)fsa); 
}

/*--------------------------------------------------------*/
/* Status : approved
 * Reviewer : Amir
 * Description : provides information about free blocks.
	
 * Arguments : pool pointer.
	
 * Return : number of free blocks.
 * Time Complexity - O(n).
 * Space Complexity - O(1).
 */
size_t FSACountFree(const fsa_t *fsa)
{
	size_t count = 0;
	size_t offset;
	fsa_t *fsa_tmp = (fsa_t *)fsa;
	
	fsa_tmp -= 1;
	
	while (fsa_tmp->next)
	{
		++count;
		offset = fsa_tmp->next;
		fsa_tmp = (fsa_t *)fsa + (offset / WORDSIZE) - 1;
	}
	
	return count;
}



/* static funcs */
/* this func checks if block size requested from user is word aligned, ammends it if not, and adds the size of block_t to it for easier implementation of FSAInit() and FSASuggestSize() */
static size_t AmendedBlockSize(size_t block_size)
{
	if (0 != ALLIGN(block_size))
	{
		block_size += WORDSIZE - ALLIGN(block_size); 
	}
	return block_size;
}
