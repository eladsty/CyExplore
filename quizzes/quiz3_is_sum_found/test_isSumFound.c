#include "isSumHead.h"


int main()
{
	int arr[] = {2,4,7,12,14};
	int arr2[] = {2,4,7,12,-14};
	int sum = 21;
	int sum2 = -7;
	
	assert(1 == IsSumFound(arr, sum));
	assert(1 == IsSumFound(arr2, sum2));
	return 0;
}
