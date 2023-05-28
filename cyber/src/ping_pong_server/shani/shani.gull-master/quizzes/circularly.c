#include <stdio.h>

int Pivot(int *arr, size_t size, size_t start, size_t end)
{
	int mid = (size / 2);
	if (start == end || start > end)
	{
		return -1;
	}
	if (arr[mid - 1] > arr[mid] && arr[mid] < arr[mid + 1])
	{
		return mid;
	}
	if (arr[mid] > arr[mid + 1])
	{
		Pivot(arr, size - mid, mid + 1, end);
	}
	if (arr[mid] < arr[mid + 1])
	{
		Pivot(arr, mid, start, mid - 1);
	}
	return -1;
}
int BinarySerach(int *arr, size_t size, size_t start, int num)
{
	size_t mid = start + (size / 2);
	if (num == arr[mid])
	{
		return mid;
	}
	if (num < arr[mid])
	{
		return BinarySerach(arr, mid, start, num);
	}
	if (num > arr[mid])
	{
		return BinarySerach(arr, (size - mid), (mid + 1), num);
	}
	return -1;
}

int main()
{
	int arr[] = {7, 8, 11, 1, 4, 5};
	int num = 5, res = 0;
	int pivot = Pivot(arr, 6, 0, 5);
	if (-1 == pivot)
	{
		return -1;
	}
	if (num == arr[pivot])
	{
		res = pivot;
	}
	else if (num > arr[0])
	{
		res = BinarySerach(arr, (pivot - 1), 0, num);
	}
	else if (num < arr[0])
	{
		res = BinarySerach(arr, (6 - (pivot + 1)), (pivot + 1), num);
	}
	printf("number is at %d index\n", res);
	return 0;
}