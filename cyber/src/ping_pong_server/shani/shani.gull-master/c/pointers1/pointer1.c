#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "pointer1.h"

/* ex1 */
void SwapValues(int *var1, int *var2)
{
	int temp = *var1;
	assert (var1 != NULL && var2 != NULL);
	*var1 = *var2;
	*var2 = temp;
}
/* ex2 */
int* CopyArr(int *arr, int length)
{
	int i = 0;
	int *new_arr = (int *)malloc(sizeof(int));
	while (i++ < length)
	{
		*new_arr++ = *arr++;
	}
	return (new_arr - length);
}
/* ex4 */
void SwapSizeT(size_t *var1, size_t *var2)
{
	size_t temp = *var1;
	assert (var1 != NULL && var2 != NULL);
	*var1 = *var2;
	*var2 = temp;
}

