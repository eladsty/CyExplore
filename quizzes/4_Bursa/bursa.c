#include <stdio.h>

/*
Status: 
Reviewer: 
Description:  find indexes to get biggest profit and the profit itself.
Return:  profit
*/
 
#include <stdio.h> /* for printf */
 
#include <stdio.h> /* for printf */
int Bursa(int *price, size_t size, size_t *result);

 


int Bursa(int *price, size_t size, size_t *result)
{
	size_t i = 0, buy_tmp = 0;
	int profit = 0, diff = 0;
	
	result[0] = result[1] = 0;
	for (; i < size; i++)
	{
		diff = price[i] - price[buy_tmp];
		
		if (diff > profit)
		{
			result[0] = buy_tmp;
			result[1] = i;
			profit = diff;
		}
		
		if (price[i] < price[result[0]])
		{
			buy_tmp = i;
		}
	}
	return profit;
}

int main()
{
	int arr[] = {6,12,3,5,1,4,9,2};
	size_t res[2] = { 0 };
	printf("if you buy at %ld and sell at %ld you will make %d\n", res[0], res[1], Bursa(arr, 9, res));
	return 0;
	
}
