#include <stddef.h>/*size_t*/
#include <stdio.h>/*printf*/

size_t OneMillChar(char c)
{
	size_t most_times = 0;
	int i = 0;
	static char flag = 0;
	static size_t char_count_arr[127];
	
	if(0 == c)
	{
		while(i < 127)
		{
			if(most_times < char_count_arr[i])
			{
				most_times = char_count_arr[i];
			}
			++i;
		}
		return most_times;
	}
	
	if(0 == flag)
	{
		for(i = 0; i<127; ++i)
		{
			char_count_arr[127] = 0;
		}
	}
	++char_count_arr[c-1];
	
	++flag;
	
	return most_times;
}

size_t CountBits(long n)
{
	size_t cnt = 0;
	while(n)
	{
		n = n&(n-1);
		++cnt;
	}
	return cnt;
}

int main()
{
	int i = 0;
	for(i = 0 ;i<100;++i)
	{
	
 
		if(0 == i%11)
		{
			OneMillChar('4');
		}
		if(0 == i%5)
		{
			OneMillChar('b');
		}
	}
	
	printf("most times same char appeared is: %ld\n", OneMillChar(0));
  
	printf("count set bit of 143 is 5,result is: %ld\n", CountBits(143));
	return 0;
}

