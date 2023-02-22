#include <stdlib.h> /*for abs*/

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
 

/*
Atoi()
Itoa36()

*/
