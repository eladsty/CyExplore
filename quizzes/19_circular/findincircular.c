#include <stdio.h>

void FindInCircular(int *arr, int len, int num)
{
 
    int low = 0, high = len - 1;
 
    while (low <= high)
    {
        
        int mid = (low + high)/2;
 
        if (num == arr[mid]) 
		{
            printf("Number was found at index: %d \n", mid);
			return;
        }
 
        if (arr[mid] <= arr[high])
        {
             
            if (num > arr[mid] && num <= arr[high]) 
			{
                low = mid + 1;     
            }
            else 
			{
                high = mid - 1;    
            }
        }
 
        else 
		{
            if (num >= arr[low] && num < arr[mid]) 
			{
                high = mid - 1;      
            }
            else 
			{
                low = mid + 1;     
            }
        }
    }
 
    printf("Number wasn't found.\n");
}
 
int main(void)
{
    int arr[] = {6, 7 ,8 ,-1, 1 ,2 ,3 ,4 ,5 };
	int res[] = {-1,1,5,6,11,-2};
	unsigned i = 0;
	unsigned arr_len = sizeof(arr) / sizeof(int);
	unsigned res_len = sizeof(res) / sizeof(int);
	
	for(i = 0; i < res_len; ++i)
	{
		FindInCircular(arr,arr_len, res[i]);
	}
 
    return 0;
}
	
 
 