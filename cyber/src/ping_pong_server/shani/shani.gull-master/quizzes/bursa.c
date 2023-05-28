#include <stdio.h> /* for printf */
#include <assert.h>
int Bursa(int *price, size_t size, size_t *result);

int main()
{
	int arr[] = {19, 7, 5, 8, 2, 10, 11, 1, 8};
	size_t res[2] = { 0 };
	char *ptr = NULL;
	assert(ptr);
	printf("if you buy at %ld and sell at %ld you will make %d\n", res[0], res[1], Bursa(arr, 9, res));
	return 0;
	
}


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
