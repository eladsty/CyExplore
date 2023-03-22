#include <stdio.h> /* for printf*/
#include <stdlib.h> /*malloc*/
#include <string.h> /* for memcpy*/
#include "vsa.h"

int main()
{
	void *vsa_start_pool = malloc(1097);
	vsa_t *new_vsa = NULL;
	vsa_t *vsa_cpy_for_info = NULL;
	int int_arr[] = {123123,234234,345345,456456,567567};
	char *string_of_90 = "klmnopqrstuvwxyabcdefghijklmnopqrstuvwxyabcdefghijklmnopqrstuvwxyabcdefghijklmnopqrstuvwxy";
	char *string_of_100 = "abcdefghijklmnopqrstuvwxyabcdefghijklmnopqrstuvwxyabcdefghijklmnopqrstuvwxyabcdefghijklmnopqrstuvwxy";
	char string_buffer[100]; 
	char *str_for_alloc;
	long block_info_print;
	if(NULL == vsa_start_pool)
	{
		return -1;
	}
	
 	new_vsa = VSAInit(vsa_start_pool, 5097);
 	printf("the size of the pool after alignment is: %d\n", BlockInfo(new_vsa)); 
 	printf("endofmem is: %d\n", *((long *)((size_t)new_vsa + BlockInfo(new_vsa) * -1))); 
	
	str_for_alloc = (char *)VSAAlloc(new_vsa, 100);
	/*
	vsa_cpy_for_info = (vsa_t *)((char *)str_for_alloc - 8);
	printf("should return 100: %d\n", BlockInfo(vsa_cpy_for_info); 
	*/

	strcpy(str_for_alloc, string_of_90);

	printf("str_for_alloc: %s\n", str_for_alloc);
	VSAFree(str_for_alloc);
 	printf("str_for_alloc: %s\n", str_for_alloc);
 	printf("the size of the pool after alignment is: %d\n", BlockInfo(new_vsa)); 
 	printf("largest block is : %d\n", VSALargestBlockAvailable(new_vsa)); 
 
	free(vsa_start_pool);
	vsa_start_pool = NULL;
	return 0;
}

 