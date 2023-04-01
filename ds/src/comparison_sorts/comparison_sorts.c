#include <stddef.h>

#include "comparison_sorts.h"
/*
	status: APPROVED
	description: sorts the given array.
	Reviewer: Hen 
	Return: 0

*/
static void SwapWTemp(int *n1, int *n2)
{
	int temp = *n1;
 	*n1 = *n2;
 	*n2 = temp;
}


static void SwapWBitwise(int *n1, int *n2)
{
	if(*n1 != *n2)
	{
		*n1 ^= *n2;
		*n2 ^= *n1;
		*n1 ^= *n2; 
	}
}
static void SwapWArit(int *n1, int *n2)
{
	*n1 += *n2;
	*n2 = *n1 - *n2;
	*n1 = *n1 - *n2;
}

int BubbleSort(int *array, size_t len)
{
	size_t i = 0, j = 0;
	for(i=0; i<len-1; ++i)
	{
		for(j=0; j<len-1-i; ++j)
		{
			if(array[j] > array[j+1])
			{
			 	SwapWTemp(&array[j],&array[j+1]);
			}
		}
	}
	return 0;
}

/*
	status: READY
	description: sorts the given array.
	Reviewer:  Hen
	Return: 0  

*/
int SelectionSort(int *array, size_t len)
{
	size_t i_curr_small = 0, i = 0, j = 0;
	
	for(i = 0; i < len-1; ++i)
	{
		i_curr_small = i;
		
		for(j = i+1; j < len; ++j)
		{
			if(array[j] < array[i_curr_small])
			{
				i_curr_small = j;
			}
		}
		if(array[i_curr_small] != array[i])
		{
			SwapWTemp(&array[i_curr_small],&array[i]);
		}
 
	}
	return 0;
} 
 
 
 /*
	status: 
	description: sorts the given array.
	Reviewer:  
	Return:  

*/
int InsertionSort(int *array, size_t len)
{
 	size_t i = 0, j = 0;	
    for(i = 1; i < len; ++i) 
    {
    	j = i;
    	while(j > 0 && array[j-1] > array[j])
    	{
			SwapWTemp(&array[j],&array[j-1]);
			--j;
    	}
    }
	return 0;
}


/* Status :
 * Reviewer :
 * Description : conducts binary search of a sorted array recursivly.
 * Arguments : array of int, its size and a value to find.
 * Return : index of found value, -1 if did not find.
 */


int IterativeSearch(int n, int arr[], int len)
{
	int i = 0, result_i = -1;
	len = (len % 2 == 0 ? len : len + 1);
	len /= 2;
	i = len;
	
	while (len)
	{
		if (arr[i] == n || arr[i - 1] == n)
		{
			if(arr[i] == n)
			{
				return i
			}
			return (i + 1);
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
	return -1;
}

 

/* Status :
 * Reviewer :
 * Description : conducts binary search of a sorted array recursivly.
 * Arguments : array of int, its size and a value to find.
 * Return : index of found value, -1 if did not find.
 */

int RecursiveSearch(int n, int arr[], int len)
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
	return ;
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


void Swap(int *a, int *b) 
{
	if(*a == *b)
	{
		return;
	}
	*a ^= *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

/*function to find the partition position*/  
int Partition(int array[], int low, int high) 
{
  /*select the rightmost element as pivot*/  
  int pivot = array[high];
  
  /* pointer for greater element*/ 
  int i = (low - 1);

  /*traverse each element of the array*/  
  /*compare them with the pivot*/  
  for (int j = low; j < high; j++) 
  {
    if (array[j] <= pivot)
     {
        
      /**/ if element smaller than pivot is found
      /**/ swap it with the greater element pointed by i
      i++;
      
      /**/ swap element at i with element at j
      swap(&array[i], &array[j]);
    }
  }

  /*swap the pivot element with the greater element at i*/  
  swap(&array[i + 1], &array[high]);
  
  /*return the partition point*/  
  return (i + 1);
}

void QuickSort(int array[], int low, int high) {
  if (low < high) 
  {
  /* 
     find the pivot element such that
     elements smaller than pivot are on left of pivot
    elements greater than pivot are on right of pivot*/
    int pi = partition(array, low, high);    
     /*recursive call on the left of pivot*/
    QuickSort(array, low, pi - 1);    
    /*recursive call on the right of pivot*/
    QuickSort(array, pi + 1, high);
  }
}
 
