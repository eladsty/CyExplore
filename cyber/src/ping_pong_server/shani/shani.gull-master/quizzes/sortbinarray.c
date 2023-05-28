#include <stdio.h>

void swap(int *a, int *b)
{
	int temp = *b;
	*b = *a;
	*a = temp;
}
void SortBinArr(int *arr, int size)
{
	int i = 0, swap_index = 0;
	for (i = 0; i < size; ++i)
	{
		if (arr[i] == 0)
		{
			swap(&arr[i], &arr[swap_index]);
			++swap_index;
		}
	}
}
int main()
{
	int arr[] = {1, 0, 1, 0, 1, 0, 1, 0, 1}, i = 0;
	SortBinArr(arr, 9);
	for (i = 0; i < 9; ++i)
	{
		printf("%d, ", arr[i]);
	}
	printf("\n");
	return 0;
}