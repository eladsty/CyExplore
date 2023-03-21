
#include "vsa.h"

#define WORDSIZE sizeof(size_t)         
#define ALIGNTOWORD(num)((0 == num % WORDSIZE) ? num : ((num >> 3) << 3) + WORDSIZE)
#define MEMSIZEALIGN(mem_size)(0 == mem_size % WORDSIZE ? mem_size : mem_size - (mem_size % WORDSIZE))
#define ENDOFMEM -97654321
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
block_info contains msb 
*/
long BlockInfo(vsa_t *block)
{
	return block->block_info; 
}

vsa_t *VSAInit(void *memory_p, size_t memory_size)
{
	vsa_t *new_vsa = (vsa_t *)((char *)ALIGNTOWORD((size_t)memory_p));
	size_t aligned_mem = MEMSIZEALIGN(memory_size);
	if(NULL == memory_p && aligned_mem >= 24)
	{	
		printf("invalid memory address or insufficient memory size.");
		return;
	}

	aligned_mem -= (sizeof(vsa_t) + sizeof(vsa_t));
	/*the block is now free to use*/
	new_vsa->block_info = -1 * aligned_mem;
	
	/*the offset is now pointing to ENDOFMEM*/
	*((long *)((size_t)new_vsa + new_vsa->block_info * -1)) = -1 * ENDOFMEM;
	return new_vsa;
}

void *VSAAlloc(vsa_t *vsa_pool, size_t block_size)
{


}
