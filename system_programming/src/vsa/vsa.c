
#include "vsa.h"

#define WORDSIZE sizeof(size_t)         
#define ALIGNTOWORD(num)((0 == num % WORDSIZE) ? num : ((num >> 3) << 3) + WORDSIZE)
#define MEMSIZEALIGN(mem_size)(0 == mem_size % WORDSIZE ? mem_size : mem_size - (mem_size % WORDSIZE))
#define ENDOFMEM -97654321
#define ABS(x) (((x) < 0) ? -(x) :(x))
 /*
 ONOFFMSB  turn on/off the leftmost bit (which represent if a block is occupied).
 Due to leftmost bit being used for this purpose, the largest number of bytes we can use is 2^31
 */

 /* 0xDECAF  represent end of memory*/
 
struct vsa
{
	long block_info;
};



/*
struct vsa 
{
	size_t mem_size;
	unsigned is_free: 1;
};
*/

/*
 this function received vsa_t * and retunrs info_block (type long)
if BlockInfor returns negative, that means the block is free

*/
long BlockInfo(vsa_t *block)
{
	return block->block_info; 
}

vsa_t *VSAInit(void *memory_p, size_t memory_size)
{
	vsa_t *new_vsa = (vsa_t *)((char *)ALIGNTOWORD((size_t)memory_p));
	size_t aligned_mem = MEMSIZEALIGN(memory_size);
	vsa_t *end_of_memory = NULL;
	aligned_mem -= (sizeof(vsa_t));
	/*the block is now free to use*/
	new_vsa->block_info = -1 * aligned_mem;
	/*the offset is now pointing to ENDOFMEM*/
	end_of_memory = ((vsa_t *)((char *)new_vsa + new_vsa->block_info));
	end_of_memory->block_info = ENDOFMEM;
	return new_vsa;
}
/*
returns pointer to vsa_t, after concatenating multiple adjacent empty blocks (if available)
*/
static vsa_t *Defrag(vsa_t *block)
{
	vsa_t *iter = (vsa_t *)block;
	  
	while(iter->block_info < 0 && iter->block_info != ENDOFMEM)
	{
 		iter = (vsa_t *)((char *)block + ABS(iter->block_info));
		if(iter->block_info < 0 && iter->block_info != ENDOFMEM)
		{
			block->block_info -= iter->block_info;
		}
	}
	return block;
}

void *VSAAlloc(vsa_t *vsa_pool, size_t block_size)
{
	vsa_t *iter = NULL;
	long available_size = vsa_pool->block_info; 
	 /*added wordsize for block_info section*/
	long aligned_block_size = ALIGNTOWORD(block_size) + WORDSIZE;

	 /*iterate, until First Match or end of memory*/
	while(available_size < aligned_block_size && iter->block_info != ENDOFMEM)
	{
		vsa_pool = (vsa_t *)((char *)vsa_pool + ABS(iter->block_info));  
		vsa_pool = Defrag(vsa_pool);  
		available_size = vsa_pool->block_info;
	}

	if(available_size > (long)block_size)
	{
		iter = (vsa_t *)((char *)vsa_pool + block_size);
		iter->block_info = (available_size - block_size);
	}
	
	vsa_pool->block_info = ((long)block_size * -1);

    return (vsa_pool + 1);
}

 

void VSAFree(void *block)
{
	*(long *)((char *)block - WORDSIZE) *= -1;
}

size_t VSALargestBlockAvailable(const vsa_t *vsa_pool)
{
 	vsa_t *iter = (vsa_t *)vsa_pool;
	long largest_size = 0;
 	while(iter->block_info != ENDOFMEM)
	{
		iter = Defrag((vsa_t *)vsa_pool);
		if(largest_size < ABS(iter->block_info))
		{
			largest_size = ABS(iter->block_info);
		}
		iter = (vsa_t *)((char *)iter + ABS(iter->block_info));
 	}
	return largest_size;
}
