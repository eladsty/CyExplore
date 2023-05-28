#include <stddef.h> /* size_t */
#include <stdlib.h> /* free, malloc */
#include <string.h> /* memcpy */
#include <limits.h> /* MAX INT value */
#include "../../include/sorts/sorts.h"

#define IS2MAX(a, b) (a > b) ? 1 : 0
#define PTR_ICREMENT(a, b) ((*(a) > *(b)) ? (++(b)) : (++(a)))
#define SIZE_DECREMENT(a, b, c, d) ((*(a) > *(b)) ? (--(c)) : (--(d)))
#define MIN2(a, b) (((a) > (b)) ? (b) : (a))
#define MAX2(a, b) (((a) < (b)) ? (b) : (a))
static void Merge(int *arr_to_sort, int start, int middle, int end);
static void SplitRec(int *arr_to_sort, int start, int end);

/* compare function for qsort */
int Comp(const void *index1, const void *index2)
{
	return (*(int *)index1 - *(int *)index2);
}

int IsSorted(int *arr, size_t size)
{
	size_t i = 0;
	for (i = 0; i < (size - 1); ++i)
	{
		if (arr[i + 1] < arr[i])
		{
			return 1;
		}
	}
	return 0;
}

/* not using it */
static size_t LargestIndexValue(int *arr, size_t size)
{
	size_t index = size, i = size - 1;

	for (; i; --i)
	{
		(arr[index] >= arr[i]) ? index : (index = i);
	}

	return index;
}

/* not using it */
static size_t SmallestIndexValue(int *arr, size_t size)
{
	size_t index = 0, i = 1;

	do
	{
		(arr[index] <= arr[i]) ? index : (index = i);
		++i;
	} while (i < size);

	return index;
}

/* safe swap of two values */
static void Swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

/* if need to swap -> swap */
static int ChecknSwap(int i, int *arr)
{
	if (IS2MAX(arr[i], arr[i + 1]))
	{
		Swap(&arr[i], &arr[i + 1]);
		return 1;
	}
	return 0;
}

/* Status : approved
 * Reviewer : Adi
 * Description : iterates over array, swapping each pair of index'es values
				that are not sorted, iterates until all array is sorted.
 * Arguments : array of int, and its size.
 * Return : void
 */
void BubbleSort(int *arr, size_t size)
{
	size_t i = 0;
	size_t itter = 1;
	while (itter)
	{
		itter = 0;
		for (i = 0; i < (size - 1); ++i)
		{
			itter += ChecknSwap(i, arr);
		}
	}
}

/* Status : approved
 * Reviewer : Adi
 * Description : iterates over array, looking for the index with the lowest
				value, and swapping it with the current value being assesed.
 * Arguments : array of int, and its size.
 * Return : void
 */
void SelectionSort(int *arr, size_t size)
{
	size_t index = 0, i = 0;

	for (i = 0; i < size; ++i)
	{
		index = SmallestIndexValue((arr + i), (size - i)) + i;
		if (index > i)
		{
			Swap(&arr[i], &arr[index]);
		}
	}
}

/* Status : approved
 * Reviewer : Adi
 * Description : iterates over array, until a non-sorted pair of indexes is
				found, swaps and iterates backwords until all prior indexes
				are sorted.
 * Arguments : array of int, and its size.
 * Return : void
 */
void InsertionSort(int *arr, size_t size)
{
	size_t i = 1, j = 0;

	while (i < size)
	{
		j = i;
		while (0 < j && ChecknSwap((j - 1), arr))
		{
			--j;
		}
		++i;
	}
}

/* Status : approved
 * Reviewer : Elad
 * Description : conducts binary search of a sorted array itterativly.
 * Arguments : array of int, its size and a value to find.
 * Return : index of found value, -1 if did not find.
 */
size_t IterativeSearch(int *arr, size_t size, int n)
{
	size_t base = 0, top = size;
	size /= 2;
	while (size < top)
	{
		if (arr[base + size] == n)
		{
			return (base + size);
		}
		if (arr[base + size] < n)
		{
			base += size;
			size = top - base;
		}
		size /= 2;
	}
	return -1;
}

/* Status : approved
 * Reviewer : Elad
 * Description : conducts binary search of a sorted array recursivly.
 * Arguments : array of int, its size and a value to find.
 * Return : index of found value, -1 if did not find.
 */
size_t RecursiveSearch(int *arr, size_t start, size_t end, int n)
{
	if (start <= end)
	{
		size_t middle = start + ((end - start) / 2);
		if (arr[middle] == n)
		{
			return middle;
		}
		else if (arr[middle] > n)
		{
			return RecursiveSearch(arr , start, middle, n);
		}
		else
		{
			return RecursiveSearch(arr, (middle + 1), end, n);
		}
	}
	return -1;
}

