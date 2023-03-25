#include <stdio.h>

/*
Status: 
Reviewer: 
Description:  find indexes to get biggest profit and the profit itself.
Return:  profit
*/
/*worked but need further testing */

int Bursa(int price[], int len, int profit_summary[])
{
	 unsigned i = 0, buy_i = 0, sell_i = 1, max_profit, temp_profit = 0;
	 
	 while(sell_i < len)
	{
	 	if(price[buy_i] < price[sell_i])
	 	{
	 		temp_profit = price[buy_i] - price[sell_i];
	 		max_profit = (max_profit > temp_profit ? max_profit : temp_profit);
	 	}
	 	else
	 	{
	 		buy_i = sell_i;
	 		++sell_i;
	 	}
	}
	
	profit_summary[0] = max_profit;
	profit_summary[1] = buy_i;
	profit_summary[2] = sell_i;
	
 	return 0;
}	
		
			
int main(void)
{
	int profit_summary[3] = {0};
	int price[] = {6,12,3,5,1,4,9,2};
	int len = 8;
 
	 
		Bursa(price, len, profit_summary);
		printf("best profit is: %d.\n buy here: %d, sell here: %d\n", profit_summary[0],profit_summary[1],profit_summary[2]);
		
	return 0;
}
