void Swap(int *n1, int *n2)
{
	if(*n1 != *n2)
	{
		*n1 ^= *n2;
		*n2 ^= *n1;
		*n1 ^= *n2; 
	}
}

int Partition(int arr[], int low, int high, unsigned k)
{
	int pivot_value = arr[high];
	int i = k, j = 0;
	for( j = low; j < high; j += k)
	{
		if( arr[j] <= pivot_value)
		{
			Swap(&arr[i], &arr[j]);
			i += k;
		}
	}
	Swap(&arr[i], &arr[high]);
	return i;
}

void QuickSortK_recursion(int *arr, unsigned low, unsigned high, unsigned k)
{
    int pivot_i;
    if(low < high)
    {
        pivot_i = Partition(arr, low, high, k);
		QuickSortK_recursion(arr, low, pivot_i - 1, k);
		QuickSortK_recursion(arr, pivot_i + 1, high, k);
	}
    
}

 void QuickSortK(int *arr, unsigned len, unsigned k)
{
    QuickSortK_recursion(arr, 0, len - 1, k);
}


int MinimumKValue(int *arr, unsigned len, unsigned k)
{
    QuickSortK(arr, len, k);
    

    return arr[k];
}

int main()
{
    int arr[] = {-2,55,4,1,2,-7,9,2,3,7,4,5,7,44,777,8,8,9,99,33};
    unsigned size = sizeof(arr) / sizeof(int);
    MinimumKValue(arr, size ,3);

    return 0;
}