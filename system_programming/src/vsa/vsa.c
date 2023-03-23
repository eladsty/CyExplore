#include <stddef.h> /* Used for size_t type */
#include <stdlib.h> /* abs  */
#include <stdio.h> /* printf for debug*/
#include "../../include/vsa.h"


#define VSASIZE sizeof(vsa_t)
#define WORDSIZE sizeof(size_t)
#define DEADBEEF (3735928559)
#define CHANGE_STATUS (-1)

#define ALIGNEDOWN(b) (((b) >> (3)) << (3))

#define ALIGNED_BLOCK(b) (((b) % WORDSIZE) ?\
	WORDSIZE - (b) % WORDSIZE + (b) : (b))


#ifndef NDEBUG
	#define BLOCKID (0xdeb49)
	#define SETDEBUG(block) \
		{ \
			(block)->debug = BLOCKID; \
		}
 		#define FREEDEBUG(free_p) \
		{ \
			if (free_p->block_size > 0) \
			{ \
				printf("VSAFree --> block was already freed. : %s\n", __FILE__); \
				exit(1); \
			} \
			if (free_p->debug != BLOCKID) \
			{ \
				printf("VSAFree --> This block was never allocated : %s\n", __FILE__); \
				exit(1); \
			} \
		}

#endif



struct vsa
{
	signed long block_size;
	#ifndef NDEBUG
    long debug;
	#endif
};



 



/*--------------------------------------------------------*/
/* Status : approved.
 * Reviewer : shlomi.
 * Description : Recieves memory pool, initiate vsa struct,
 *				 returns pointer to vsa struct. Minimum size is 24 bytes.
 * Arguments : memory_p -  a pointer to allocated memory by user.
 *			   memory_size - the total amount of allocated memory in bytes.
 * Return : pointer to pool.
 * Time Complexity - O(1).
 * Space Complexity - O(1). 
 */
vsa_t *VSAInit(void *memory_p, size_t memory_size)
{
	vsa_t *end = NULL, *new_pool = (vsa_t *)ALIGNED_BLOCK((size_t)memory_p);
	memory_size = ALIGNEDOWN(memory_size);
	
	new_pool->block_size = ((long)memory_size - (VSASIZE * 2));
	end = (vsa_t *)((char *)new_pool + new_pool->block_size);
	end->block_size = DEADBEEF;
	return new_pool;	
}



/* helper function */
static vsa_t *Defrag(vsa_t *curr_block)
{
	vsa_t *temp = curr_block;
	
	while (DEADBEEF != temp->block_size && temp->block_size > 0)
	{
		temp = (vsa_t *)((char *)temp + temp->block_size);
		if (temp->block_size > 0 && temp->block_size != DEADBEEF)
		{
			curr_block->block_size += temp->block_size;
		}
	}
	return curr_block;
}




/*--------------------------------------------------------*/
/* Status : approved.
 * Reviewer : shlomi.
 * Description : Allocates a block to user the size of block_size.
 * Arguments : vsa_pool - pointer to the pool
 * 			   block_size - size of block to allocate, in bytes.
 * Return : void pointer to block start.
 * 			If no space available - undefined behavior.
 * Time Complexity - O(n).
 * Space Complexity - O(1).
 */
void *VSAAlloc(vsa_t *vsa_pool, size_t block_size)
{
	vsa_t *next = NULL;
	long int available = vsa_pool->block_size;
    
	if (block_size > VSALargestBlockAvailable(vsa_pool))
	{
		return NULL;
	}
    /* align block size + manegment unit */
    
    block_size = ALIGNED_BLOCK(block_size) + VSASIZE;
    
	/* will go through the pool until first match is foun - using defrag while running */
	
    while (available < (long)block_size && vsa_pool->block_size != DEADBEEF)
    {
		vsa_pool = (vsa_t *)((char *)vsa_pool + labs(vsa_pool->block_size));  
		/* labs presents the absolute number, that way we can move to the next block even if curr block is occupide and represented as minus */
		
		/* defrag next block (will return unchanged if occupied or next is occupied */
        vsa_pool = Defrag(vsa_pool);
        available = vsa_pool->block_size;
    }
    
    if (available > (long int)block_size)

    {
    	next = (vsa_t *)((char *)vsa_pool + block_size);
    	next->block_size = (available - block_size);
		SETDEBUG(available);
    }
    
    vsa_pool->block_size = ((long)block_size * CHANGE_STATUS);

	/* move the block 8 bytes foward so the user won't overrides our mangmant info */
    return (vsa_pool + 1);
}



/*--------------------------------------------------------*/
/* Status : aprroved.
 * Reviewer : shlomi.
 * Description : Frees one block from user.
 * Arguments : block - void pointer to a block.
 * Return : void.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 */
void VSAFree(void *block)
{
	vsa_t *block_to_free = (vsa_t *)block;

	block_to_free -= 1;      /* -1 will move it 8 bytse backwords to block's managment struct.*/
	FREEDEBUG(free);	
	block_to_free->block_size *= -1	;
	return;
}
		

/*--------------------------------------------------------*/
/* Status : approved
 * Reviewer : shlomi.
 * Description : provides information about free blocks.
 * Arguments : vas_pool - pool pointer.
 * Return : number of bytes in largest available block.
 * Time Complexity - O(n).
 * Space Complexity - O(1).
 */
size_t VSALargestBlockAvailable(const vsa_t *vsa_pool)
{
	long largest = 0;
	vsa_t *block = (vsa_t *)vsa_pool;

	while (DEADBEEF != block->block_size)
	{
	    block = Defrag(block);
		if (block->block_size > largest)
		{
			largest = block->block_size;
		}
		block = (vsa_t *)((char *)block + labs(block->block_size));
	}
	return (size_t)largest;	
}
