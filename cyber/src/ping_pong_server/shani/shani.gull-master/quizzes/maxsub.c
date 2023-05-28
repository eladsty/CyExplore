#include <stdio.h>
#include <stdlib.h>
int *MaxSubArray(int *arr, int size, int *result);
int main()
{
		int res[3], arr[9] = {1, 4, -5, -2, -3, 10, 1, -2, 5};
		MaxSubArray(arr, 9, res);
		printf("low index: %d, high index: %d, max: %d\n", res[0], res[1], res[2]);
		return 0;
}

int *MaxSubArray(int *arr, int size, int *result)
{
	int tmp_low, tmp_high, tmp_max = 0, low = 0, high = 0, max = 0, i = 0;
	for (; i < size; i++)
	{
		if (arr[i] >= 0)
		{
			tmp_max = arr[i];
			max = arr[i];
			low = i;
			high = i;
			while (tmp_max >= 0 && i < size)
			{
				tmp_max += arr[i];
				if (tmp_max > max)
				{
					high = i;
					max = tmp_max;
				}
				++i;
			}

		}

		
		
				
	}
	result[0] = low;
	result[1] = high;
	result[2] = max;
	return result;
}
