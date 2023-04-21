#include <stdio.h>

void SortArr10(int *arr, int *len)
{
	int i = 0, j = 0;
	for(j = 0; j < *len ; ++j)
	{
		if(0 == arr[j])
		{
			arr[i] ^= arr[j];
			arr[j] ^= arr[i];
			arr[i] ^= arr[j];
			++i;
		}
	}
}


int main()
{
	int arr[] = {0,1,0,1,0,1,0,1,1,1,1,1};
	int arr2[] = {0,1,0,1,0,1,0,1,1,1,1,0};
	int i = 0;
	int len = sizeof(arr) / sizeof(int);
	
	SortArr10(arr, &len);
	for(i = 0; i < len ; ++i)
	{
		printf("%d, ", arr[i]);
	}
	printf("\n\n");

	SortArr10(arr2 , &len);
	for(i = 0; i < len ; ++i)
	{
		printf("%d, ", arr2[i]);
	}

	return 0;
	
}
