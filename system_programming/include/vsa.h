#ifndef __VSA_H_CR4__ 
#define __VSA_H_CR4__ 


#include <stddef.h> /* Used for size_t type */

typedef struct vsa vsa_t;
 

/* block_size represent the size (in bytes) of the current block,
 * the most segnificant bit represent if the block is free,
 * 1 means free, 0 means allocated */
 
 

/*--------------------------------------------------------*/
/* Status : 
 * Reviewer : 
 * Description : Recieves memory pool, initiate vsa struct,
 *				 returns pointer to vsa struct. Minimum size is 24 bytes.
 * Arguments : memory_p -  a pointer to allocated memory by user.
 *			   memory_size - the total amount of allocated memory in bytes.
 * Return : pointer to pool.
 * Time Complexity - O(1).
 * Space Complexity - O(1). 
 */
vsa_t *VSAInit(void *memory_p, size_t memory_size);


/*--------------------------------------------------------*/
/* Status : 
 * Reviewer : 
 * Description : Allocates a block to user the size of block_size.
 * Arguments : vsa_pool - pointer to the pool
 * 			   block_size - size of block to allocate, in bytes.
 * Return : void pointer to block start.
 * 			If no space available - undefined behavior.
 * Time Complexity - O(n).
 * Space Complexity - O(1).
 */
void *VSAAlloc(vsa_t *vsa_pool, size_t block_size);


/*--------------------------------------------------------*/
/* Status : 
 * Reviewer : 
 * Description : Frees one block from user.
 * Arguments : block - void pointer to a block.
 * Return : void.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 */
void VSAFree(void *block);


/*--------------------------------------------------------*/
/* Status : 
 * Reviewer : 
 * Description : provides information about free blocks.
 * Arguments : vas_pool - pool pointer.
 * Return : number of bytes in largest available block.
 * Time Complexity - O(n).
 * Space Complexity - O(1).
 */
size_t VSALargestBlockAvailable(const vsa_t *vsa_pool);


/*returns block_info section that is negative if block is occupied, contain the size of available space*/
long BlockInfo(vsa_t *block);
#endif /* __VSA_H_CR4__ */
