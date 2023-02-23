#include <stddef.h> /*to use NULL*/
#include <stdlib.h> /* for AtoiVsAtoi to use atoi()*/

#include "atoiitoa.h"

/*
	status:approved
	description:turn int to string
	Reviewer: Nawi
	Return: pointer

*/
 
char* Itoa(int val, char* buffer, int base )
{
	char *bufCpy = buffer;
	int valCopy;
	short isNegative = 0;
	
	if(0 == val)
	{
		*buffer = '0';
		return buffer;
	}
	
	if(val < 0)
	{
		++isNegative;
		val *= -1;
	}
	
	valCopy = val;
	
	while (valCopy > 0)
	{
		valCopy = valCopy / base;
		++bufCpy;
	}
	
	*bufCpy = '\0';
 	--bufCpy;
 	
	valCopy = val;
	
 	while(0 < valCopy)
 	{
 		if(valCopy % base > 9 && valCopy % base < 36)
 		{
 			*bufCpy = (char)((valCopy % base) + 55);
 		}
 		else
 		{
 			*bufCpy = (char)((valCopy % base) + 48);
 		}
 		
 		valCopy /= base;
 		--bufCpy;
 	}
 	
 	if(isNegative)
 	{
 		*bufCpy = '-';
 		--bufCpy;
 	}

 	++bufCpy;
	return (char *)bufCpy;
}
 
 /*
	status: READY
	description:turn string into int  
	Reviewer: Nawi  
	Return: int
*/

int Atoi(const char *str)
{
	short isNegative = 1;
	int num = 0;
	const char* p_str = str;
	assert(NULL != str);
	
	if(*p_str == '-')
	{
		isNegative = -1;
		++p_str;
	}
	
	
	while('\0' != *p_str && *p_str >= '0' && *p_str <= '9')
	{
		num = num*10 + ((int)*p_str - 48);
		++p_str;
	}

		
	return num*isNegative;	
}


/*
	status: READY
	description:turn string to int in any base
	Reviewer:  Shani
	Return: int

*/
 
int Atoi36(const char *str, int base)
{
	short is_negative = 1;
	int result = 0;
	char base_bank[] = {"2223456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
	
	if (*str == '-')
	{
		is_negative = -1;
		++str;
	}	
	
	while ('\0' != *str && *str < base_bank[base]) 
	{
		if(!((*str >= 'A' && *str <= 'Z') ||( *str >= '0' && *str <= '9')))
		{
			return result;
		}
		
		if (*str >= '0' && *str <= '9')
		{
			result = (result * base) + (*str - 48);
		}	
		else if(*str >= 'A' && *str <= 'Z')
		{
			result = (result * base) + (*str - 55);
		}
		++str;
	}	
		
	return result * is_negative;
}


/*
	status: 
	description: compares output of Atoi and standard atoi.
	Reviewer:  
	Return: 1 if output is the same, 0 if not.

*/

int AtoiVsAtoi(const char *str)
{
	if(Atoi(str) == atoi(str))
	{
		return 1;
	}
	
	return 0;
}

int TestAtoi()
{
 	char *strings[] = {"-1424","14-24","0","99","","53a22"};  
 	int i = 0;
 	
 	for(;i<6; i++) 
  	{ 
		if(1 != AtoiVsAtoi(strings[i]))
		{
			return 0;
		}
	}
	
	return 1;
}
 
 
