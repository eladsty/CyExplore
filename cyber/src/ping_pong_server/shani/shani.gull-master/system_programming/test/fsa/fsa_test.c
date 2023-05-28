#include <stddef.h> /* Used for size_t type */
#include <stdlib.h> /* malloc free */
#include <stdio.h> /* printf */
#include "../../include/fsa/fsa.h"


int main(void)
{
	int i = 1;
	size_t block_count = 5;
	size_t block_size = 17;
	size_t fsa_size = FSASuggestSize(block_size, block_count);
	void *memory = malloc(fsa_size);
	void *block1 = NULL, *block2 = NULL, *block3 = NULL, *block4 = NULL, *block5 = NULL, *block6 = NULL;
	char *memory_misalligned = (char *)memory + 1;
	fsa_t *fsa = NULL;
	
	if (NULL == memory)
	{
		return 1;
	}
	/***********pool 1************/
	printf("test 1 - alligned pointer\n");
	fsa = FSAInit(memory, fsa_size, block_size);
	printf("there are %ld free blocks of memory available\n", FSACountFree(fsa));

	
	/***********alloc************/
	block1 = FSAAlloc(fsa);
	block2 = FSAAlloc(fsa);
	block3 = FSAAlloc(fsa);
	block4 = FSAAlloc(fsa);
	block5 = FSAAlloc(fsa);
	block6 = FSAAlloc(fsa); /* this should return NULL */
	if (NULL == block6 && NULL != block5)
	{
		printf("worked\n");
	}
	printf("there are %ld free blocks of memory available\n", FSACountFree(fsa));
	/***********free************/
	FSAFree(block1, fsa);
	FSAFree(block2, fsa);
	FSAFree(block3, fsa);
	FSAFree(block4, fsa);
	FSAFree(block5, fsa);
	
	printf("there are %ld free blocks of memory available\n", FSACountFree(fsa)); 
	
	/***********pool 2 - misalligned************/
	printf("++++++++++++++++++++++++++++++\n");
	printf("test 2 - misalligned pointer\n");
	fsa = FSAInit(memory_misalligned, fsa_size, block_size);
	printf("there are %ld free blocks of memory available\n", FSACountFree(fsa));
	
	/***********alloc************/
	block1 = FSAAlloc(fsa);
	block2 = FSAAlloc(fsa);
	block3 = FSAAlloc(fsa);
	block4 = FSAAlloc(fsa);
	block5 = FSAAlloc(fsa);
	block6 = FSAAlloc(fsa); /* this should return NULL */
	if (NULL == block6 && NULL != block5)
	{
		printf("worked\n");
	}
	printf("there are %ld free blocks of memory available\n", FSACountFree(fsa));
	/***********free************/
	FSAFree(block1, fsa);
	FSAFree(block2, fsa);
	FSAFree(block3, fsa);
	FSAFree(block4, fsa);
	FSAFree(block5, fsa);
	
	printf("there are %ld free blocks of memory available\n", FSACountFree(fsa));
	
	free(memory);
	memory = NULL;	
	return (0);
}

