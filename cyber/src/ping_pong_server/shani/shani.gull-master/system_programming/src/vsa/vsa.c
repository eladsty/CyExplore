#include <stdlib.h> /* abs function */
#include "../../include/vsa/vsa.h"


#define VSA_SIZE (sizeof(vsa_t))
#define WORD (sizeof(size_t))
#define CHANGE_STATUS (-1)
#define ALIGN(x)  (x < WORD ? WORD - x : x % WORD) /* if x is less then 8bytes, returns positiove how much to add. if not returns negative how much to take. */
#define POINTER_ALIGN(x)  ((x) % WORD)
#define STOP (123456789) /* indicates the end of vsa memory segment */
#define POINTER_ADD_BYTE(x, y) ((x) + ((y) / WORD))

#ifndef NDEBUG
#include <stdio.h> /* printf */
#define IDENTIFIER (0xB110C)
#define DEBUG_SET_IDENTIFIER(pointer) { \
            (pointer)->identifier = IDENTIFIER; \
        }
#define IS_IDENTIFIED(pointer) (((*(long *)pointer) == IDENTIFIER) ? (0) : (1))
#define IS_ALLOCATED(pointer) ((0 < (*(long *)pointer)) ? (0) : (1))
#define DEBUG_IS_VALID(pointer) { \
                            if (!IS_IDENTIFIED(pointer)) \
                            { \
                                printf("program: %s:%d: main: pointer was given that was not previously allocated.\n", __FILE__, __LINE__); \
                                exit(1); \
                            } \
                            if (!IS_ALLOCATED(pointer)) \
                            { \
                                printf("program: %s:%d: main: pointer was given that was previously freed.\n", __FILE__, __LINE__); \
                                exit(1); \
                            } \
                        }
#else
#define SET_IDENTIFIER(ignore) { \
            ; \
        }
#define IS_VALID(ignore) { \
            ; \
        }
#endif /* NDEBUG */

struct vsa
{
    long block_size; 
    #ifndef NDEBUG
    size_t identifier;
    #endif /* NDEBUG */
};


static void Defrag(const vsa_t *vsa)
{
    vsa_t *tmp = (vsa_t *)vsa;
    while (0 > tmp->block_size && 
            0 > (long)(POINTER_ADD_BYTE(tmp, labs(tmp->block_size)))->block_size) /* two conseq blocks are free */
    {
        tmp->block_size = tmp->block_size + 
                            (long)(POINTER_ADD_BYTE(tmp, labs(tmp->block_size)))->block_size;
    tmp = POINTER_ADD_BYTE(tmp, labs(tmp->block_size));
    }
    return;
}

/* Status : Approved
 * Reviewer : Nadav
 * Description : recieves a pointer to a allocated memory block 
 *              and it's size from user, and builds a free list. 
 * 				when providing size, please add 24 bytes for vsa managing.
	
 * Arguments : void pointer memory_p to memory allocated by user, 
                and size the size of memory allocated.
 * Return : vsa_t pointer to vsa. 
 * Time Complexity - O(1).
 * Space Complexity - O(1). 
 */
vsa_t *VSAInit(void *memory_p, size_t size)
{
    vsa_t *vsa = (vsa_t *)memory_p + ALIGN((size_t)memory_p);
    if ((size_t)ALIGN((size_t)vsa))
    {
        vsa = POINTER_ADD_BYTE(vsa, (size_t)ALIGN((size_t)vsa));
        size -= ALIGN((size_t)vsa);        
    }
    POINTER_ADD_BYTE(vsa, (size - WORD))->block_size = STOP;
    vsa->block_size = (signed long)((size - WORD) * CHANGE_STATUS); /* mind you - dataWORD is included in block size. not including end of vsa*/
    return vsa;
}


/* Status : Approved
 * Reviewer : Nadav
 * Description : recieves free list pointer and requested block size, 
 *              returns a void pointer to the allocated block. removes block from free list.
	
 * Arguments : free list pointer and requested block size.
	
 * Return : void pointer to allocated block. if no block available undifined behavior.
 * Time Complexity - O(n).
 * Space Complexity - O(1). 
 */
void *VSAAlloc(vsa_t *vsa, size_t block_size) /* i will concider block bytes to include manage WORD */
{
    void *block = NULL;
    block_size += WORD; 
    block_size += (ALIGN(block_size)) ? ALIGN(block_size) : 0;
    while (STOP != vsa->block_size)
    {
        Defrag((const vsa_t *) vsa);
        if (0 > vsa->block_size && (size_t)labs(vsa->block_size) >= block_size)
        {            
            if (block_size < (size_t)labs(vsa->block_size))
            {
                POINTER_ADD_BYTE(vsa, block_size)->block_size = vsa->block_size + block_size;
            }
            vsa->block_size = block_size;
            DEBUG_SET_IDENTIFIER(vsa);
            block = (void *)(vsa + 1);
            return block;
        }
        vsa = POINTER_ADD_BYTE(vsa, vsa->block_size);
    }
    return block;
}


/* Status : Approved
 * Reviewer : Nadav
 * Description : recieves a pointer to allocated block, adds it to free list.
	
 * Arguments : pointer to allocated block
	
 * Return : void
 * Time Complexity - O(1).
 * Space Complexity - O(1). 
 */
void VSAFree(void *block)
{
    vsa_t *manage = (vsa_t *)block - 1;
    DEBUG_IS_VALID(manage);
    manage->block_size = manage->block_size * CHANGE_STATUS;
    return;
}





/* Status : Approved
 * Reviewer : Nadav
 * Description : recieves "vsa" - pointer to vsa, finds the biggest continuous block in it.
 * Arguments : vsa pointer "vsa".
	
 * Return : size of biggest continuous block.
 * Time Complexity - O(n).
 * Space Complexity - O(1). 
 */

size_t VSALargestBlockAvailable(const vsa_t *vsa)
{
    vsa_t *vsa_tmp = (vsa_t *)vsa;
    long block_size = 0, largest = 0;
    while (STOP != block_size)
    {
        Defrag((const vsa_t *)vsa);
        vsa_tmp = POINTER_ADD_BYTE(vsa_tmp, labs(block_size));
        block_size = vsa_tmp->block_size;
        largest = (block_size < largest) ? block_size : largest;
        
    }
    largest = largest + ALIGN((size_t)labs(largest));
    if (-16 < largest)
    {
        return 0;
    }
    return (CHANGE_STATUS * largest) - VSA_SIZE;
}

