#include <stdio.h>

#include "sorting.h"
#define ARRAYLEN(arr)(sizeof(arr) / sizeof(int))
int main()
{
	int unsorted[] = { 333,11,5,666,100,-26,-33,0}; 
 	int results2[] = { -11,11,5,666,100,2626,6267,8888}; 
 	int results1[] = {1,22,3,44,5,66,7,88};
 	int results[] = {11,2,33,4,55,6,77,8};
	int int_arr2[] = {-11,1,5,66,100,262,6267,8888};
	int int_arr[] = {1,2,3,4,5,6,7,8};
 	size_t i = 0; 
  
 	printf("array length should be 8: %d\n", ARRAYLEN(int_arr));
 	
 	for(i = 0; i < 8; ++i)
 	{
 		printf("%d iterative: %d\n",results[i], IterativeSearch( results[i],int_arr,ARRAYLEN(int_arr))); 
 	}
    for(i = 0; i < 8; ++i)
 	{
 		printf("%d recursive: %d\n",results[i], RecursiveSearch( results[i],int_arr,0, ARRAYLEN(int_arr) -1)); 
 	}


 

 for(i = 0; i < 8; ++i)
 	{
 		printf("%d from result: %d\n",results[i], RecursiveSearch( results[i],int_arr,0, ARRAYLEN(int_arr) -1)); 
 	}
	
	printf(" before sorting\n");

 	for(i = 0; i < 8; ++i)
	{
		printf(" %d, ",unsorted[i] );
	}
	printf("\n");

	MergeSort(unsorted, 8);
	
	printf(" after sorting\n");


 	for(i = 0; i < 8; ++i)
	{
		printf(" %d, ",unsorted[i]);
	}

	return 0;
} 
  