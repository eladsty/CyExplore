#ifndef __SORTS_H_CR4__ 
#define __SORTS_H_CR4__ 

#include <stddef.h> /* size_t */


void InsertionSort(int *arr, size_t size);
void SelectionSort(int *arr, size_t size);
void BubbleSort(int *arr, size_t size);

int Comp(const void *index1, const void *index2);
int IsSorted(int *arr, size_t size);
struct test
	{
		void (*func)(int *arr, size_t size);
		char *name;
	};

size_t IterativeSearch(int *arr, size_t size, int n);
size_t RecursiveSearch(int *arr, size_t start, size_t end, int n);
int RecursiveMerge(int *arr_to_sort, size_t num_elements);
void Qsort(void *base, size_t num_elem, size_t size_elem, int (*compar)(const void *, const void *));
#endif /* __SORTS_H_CR4__ */
