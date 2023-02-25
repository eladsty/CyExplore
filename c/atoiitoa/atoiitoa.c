#include <stddef.h> /*to use NULL*/
#include <stdlib.h> /* for AtoiVsAtoi to use atoi()*/
#include <stdio.h>/* printf */

#include "atoiitoa.h"






/*
	status:approved
	description:turn int to string
	Reviewer: Nave
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
	char base_bank[] = {"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
	
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
	Reviewer:  Shani
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


/*
	status: 
	description: compares output of Atoi and standard atoi w builed in test cases.
	Reviewer:  Shani
	Return: 1 if output is the same, 0 if not.
*/

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
 


/*
	status: READY
	description:  print character that appear in arr1 and 2 but not 3
	Reviewer:   Shani
	Return:  print
*/

void *InTwoOutOfThree(char *arr1, char *arr2, char *arr3)
{
	char my_buffer[128] = {0};
	
	assert(NULL != arr1 && NULL != arr2 && NULL != arr3);
	
	while('\0' != *arr1)
	{	
		++my_buffer[(int)*arr1];	
		++arr1;
	}
	
	while('\0' != *arr3)
	{
		if(my_buffer[(int)*arr3])
		{
			my_buffer[(int)*arr3] = 0;
		}
		++arr3;
	}
	
	while('\0' != *arr2)
	{
		if(my_buffer[(int)*arr2])
		{
			printf("%c is common between array 1st and 2nd but not 3rd\n", *arr2); 
			my_buffer[(int)*arr2] = 0;
		}
		++arr2;
	}
}
 
 
/*
	status: READY
	description:  check if little endian and return 1 else 0l
	Reviewer:   Shlomi 
	Return:  1 or 0.
*/
int IsLittleEndian()
{
	short n = 1;
	return (*(char *)&n == 1? 1: 0);
}


 
 
 
