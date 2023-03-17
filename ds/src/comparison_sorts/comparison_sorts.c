#include <stddef.h>

#include "comparison_sorts.h"

static void swap(int *n1, int *n2)
{
	int temp = *n1;
	*n1 = *n2;
	*n2 = temp;
}
/*
	status: 
	description: sorts the given array.
	Reviewer:  
	Return:  

*/
int BubbleSort(int *array, size_t len)
{
	size_t i = 0, j = 0;
	for(i=0; i<len-1; ++i)
	{
		for(j=0; j<len-1-i; ++j)
		{
			if(array[j+1] < array[j])
			{
			 swap(&array[j], &array[j+1]);
			}
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
			swap(&array[i_curr_small],&array[i]);
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
			swap(&array[j],&array[j-1]);
			--j;
    	}
    }
	return 0;
}
 
