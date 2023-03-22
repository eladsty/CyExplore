
#include "vsa.h"

#define WORDSIZE sizeof(size_t)         
#define ALIGNTOWORD(num)((0 == num % WORDSIZE) ? num : ((num >> 3) << 3) + WORDSIZE)
#define MEMSIZEALIGN(mem_size)(0 == mem_size % WORDSIZE ? mem_size : mem_size - (mem_size % WORDSIZE))
#define ENDOFMEM -97654321
#define ABS(n)(n < 0 ? n * -1: n)
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
	aligned_mem -= (sizeof(vsa_t));
	/*the block is now free to use*/
	new_vsa->block_info = -1 * aligned_mem;
	
	/*the offset is now pointing to ENDOFMEM*/
	*((long *)((char *)new_vsa + new_vsa->block_info * -1)) = ENDOFMEM;
	return new_vsa;
}
/*
	send it empty block and get total size of defraged spaced
	if BlockInfor returns negative, that means	 the block is free*/
static size_t Defrag(vsa_t *block)
{
	size_t total_size = 0;
	vsa_t *iter = NULL;
	iter = (vsa_t *)block;
	while(iter->block_info < 0 && iter->block_info != ENDOFMEM)
	{
		total_size += (iter->block_info * -1);
 		iter = (vsa_t *)((char *)block + total_size);
	}
	return total_size;
}

void *VSAAlloc(vsa_t *vsa_pool, size_t block_size)
{
	vsa_t *iter = NULL;
	long available_size = 0; 			/*added wordsize for block_info section*/
	long aligned_block_size = ALIGNTOWORD(block_size) + WORDSIZE;
	iter = vsa_pool;

	while(iter->block_info != ENDOFMEM)
	{
		available_size = Defrag(iter);
		if(BlockInfo(iter) < 0 && available_size >= aligned_block_size)
		{	/* ad extra WORDSIZE is added to the return to avoid overwriting blockinfo section*/
			iter->block_info = aligned_block_size;
			if(available_size > aligned_block_size)
			{
				*(long *)((char *)iter + aligned_block_size) = (available_size - aligned_block_size) * -1;
			}
 			return (void *)((char *)iter + WORDSIZE);
		}
		iter = (vsa_t *)(char *)iter + iter->block_info;
	}
	return NULL;
}

 

void VSAFree(void *block)
{
	*(long *)((char *)block - WORDSIZE) *= -1;
}

size_t VSALargestBlockAvailable(const vsa_t *vsa_pool)
{
 	vsa_t *iter = (vsa_t *)vsa_pool;
	size_t largest_size = 0;
	while(iter->block_info != ENDOFMEM)
	{
		if(0 > iter->block_info && Defrag(iter) > largest_size)
		{
			largest_size =  Defrag(iter);
		}
		iter = (vsa_t *)((char *)iter + ABS(iter->block_info));
 	}
	return largest_size;
}
