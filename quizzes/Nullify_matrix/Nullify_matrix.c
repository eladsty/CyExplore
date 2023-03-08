#include <stdio.h>
 




int main()
{
	int arr[5][5] = {{5,3,0,2,1},{5,3,2,2,1},{1,5,3,2,1},{5,3,2,3,1},{5,3,6,1,0}};
	int i = 0, j = 0;
	int m = 5, n = 5;
	int col_arr[5] = {1,1,1,1,1};
	
	for(i=0 ;i<m; ++i)
	{
		for(j=0 ;j<n; ++j)
		{
			if(0 == arr[i][j])
			{
				col_arr[j] = 0;
				arr[i][0] = 0;
				
			}
		}
	}
	
	 
	for(i=0; i<m; ++i)
	{
		if(0 == arr[i][0])
		{
			for(j=1; j<m; ++j)
			{
				arr[i][j] = 0;
			}
		}
	}
	
	
	for(j=0; j<n; ++j)
	{
		if(0 == col_arr[j])
		{
			for(i=0; i<n; ++i)
			{
				arr[i][j] = 0;
			}
		}
	}
	
	
 

	for(i=0 ;i<m; ++i)
	{
		for(j=0 ;j<n; ++j)
		{
			printf("%d ",arr[i][j]);
		}
		printf("\n");
	}
		
	 
	return 0;
}
