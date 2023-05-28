#include <time.h> /* clock() */
#include <stdlib.h> /* qsort */
#include <stdio.h> /* printf */
#include <string.h> /* memcpy */
#include "../../include/sorts/sorts.h"


#define TEST 5000
void BinaryTest(int *sorted_even, int *sorted_odd);
void RandomArray(int *arr)
{
	size_t j = 0;
	for (j = 0; j < TEST; ++j)
		{
			arr[j] = rand() % 100;
		}
	return;
}


int main(void)
{
	size_t i = 0, j = 0;
	int test_array[6][TEST];
	int sorted_even[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int merge_test[10] = {-10, 1, 19, 3, 0, 5, 53, 7, 200, 9};
	int sorted_odd[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int qsort_doubles[5] = {1, 4, 7, 9, 1};
	clock_t start_t, end_t;
	float total_time = 0;
	int merge[4] = {1, 0, 4, 3};
	

	/* create LUT */
	struct test test_t[3] = {{&BubbleSort, "BubbleSort"}, 
							{&SelectionSort,"SelectionSort"}, 
							{&InsertionSort, "InsertionSort"}};
	RandomArray(test_array[0]);
	for (i = 1; i < 5; ++i)
	{
		for (j = 0; j < TEST; ++j)
		{
			memcpy(test_array[i], test_array[0], TEST * sizeof(int));
		}
	}
	
	/* use LUT to feed test_array to each function */
	for (i = 0; i < 3; ++i)
	{
		
		total_time = 0;
		start_t = clock();
		test_t[i].func(test_array[i], (sizeof(test_array[i])/ sizeof(int)));
		end_t = clock();
		total_time = (double)(end_t - start_t) / CLOCKS_PER_SEC;
		printf("++++++ in function %s ++++++\n", test_t[i].name);
		if (!(IsSorted(test_array[i], TEST)))
		{
			printf("list sorted\n");
		}
		printf("total duration %f  seconds\n \n", 
				total_time);
		
		
	}
	printf("           -qsort-\n");
	total_time = 0;
	start_t = clock();
	qsort(test_array[i], TEST, sizeof(int), Comp);
	end_t = clock();
	total_time = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	if (!(IsSorted(test_array[i], TEST)))
		{
			printf("qsort list sorted\n");
		}
	printf("total duration %f  seconds\n \n", 
			total_time);
	
	++i;
	printf("           -Qsort-\n");
	total_time = 0;
	start_t = clock();
	/*Qsort(test_array[i], TEST, sizeof(int), Comp);*/
	Qsort(qsort_doubles, 5, 4, Comp);
	printf("%d, %d, %d, %d, %d\n", qsort_doubles[0], qsort_doubles[1], qsort_doubles[2], qsort_doubles[3], qsort_doubles[4]);
	end_t = clock();
	total_time = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	if (!(IsSorted(test_array[i], TEST)))
		{
			printf("qsort list sorted\n");
		}
	printf("total duration %f  seconds\n \n", 
			total_time);
	++i;
	printf("i = %d\n", i);
	BinaryTest(sorted_even, sorted_odd);
/*********************************************************************/
	printf("           -RecursiveMerge-\n");	total_time = 0;
	RecursiveMerge(test_array[i], (sizeof(test_array[i])/ sizeof(int)));
	if (!(IsSorted(test_array[i], TEST)))
		{
			printf("merge list sorted\n");
		}
	
	return 0;
}

void BinaryTest(int *sorted_even, int *sorted_odd)
{
	size_t i = 0;
	size_t find = 0;
	printf("\n\n\n\n\n           -binary search-\n");
	printf("iterative\n");
	for (i = 0; i < 10; ++i)
	{
		find = IterativeSearch(sorted_even, 10, i);
		printf("the value %ld is at index %ld\n", i, find);
	}
	for (i = 0; i < 11; ++i)
	{
		find = IterativeSearch(sorted_odd, 11, i);
		printf("the value %ld is at index %ld\n", i, find);
	}
	printf("recursive\n");
	for (i = 0; i < 10; ++i)
	{
		find = RecursiveSearch(sorted_even, 0, 9, i);
		printf("the value %ld is at index %ld\n", i, find);
	}
	for (i = 0; i < 11; ++i)
	{
		find = RecursiveSearch(sorted_odd, 0, 10, i);
		printf("the value %ld is at index %ld\n", i, find);
	}
}
