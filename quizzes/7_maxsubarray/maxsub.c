
#include <stdio.h>

void MaxSubArray(int *arr, size_t size, int ans[2])
{
  size_t start = 0, end = 0;
  size_t i = 0;
  int max_so_far = arr[0], max_ending_here = arr[0];

  for(i = 1; i < size; ++i)
  {
    if(arr[i] > max_ending_here + arr[i])
    {
      start = i;
      max_ending_here = arr[i];
    }
    else
    {
      max_ending_here += arr[i];
    }

    if(max_so_far < max_ending_here)
    {
      max_so_far = max_ending_here;
      end = i;
    }
  }

  ans[0] = start;
  ans[1] = end;
}

int main(void)
{
	int nums[] = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
	int msa[2] = { 0, 0 };
	
	MaxSubArray(nums, sizeof(nums)/sizeof(nums[0]), msa);
	
	printf("Max Sub Array starts at %d and ends in %d\n", msa[0], msa[1]);
	
	return 0;
}












/*


/*
	int start_i = 0, end_i = 0, max_sum = 0, temp_sum;
  	unsigned i = 0 , j = 0;
	
	while(i < len);
	{
 		
 		if(arr[i] >= 0)
 		{
	 		if(arr[i] > temp_sum)
	 		{
	 			max_sum = arr[i];
	 			start_i = i;
	 			end_i = i;
	 		}
 		}
 		
 		++end_i;
 		++i;
 	}
 	
	while(i2 >= len)
	{
		if((array[i1] + array[i2]) > max_sum)
 		{
 			max_sum = array[i1] + array[i2];
 			max_i1 = i1;
 			max_i2 = i2;
 		}
		++i2;
	}
	
/*
 arr[start_i] + (end_i == start_i ? 0 : arr[end_i]);

	printf("should be 3,6 and 8.\ni1 is: %d, i2 is: %d, sum is:%d \n", max_i1, max_i2, max_sum); */
 	
	

 