/* Status :
 * Reviewer :
 * Description : sorts an array of ints.
 * Arguments : arr_to_sort - pointers to array, num_elements - size of array.
 * Return : returns 0 uppon completion.
 */
int RecursiveMerge(int *arr_to_sort, size_t num_elements)
{
	SplitRec(arr_to_sort, 0, (num_elements - 1));
	return 0;
}





static void SplitRec(int *arr_to_sort, int start, int end)
{
	if (start < end)
	{
		int middle = ((start + end) / 2);
		SplitRec(arr_to_sort, start, middle);
		SplitRec(arr_to_sort, (middle + 1), end);
		Merge(arr_to_sort, start, middle, end);
	}
}

static void Merge(int *arr_to_sort, int start, int middle, int end)
{
	int part_one = middle - start + 1;
	int part_two = end - middle;
	int *one_buffer = (int *)malloc((part_one + 1) * sizeof(int));
	int *two_buffer = (int *)malloc((part_two + 1) * sizeof(int));
	int i = 0, j = 0, m = 0, x = 0;
	if (NULL == one_buffer || NULL == two_buffer)
	{
		exit(1);
	}
	for (i = 0; i < part_one; ++i)
	{
		one_buffer[i] = arr_to_sort[start + i];
	}
	one_buffer[part_one] = INT_MAX;
	for (i = 0; i < part_two; ++i)
	{
		two_buffer[i] = arr_to_sort[middle + i + 1];
	}
	two_buffer[part_two] = INT_MAX;
	j = 0;
	for (m = start; m <= end; ++m)
	{
		if (one_buffer[x] < two_buffer[j])
		{
			arr_to_sort[m] = one_buffer[x];
			++x;
		}
		else
		{
			arr_to_sort[m] = two_buffer[j];
			++j;
		}
	}
	free(one_buffer);
	free(two_buffer);
}

int IntCompare(const void *data, const void *param)
{
	if (*(int *)data >= *(int *)param)
	{
		return 1;
	}
	return -1;
}
void swap(void *a, void *b)
{
	int temp;
	temp = *(int *)a;
	*(int *)a = *(int *)b;
	*(int *)b = temp;
}
/* Status : 
 * Reviewer :
 * Description : quick sort
 * Arguments : function sorts an array with num_elem elements of size size_elem.
 * 				The base argument points to the start of the array.
 * 				The comparison function must return an integer less than, equal 
 * 				to, or greater than zero if the first argument is 
 * 				considered to be respectively less than, equal to, or greater 
 * 				than the second. If two members compare as equal, their
       			order in the sorted array is undefined.
 * Return : 
 */
void Qsort(void *base, size_t num_elem, size_t size_elem, int (*compar)(const void *, const void *))
{
	long swap_index = -1;
	size_t i = 0;
	size_t pivot = num_elem - 1;
	if (1 >= num_elem)
	{
		return;
	}
	for (i = 0; i < pivot; ++i)
	{
		if (0 > compar(((char *)base + (pivot * size_elem)), ((char *)base + (i * size_elem))) && -1 == swap_index)
		{
			swap_index = i;
		}

		if (0 <= compar(((char *)base + (pivot * size_elem)), ((char *)base + (i * size_elem))) && -1 != swap_index)
		{
			swap(((char *)base + (swap_index * size_elem)), ((char *)base + (i * size_elem)));
			++swap_index;
		}		
	}
	if (-1 != swap_index)
	{
		swap((char *)base+ (swap_index * size_elem), (char *)base + (pivot * size_elem));
	}
	qsort((char *)base, swap_index, size_elem, compar);
	qsort(((char *)base + ((swap_index + 1) * size_elem)), (num_elem - (swap_index + 1)), size_elem, compar);
	return;
}

/* my original merge, did not pass vlg.. */
/*static int *Merge(int *part_one, int *part_two, size_t size_one, size_t size_two)
{
	size_t final_size = size_one + size_two;
	int *temp = (int *)malloc(final_size * sizeof(int));
	int *start = part_one;
	size_t i = 0;
	if (NULL == temp)
	{
		exit(1);
	}
	while (size_one + size_two)
	{
		if (0 != size_one && *part_one < *part_two)
		{
			*temp = *part_one;
			++temp, ++part_one, --size_one;
		}
		else if (0 != size_two)
		{
			*temp = *part_two;
			++temp, ++part_two, --size_two;
		}
		else
		{
			*temp = *part_one;
			++temp, ++part_one, --size_one;
		}
	}
	temp = temp - final_size;
	part_one = start;
	for (i = 0; final_size; ++i)
	{
		part_one[i] = temp[i];
		--final_size;
	}
	free(temp);
	temp = NULL;
	return part_one;
}*/
