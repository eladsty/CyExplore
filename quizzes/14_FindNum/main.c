#include <assert.h>
#include <stdio.h>/*printf*/
#include <stddef.h> /*size_t*/

/* while(free)  check pointers arithmetic */
int FindNum(int *num_arr, int n, size_t arr_size)
{
	size_t i = 0;
	while(n != num_arr[i] && arr_size > 0)
	{
		++i;
		--arr_size;
	}
	if(num_arr[i] == n)
	{
		return 1;
	}
	return 0;
}

int main()
{
 	int i = 0;
	int arr[10] = {8,4,-3,2,6,77,-21,111,75,0};
	int arr_test[10] = {111,-21,0,1211,20,23};
	for(i=0;i<3;++i)
	{
		printf("should be 1: %d\n",FindNum(arr,arr_test[i],10));
	}
	for(;i<6;++i)
	{
		printf("should be 0: %d\n",FindNum(arr,arr_test[i], 10));
	}
   
	return 0;
}


