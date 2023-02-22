#include <stddef.h> /*to use NULL*/


#include "atoiitoa.h"

 
 
char* Itoa(int val, char* buffer, int base)
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
 		*bufCpy = (char)(valCopy % base) + 48;
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
 
int Atoi(const char *str)
{
	short isNegative = 0;
	int num = 0;
	const char* p_str = str;
	assert(NULL != str);
	
	if(*p_str == '-')
	{
		++isNegative;
		++p_str;
	}

	while('\0' != *p_str && *p_str >= '0' && *p_str <= '9')
	{
		num = num*10 + ((int)*p_str - 48);
		++p_str;
	}

	if(isNegative)
	{
		num *= -1;
	}
		
	return num;	
}

 
