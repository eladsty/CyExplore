 #include <stdio.h>



int MinimumKValue(int *arr, unsigned len, unsigned k)
{
	unsigned i = 0; 
	int min_val = arr[k];

	for(i = k; i < len ; i += k)
	{
		if(arr[i] < min_val)
		{
			min_val = arr[i];
		}
	}
	 
    return min_val;
}

int main()
{
    int arr[] = {-2,55,4,1,2,-7,9,2,3,7,4,5,7,44,777,8,8,9,99,33 };
    unsigned size = sizeof(arr) / sizeof(int);
    int res = MinimumKValue(arr, size ,3);
	printf("the min value of the give k is: %d\n", res);
    return 0;
}