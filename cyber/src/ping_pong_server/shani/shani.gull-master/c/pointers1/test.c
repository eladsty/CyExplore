#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pointer1.h"

int main()
{
	int stam[] = {0, 17, 3}; 
	int *arr, a = 3, b = 4;
	size_t i, j, *ptr, *ptr2, **ptr_to_ptr, **ptr_to_ptr2;
	SwapValues(&a, &b); /*test for ex1*/
	arr[] = CopyArr(stam, 3); /*test for ex2*/
	i = 12;/* test for ex4*/
	j = 15;
	ptr = &i;
	ptr2 =&j;
	ptr_to_ptr = &ptr;
	ptr_to_ptr2 = &ptr2;
	SwapSizeT((size_t*)ptr_to_ptr, (size_t*)ptr_to_ptr2);
	return 0;
}

