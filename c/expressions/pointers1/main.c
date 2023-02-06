#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pointExp.h"

int main()
{
	int arr[5] = {3,4,5,6,7};
	int N = sizeof(arr)/sizeof(arr[0]);
	int *p_cArr = CopyArr(arr, N);
	printf("%d", *p_cArr);
	
	return 0;
}




 
