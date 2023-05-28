#include <stdio.h>
int IsSumFound(int *arr, int sum, int arr_size);

int main()
{
	int arr[10] = {1, 3, 5, 6, 10, 12, 17, 20, 25, 29};
	printf("%d\n", IsSumFound(arr, 15, 10));
	return 0;
}

int IsSumFound(int *arr, int sum, int arr_size)
{
	int *end = arr + (arr_size - 1), *start_saver = arr;
	while (*arr != *end)
	{
		if (sum == (*arr+*end))
		{
			
			printf("first index is %ld, second index is %ld\n", (arr - start_saver), (end - start_saver));
			return 1;
		}
		if (sum < (*arr+*end))
		{
			--end;
			continue;
		}
		else if (sum > (*arr+*end))
		{
			++arr;
			continue;
		}
	}
	return 0;
}
