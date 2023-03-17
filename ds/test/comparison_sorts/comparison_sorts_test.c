#include <stddef.h>
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
	/*presort*/
	printf("***random array below***\n\n\n\n");
 	MakeRandomArr_5K(int_arr);
 	PrintArr_5k(int_arr);
	/*postsort*/
	printf("***Bubble sorted array below***\n\n\n\n");
	BubbleSort(int_arr, 5000);
	PrintArr_5k(int_arr);
	
	
	/*presort*/
	printf("***random array below***\n\n\n\n");
 	MakeRandomArr_5K(int_arr);
	PrintArr_5k(int_arr);
	/*postsort*/
	printf("***Selection sorted array below***\n\n\n\n");
	SelectionSort(int_arr, 5000);
	PrintArr_5k(int_arr);
	
	/*presort*/
	printf("***random array below***\n\n\n\n");
 	MakeRandomArr_5K(int_arr);
	PrintArr_5k(int_arr);
	/*postsort*/
	printf("***Insertion sorted array below***\n\n\n\n");
	InsertionSort(int_arr, 5000);
	PrintArr_5k(int_arr);
	
	
	
	return 0;
}
