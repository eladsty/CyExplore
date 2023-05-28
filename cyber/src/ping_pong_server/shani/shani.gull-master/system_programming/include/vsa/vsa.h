#ifndef __VSA_H_CR4__ 
#define __VSA_H_CR4__ 

#include <stddef.h> /* Used for size_t type */

typedef struct vsa vsa_t;

/* Status : Approved
 * Reviewer : Nadav
 * Description : recieves a pointer to a allocated memory block 
 *              and it's size from user, and builds a free list. 
 * 				when providing size, please add 24 bytes for vsa managing.
	
 * Arguments : void pointer to memory, size of memory allocated.
	
 * Return : pointer to free list. 
 * Time Complexity - O(1).
 * Space Complexity - O(1). 
 */
vsa_t *VSAInit(void *memory_p, size_t size);


/* Status : Approved
 * Reviewer : Nadav
 * Description : recieves free list pointer and requested block size, 
 *              returns a void pointer to the allocated block. removes block from free list.
	
 * Arguments : free list pointer and requested block size.
	
 * Return : void pointer to allocated block. if no block available undifined behavior.
 * Time Complexity - O(n).
 * Space Complexity - O(1). 
 */
void *VSAAlloc(vsa_t *pool, size_t block_size);


/* Status : Approved
 * Reviewer : Nadav
 * Description : recieves a pointer to allocated block, adds it to free list.
	
 * Arguments : pointer to allocated block
	
 * Return : void
 * Time Complexity - O(1).
 * Space Complexity - O(1). 
 */
void VSAFree(void *block);


/* Status : Approved
 * Reviewer : Nadav
 * Description : recieves free list pointer, finds the biggest continuos block in free list.
	
 * Arguments : free list pointer.
	
 * Return : size of biggest block.
 * Time Complexity - O(n).
 * Space Complexity - O(1). 
 */

size_t VSALargestBlockAvailable(const vsa_t *pool);



#endif /* __VSA_H_CR4__ */
