#include <stdio.h> /* printf for testing */

int FindNum2(int *arr, int num, int size)
{
	for (i = 0;  arr[i] != (arr[i] & num); ++i);
	printf("%d\n",arr[6]);
	return 0;
}


int main()
{
	int arr[] = {1, 3, 6, 7, 89, 14, -5};
	int num[] = {1, 5, 13, 14, -5};
	int i = 0;
	for ( ; i < 5; ++i)
	{ 
		FindNum(arr, num[i], 7);
	}		
	return 0;
}

int FindNum(int *arr, int num, int size)
{
	int i = 0;
	for (i = 0; i < size && arr[i] != num; ++i);
	return ((i == size) ? 1 : 0);
}
