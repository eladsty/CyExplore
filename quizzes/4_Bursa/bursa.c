#include <stdio.h>

/*
Status: 
Reviewer: 
Description:  find indexes to get biggest profit and the profit itself.
Return:  profit
*/
/*worked but need further testing */

int Bursa(int price[], int len, int profit_buy_sell_i[])
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
		
			
int main(void)
{
	int profit_buy_sell_i[3] = {0};
	int price[] = {6,12,3,5,1,4,9,2};
	int len = 8;
 
	 
		Bursa(price, len, profit_buy_sell_i);
		printf("best profit is: %d.\n buy here: %d, sell here: %d\n", profit_buy_sell_i[0],profit_buy_sell_i[1],profit_buy_sell_i[2]);
		
	return 0;
}
