#include <stddef.h> /*size_t*/

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

 
 
/*((((((((((((((((((((((((((((((((((((((((recursive merge sort))))))))))))))))))))))))))))))))))))))))*/	 

void Merger(int arr[], int start_i, int mid_i, int end_i)
{	
	unsigned i, j, k;
	unsigned left_end = 0, right_end = 0;
	/* create temp array*/
 	int left_arr[left_end], right_arr[right_end];

	left_end = mid_i - start_i + 1;
	right_end = end_i - mid_i;
	/* copy data to each part*/
	for(i = 0; i < left_end; ++i)
	{
		left_arr[i] = arr[start_i + i];
	}
	
	for (j = 0; j < right_end; j++)
	{
		right_arr[j] = arr[mid_i + 1+ j];
	}
			
	/* merge the temporary arrays */	
 	i = 0;
	j = 0;
	k = left_end;
	while (i < left_end && j < right_end)
	{
		if (left_arr[i] <= right_arr[j])
		{
			arr[k] = left_arr[i];
			++i;
		}
		else
		{
			arr[k] = right_arr[j];
			++j;
		}

		++k;
	}
	/* copy the elemets of the left array */
 	while (i < left_end)
	{
		arr[k] = left_arr[i];
		i++;
		k++;
	}
	/* copy the elemets of the right array */
	while (j < right_end)
	{
		arr[k] = right_arr[j];
		j++;
		k++;
	}
}

int MergeSort(int *arr_to_sort, size_t num_elements)
{
	unsigned i_start = 0, i_end = 0, m = 0;
	i_end = num_elements-1;
	i_mid = (i_end - i_start)/2;

	if((i_end - i_start) <= 1)
	{
		return;
	}

	/* left side */
	MergeSort(arr_to_sort, i_mid);
 
	/* right side */
	MergeSort((arr_to_sort + i_mid), (i_mid + 1));

	/* merging */
	Merger(arr_to_sort , i_start, i_mid, i_end); 
}

