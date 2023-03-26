#include <stddef.h> /*size_t*/
#include <stdlib.h>/* mallocls*/

#include "sorting.h"

int IterativeSearch(int n, int arr[], int len)
{
	int i = 0;
	len = (len % 2 == 0 ? len : len + 1);
	len /= 2;
	i = len;

	while (len)
	{
		if (arr[i] == n || arr[i - 1] == n)
		{
			return 1;
		}
		else if (n > arr[i])
		{
			i += (len / 2);
		}
		else if (n < arr[i])
		{
			i -= (len / 2);
		}
		len /= 2;
	}
	return 0;
}

 

RecursiveSearch(int n, int arr[], int len)
{
	int i = len/2;
	if (n == arr[i])
	{
		return 1;
	}
	else if (len < 2)
	{
		return (arr[i] == n || n == arr[i + 1] ? 1 : 0);
	}

	else if (arr[i] < n)
	{
		RecursiveSearch(n, (arr + i + 1), len /= 2);
	}

	else if (arr[i] > n)
	{
		RecursiveSearch(n, arr, len /= 2);
	}
}

 




/* ex 3 - MergeSort
description:  recieves pointer to start of array of integers and sorts the array .  
status: impltst   
reviewer:   
args: pointer to start of array of integers + num of elements
return: 0 at finish 
notes:   
*/

void MergerTwo(int *array , int left , int right, int middle )
{
	int i = 0;
	int j = 0;
	
	int k = left;
	int num_elements_left_arr = middle - left + 1;   /*num elements = index + 1*/ 
	int num_elements_right_arr = right - middle; 
	
	int *left_arr_mem = NULL;
	int *right_arr_mem = NULL; 
	
	/* memory for both arrays */
	
	left_arr_mem = (int *)malloc(num_elements_left_arr*sizeof(int));
	if (left_arr_mem == NULL)
	{
		printf("memory allocation failed, exiting \n");
		exit(0);
	}
	
	right_arr_mem = (int *)malloc(num_elements_right_arr*sizeof(int));
	if (right_arr_mem == NULL)
	{
		printf("memory allocation failed, exiting \n");
		exit(0);
	}

	/*copy left of array to left memory , right of array to right memory */
	
	for ( i = 0; i < num_elements_left_arr ; ++i )
	{
		left_arr_mem[i] = array[left+i];
	}
	
	for ( i = 0 ; i < num_elements_right_arr ; ++i )
	{
		right_arr_mem[i] = array[middle+1+i];
	}
	
	/*merge left and right memory into original array */
	
	i = 0;
	
	while ( i < num_elements_left_arr && j < num_elements_right_arr )
	{
		if (left_arr_mem[i] <= right_arr_mem[j])
		{
			array[k] = left_arr_mem[i];
			++i;
		}
		
		else
		{
			array[k] = right_arr_mem[j];
			++j;
		}
		
		++k;
	}
	

	
	/*insert remaining elements from right memory and left memory into array */
	
	while (i < num_elements_left_arr)
	{
		array[k] = left_arr_mem[i];
		++i;
		++k;
	}

	while (j < num_elements_right_arr)
	{
		array[k] = right_arr_mem[j];
		++j;
		++k;
	}
	
	/*free temp memory*/

	free(left_arr_mem);
	free(right_arr_mem);
	
}


void MergerOne( int *array , int left, int right )
{
	int middle;
	
	if (left < right)
	{
		middle = left + (right-left)/2;
		
		MergerOne(array,left,middle);

		MergerOne(array,middle+1,right);

		MergerTwo(array , left , right , middle);
	
	}
}



int MergeSort(int *arr_to_sort, size_t num_elements)
{
	int left = 0;
	int right = num_elements-1;
	

	MergerOne(arr_to_sort, left, right);
	
	return 0;
}
