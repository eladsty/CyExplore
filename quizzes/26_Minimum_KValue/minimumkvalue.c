 #include <stdio.h>
 
 
int partition(int arr[], int l, int r)
{
    int pivot = arr[r-1], i = 0, piv_j = l, j = 0;

    for (j = l; j < r; ++j) 
    {	
		if (arr[j] <= pivot) 
		{
			++i;
			arr[i] ^= arr[j];
			arr[j] ^= arr[j];
			arr[j] ^= arr[j];
		}
    }
    arr[i+1] ^= arr[r];
    arr[r] ^= arr[i+1];
    arr[i+1] ^= arr[r];
    return i+1;
}

int MinimumKValue(int arr[], int l, int r, int k)
{
	int piv_i = 0;
	if (k > 0 && k <= r - l) 
	{
		piv_i = partition(arr, l, r);
		if (piv_i - l == k - 1)
		{
			return arr[piv_i];
		}
		else if (piv_i - l > k - 1)
		{
			return MinimumKValue(arr, l, piv_i - 1, k);
		}
		else
		{
			return MinimumKValue(arr, piv_i + 1, r, k);
		}
	}
}

int main()
{
	int kth = 5;
    int arr[] = {-2,55,4,1,2,-7,9,2,3,7,4,5,7,44,777,8,8,9,99,33 };
	int arr2[] = {9,8,7,6,5,4,3,2,1,88,77,66,55,44,33,22,11,0};
    unsigned size = sizeof(arr2) / sizeof(int);
    int res = MinimumKValue(arr2, 0, size ,kth);
	printf("the min value of the give k is: %d\n", res);
    return 0;
}
