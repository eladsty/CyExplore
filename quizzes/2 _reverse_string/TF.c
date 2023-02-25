#include <assert.h>
#include <string.h>

#include "header.h"

void TF(int num)
{
	int i = 1;
	
	for(; i<=num; ++i)
	{
		if(0 == i%15)
		{
			printf("TF\n");
		}
		
		else if( 0 == (i%3))
		{
			printf("T\n");
		}
		
		else if( 0 == (i%5))
		{
			printf("F\n");
		}
		else
		{			
			printf("%d\n",i);
		}
	}	
	 
}

char ToLower(char c)
{
	return (c > 'A' && c < 'Z'? c+32: c);
}

void StrReverser(char *str)
{
	size_t len = strlen(str);
 	char temp;
 	size_t i = 0;
 	
 	for(;i<(len/2); ++i)
 	{
 		temp = str[i];
 		str[i] = ToLower(str[len-i-1]);
 		str[len-1-i] = ToLower(temp);
 	}
 	
}

