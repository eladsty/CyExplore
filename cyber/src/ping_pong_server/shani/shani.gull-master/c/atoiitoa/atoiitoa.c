#include "atoiitoa.h"
#include <stdio.h>
#include <stdlib.h> /* abs */

/* 0 1 2 3 4 5 6 7 8 9 0 A B C D ... Z */


/* #############################*/
/* # Ex.1                      #*/
/* # status: approved          #*/
/* # reviewer: Adi             #*/
/* # description: this func    #*/
/* # will convert int to str   #*/
/* # return: ptr to arr        #*/
/* # special notes: itoa and   #*/
/* # atoi for base 10          #*/
/* #############################*/
char *ItoA(int n, char *buffer, int radix)
{
	int i = 1, m = n, base = 0;
	if (n < 0)
	{
		n = abs(n);
		++i, ++base;
		buffer[0] = (char)45;
	}
	
	while (m / radix)
	{
		++i;
		m = m / radix;
	}
	buffer[i] = '\0';
	for ( ; i > base; i--)
	{
		buffer[i - 1] = (char)(n % radix + 48);
		n = n / radix;
	}
	
	return buffer;
}
/* #############################*/
/* # Ex.1                      #*/
/* # status: approved          #*/
/* # reviewer: Adi             #*/
/* # description: this func    #*/
/* # will convert str to int   #*/
/* # return: ptr to arr        #*/
/* # special notes: itoa and   #*/
/* # atoi for base 10          #*/
/* #############################*/
int Atoi(const char *nptr)
{
	const char *temp;
	int neg_flag = 1;
	int result = 0;
	assert(nptr);
	temp = nptr;
	if (*temp == '-')
	{
		neg_flag = -1;
		++temp;
	}
	while ('\0' != *temp)
	{
		if (*temp < 58 && *temp > 47)
			{	
				result = result * 10 + (*temp - 48);
				++temp;
			}
		else
		{
			return (result * neg_flag);
		}
	}
	return (result * neg_flag);
}

/* #############################*/
/* # Ex.1                      #*/
/* # status: approved          #*/
/* # reviewer: Adi             #*/
/* # description: this func    #*/
/* # will convert int to str   #*/
/* # return: ptr to arr        #*/
/* # special notes: itoa and   #*/
/* # atoi for all bases        #*/
/* #############################*/
char *ItoA36(int n, char *buffer, int radix) /* int to base_x*/
{
	int i = 1, m = n, base = 0;
	if (n < 0)
	{
		n = abs(n);
		++i;
		++base;
		*buffer = '-';
	}
	buffer[i] = '\0';
	while (m / radix)
	{
		++i;
		m /= radix;
	}
	for ( ; n != 0; --i)
	{
		buffer[i - 1] = (char)REPCON_ITOA(n % radix);
		n = n / radix;
	}
	return buffer;
}
/* #############################*/
/* # Ex.1                      #*/
/* # status: approved          #*/
/* # reviewer: Adi             #*/
/* # description: this func    #*/
/* # will convert str to int   #*/
/* # return: ptr to arr        #*/
/* # special notes: itoa and   #*/
/* # atoi for all bases        #*/
/* #############################*/
int Atoi36(const char *nptr, int radix) /* base_x to int*/
{
	const char *temp = nptr;
	int neg_flag = 1;
	int result = 0;
	if (*temp == '-')
	{
		neg_flag = -1;
		++temp;
	}
	while (radix > 10) /* '\0' != *temp */
	{
		if ((*temp < 58 && *temp > 47) || (*temp < 91 && *temp > 64))
			{	
				result = result * radix + (REPCON_ATOI(*temp));
				++temp;
			}
		else
		{
			return (result * neg_flag);
		}
	}
	while (radix < 10)
	{
		if (*temp < 58 && *temp > 47)
			{	
				result = result * radix + (REPCON_ATOI(*temp));
				++temp;
			}
		else
		{
			return (result * neg_flag);
		}
	}
	return (result * neg_flag);
}
/* test function */
int TestFunc(void)
{
	char str[] = {"abcdefg"}, str2[] = {"atyegjsedu"}, str3[] = {"adf"};
	char buffer[100], buffer2[100], buffer3[100];
	sprintf(buffer3, "%d", 0);
	/*all good 
	printf("Atoi local function: %d\n  original function: %d\n", Atoi(str), atoi(str));*/
	/*all good 
	printf("Atoi36 local function: %d\n    original function: 0\n", Atoi36(str2, 8));*/
	/*all good 
	printf("Itoa local function: %s\n  original function: %s\n", ItoA(0, buffer, 10), buffer3);*/
	/*all good
	printf("Itoa36 local function: %s\n    original function: 24\n", ItoA36(20, buffer2, 8));*/
	
	InTwoOutOfThree(str, str2, str3);
	IsLittleEndian();
	IS_LITTLE_ENDIAN();
	return 0;
}

/* #############################*/
/* # Ex.2                      #*/
/* # status: approved          #*/
/* # reviewer: Adi             #*/
/* # description: this func    #*/
/* # will print conjunction of #*/
/* # two arrays with           #*/
/* # disconjunction with a     #*/
/* # third array               #*/
/* # return: letters only      #*/
/* # appearing int two arrays  #*/
/* # and not in third array    #*/
/* # special notes:            #*/
/* #############################*/
void InTwoOutOfThree(char *arr1,char *arr2, char *arr3)
{
	char ascii[255] = { 0 };
	while ('\0' != *arr1)
	{
		ascii[*arr1] = 1;
		++arr1;
	}
	while ('\0' != *arr3)
	{
		ascii[*arr3] = 0;
		++arr3;
	}
	while ('\0' != *arr2)
	{
		if (ascii[*arr2] == 1)
		{
			printf("%c", *arr2);
			
		}
		++arr2;
	}
	printf("\n");
	
}
/* #############################*/
/* # Ex.3                      #*/
/* # status: approved          #*/
/* # reviewer: Adi             #*/
/* # description: this func    #*/
/* # will detect if the system #*/
/* # is big or small endian    #*/
/* # return: void              #*/
/* # special notes:            #*/
/* #############################*/
void IsLittleEndian(void)
{
	char n[] = "12";
	printf((&n[0] > &n[1]) ? "big endian\n" : "little endian\n");
}
	
	


