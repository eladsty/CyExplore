#include <stddef.h>
#include <time.h>/*show the time*/
#include <stdio.h> /*printf*/

#include "comparison_sorts.h"

int int_arr[5000] = {0};

void MakeRandomArr_5K(int *arr)
{	
	int random_n = 0;
	size_t i = 0;
	for(i=0; i<5000; ++i)
	{
		random_n = rand();
		if(0 == random_n%1111)
		{
			random_n*= -1;
		}
		arr[i] = random_n;
	}
}

void PrintArr_5k(int *arr)
{
	size_t i = 0;
	for(i=0; i<5000; ++i)
	{
		printf("%d, ",arr[i]);
	}
	printf(" \n\n\n\n");
}

int main()
{
  	clock_t tic_bub = 0;
  	clock_t toc_bub = 0;
	clock_t tic_sel = 0;
  	clock_t toc_sel = 0;	 
  	clock_t tic_ins = 0;
  	clock_t toc_ins = 0;

	/*presort - created by MakeRandom*/
 	MakeRandomArr_5K(int_arr);
 	PrintArr_5k(int_arr);
	/*postsort*/
	printf("***Bubble sorted array below***\n\n\n\n");
	tic_bub = clock();
	BubbleSort(int_arr, 5000);
	toc_bub = clock();
	PrintArr_5k(int_arr);
	
	
	/*presort - created by MakeRandom*/
	printf("***random array below***\n\n\n\n");
 	MakeRandomArr_5K(int_arr);
	PrintArr_5k(int_arr);
	/*postsort*/
	printf("***Selection sorted array below***\n\n\n\n");
	tic_sel = clock();
	SelectionSort(int_arr, 5000);
	toc_sel = clock();
	PrintArr_5k(int_arr);
	
	/*presort - created by MakeRandom*/
	printf("***random array below***\n\n\n\n");
 	MakeRandomArr_5K(int_arr);
	PrintArr_5k(int_arr);
	/*postsort*/
	printf("***Insertion sorted array below***\n\n\n\n");
	tic_ins = clock();
	InsertionSort(int_arr, 5000);
	toc_ins = clock();
	PrintArr_5k(int_arr);
	printf("Time elapsed for BubbleSort: %f seconds\n",(double)(toc_bub - tic_bub) / CLOCKS_PER_SEC);
	printf("Time elapsed for SelectionSort: %f seconds\n", (double)(toc_sel - tic_sel) / CLOCKS_PER_SEC);
	printf("Time elapsed for InsertionSort: %f seconds\n", (double)(toc_ins - tic_ins) / CLOCKS_PER_SEC);
	return 0;
}
