#include <stdio.h> /* for printf*/
#include <stdlib.h> /*malloc*/

#include "vsa.h"

int main()
{
	void *vsa_start_pool = malloc(1097);
	vsa_t *new_vsa = NULL;
	int int_arr[] = {123123,234234,345345,456456,567567};
	long block_info_print;
	if(NULL == vsa_start_pool)
	{
		return -1;
	}
 	new_vsa = VSAInit(vsa_start_pool, 5097);
 	printf("the size of the pool after alignment is: %d\n", BlockInfo(new_vsa)); 
 	printf("endofmem is: %d\n", *((long *)((size_t)new_vsa + BlockInfo(new_vsa) * -1))); 

	free(vsa_start_pool);
	vsa_start_pool = NULL;
	return 0;
}