#include <stdio.h>

void RowSum(int *SumArr, int *arr, size_t col, size_t row)
{
	size_t i = 0, j = 0;
	
 	for(;i < row; i++)
 	{
 		for(j = 0; j < col; ++j)
 		{
 			SumArr[i] += arr[i * col + j];
 		}
 
 	}
}

int main()
{
	int i = 0;
	int arr[3][3] = {{4,-5,2},{-3,1,11},{9,0,4}};
	int SumArr[3];
	
	RowSum(SumArr,arr[0],3,3);	
	
	for(i=0; i<3 ;i++)
	{
		printf("%d\n", SumArr[i]);
	}

	return 0;
}
