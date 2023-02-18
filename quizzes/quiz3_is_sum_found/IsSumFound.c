#include "isSumHead.h"

int IsSumFound(int arr[5], int sum)
{
	size_t indexes[2] = {0,0};
	int p_end = 4;
	int p_start = 0;
 
	assert(NULL != arr);
		
	while(p_start < p_end)
	{
		if(sum == (arr[p_start]+arr[p_end]))
		{
			indexes[0] = p_start;
			indexes[1] = p_end;
			/*maybe here use malloc and return the indexes array*/
			
			return 1;
		} 
		
		else if (sum > (arr[p_start]+arr[p_end]))
		{
			++p_start;
		}
		
		else
		{
			--p_end;
		}
	
	}
 
	return 0;
}
