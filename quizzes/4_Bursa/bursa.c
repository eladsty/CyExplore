#include <stdio.h>
#include <stddef.h>

void Bursa(int *prices, size_t size, int result[3])
{
    int max = prices[size-1];
    int min = prices[size-1];
    int i = 0;

    for (i = size - 2; i >= 0; --i)
    {
      if (prices[i] > max)
      {
        max = prices[i];
        min = prices[i];
        continue;
      }
      
      if (prices[i] < min)
      {
        min = prices[i];
        if(max - min > result[2])
        {
	        result[0] = min;
	        result[1] = max;
	        result[2] = max - min;
        }
       }
    
     }
}

int main(void)
{
	int prices[] = {6,12,3,5,1,4,9,2};
	int res[3] = { 0, 0, 0 };
	
	Bursa(prices, sizeof(prices)/sizeof(prices[0]), res);
	printf("Buy: %d  Sell: %d  Price: %d\n", res[0], res[1], res[2]);
	
	return 0;
}


 
