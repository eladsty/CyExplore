 #include <stdio.h>
void swap(int *a, int *b);

int partition(int arr[], int l, int r)
{
	int x = arr[r], i = l, j = 0;

	for(j = l; j <= r-1; ++j)
	{
		if( arr[j] <= x)
		{
			swap(&arr[i], &arr[j]);
			++i;
		}
	}
	swap(&arr[i], &arr[r]);
	return i;
}

int MinimumKValue(int arr[], int l, int r, int k)
{
	int min_val = arr[k];
	int pos;
	if(k > 0 && k <= r - l + 1)
	{
		pos = partition(arr, l , r);
		if(pos - 1 == k - 1)
		{
			return MinimumKValue(arr, l, pos - 1, k);
		}
		return MinimumKValue(arr, pos+1, r, (k - pos + l - 1));

	}
    return min_val;
}
void swap(int *a, int *b)
{
	int temp = *a;
	*a  = *b;
	*b = temp;
}

int main()
{
    int arr[] = {-2,55,4,1,2,-7,9,2,3,7,4,5,7,44,777,8,8,9,99,33 };
    unsigned size = sizeof(arr) / sizeof(int);
    int res = MinimumKValue(arr, 0,size - 1 ,3);
	printf("the min value of the give k is: %d\n", res);
    return 0;
}