#include <stdio.h>


/*
Status: 
Reviewer: 
Description: recieve sorted array of ints and a sum, return 1 if it finds 2 numbers in the array that sum up to the sum provided to the function, and their indexes, return 0 otherwise.
Return: 1 if two numbers
*/

int IsSumFound(int arr[],int len, int sum, int indexes[2])
{
	int l_i = 0, r_i = len-1;
	
	while (l_i <= r_i)
	{
		if ((arr[l_i] + arr[r_i]) > sum)
		{
			--r_i;
		}
		else if ((arr[l_i] + arr[r_i]) < sum)
		{
			++l_i;
		}
		else if ((arr[l_i] + arr[r_i]) == sum)
		{
			indexes[0] = l_i;
			indexes[1] = r_i;
			return 1;
		}
	}
	return 0;
}

int main()
{
	int arr1[] = {2 ,4 ,7 ,12, 14};
	int arr2[] = {-3 ,-1 ,0 ,5 ,6};
	int sum1 = 21;
	int sum2 = 4; 
 	
	int indexes[] = {0,0};
	
	printf("should print 1: %d \n ",IsSumFound(arr1, 5, sum1, indexes));
	printf("should print 2 and 4: %d and %d \n ",indexes[0],indexes[1]);
 	
	
	printf("should print 1: %d \n ",IsSumFound(arr2, 5, sum2, indexes));
	printf("should print 1 and 3: %d and %d \n ",indexes[0],indexes[1]);
	
	printf("should print 0: %d \n ",IsSumFound(arr2, 5, sum1, indexes));
	
	
	return 0;
}
