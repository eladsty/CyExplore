#include <stdio.h>

void RowSum(int SumArr[3], int **lsarr, size_t col, size_t row)
{
	int i = 0, j = 0;
	
 	for(;i < 3; i++)
 	{
 		for(j = 0; j < 3; ++j)
 		{
 			SumArr[i] += arr[i][j];
 		}
 
 	}
}

int main()
{
	int i = 0;
	int arr[3][3] = {{4,-5,2},{-3,1,11},{9,0,4}};
	int SumArr[3];
	RowSum(SumArr,arr);	
	
	for(i=0; i<3 ;i++)
	{
		printf("%d\n", SumArr[i]);
	}

	return 0;
}
