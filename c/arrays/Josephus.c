#include <stdio.h>

int Survival(int *arr)
{	
	int i=0; 
	
	while(arr[i] != i)
	{
		arr[i] = arr[arr[i]];
		i = arr[i];
	}

	return i+1;
}

int main()
{
	int arr[100];
	int arr2[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,0};
	int i = 0;

	for(;i<100;++i)
	{
		arr[i] = i+1;
	}
	arr[99] = 0;
	
 	
 	printf("%d\n", Survival(arr2));
	printf("%d\n", Survival(arr));
	return 0;
}
