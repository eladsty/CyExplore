#include <stdlib.h>
#include <stdio.h>
#include "../../include/vsa/vsa.h"

int main(void)
{
	size_t size = sizeof(size_t) * 11;
	void *memory = malloc(size);
	void *block1 = NULL, *block2 = NULL, *block3 = NULL, *block4 = NULL, *debug_block = NULL;
	vsa_t *my_vsa = VSAInit(memory, (size));
	size_t max_block = VSALargestBlockAvailable(my_vsa);
	printf("%ld\n", max_block);
	block1 = VSAAlloc(my_vsa, 16);
	if (NULL == block1)
	{
		return 1;
	}
	max_block = VSALargestBlockAvailable(my_vsa);
	printf("%ld\n", max_block);
	block2 = VSAAlloc(my_vsa, 8);
	if (NULL == block2)
	{
		return 1;
	}
	max_block = VSALargestBlockAvailable(my_vsa);
	printf("%ld\n", max_block);
	block3 = VSAAlloc(my_vsa, 8);
	if (NULL == block3)
	{
		return 1;
	}
	max_block = VSALargestBlockAvailable(my_vsa);
	printf("%ld\n", max_block);
	block4 = VSAAlloc(my_vsa, 8);
	if (NULL == block4)
	{
		return 1;
	}
	max_block = VSALargestBlockAvailable(my_vsa);
	printf("%ld\n", max_block);
	
	VSAFree(block2);
	max_block = VSALargestBlockAvailable(my_vsa);
	VSAFree(block3);
	max_block = VSALargestBlockAvailable(my_vsa);
	printf("%ld\n", max_block);
	VSAFree(debug_block);
	free(memory);
	return (0);
}

