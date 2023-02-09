#include <stdio.h>

int Survival (int *arr)
{	
	int i=0; 
	
	while(arr[i] != i)
	{
		arr[i] = arr[arr[i]];
		i = arr[i];
	}

	return i;
}

int main()
{
	int arr[100];
	int i = 0;
	for(;i<100;i++)
	{
		arr[i] = i+1;
	}
	arr[99] = 0;
	
 
	 
	
	printf("%d", Survival(arr));
	return 0;
}
