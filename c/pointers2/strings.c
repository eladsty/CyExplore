#include <stddef.h>
#include <assert.h>
#include "Strings.h"
#include <stdlib.h>

size_t Strlen(const char *str)
{
	const char *stre_p = NULL;
	assert(str != NULL);
	 
	for (stre_p = str; *stre_p != '\0'; ++stre_p){};
	
	return stre_p - str;
}




 int StrCmp(const char *str1, const char *str2)
{

	assert(str1 != NULL && str2 != NULL);
	
	while ((*str1 && *str2) && (*str1 == *str2))
	
	{
		str1++;
		str2++;
	}
	
	if(*str1 > *str2)
		{
			return 1;
		}
		
	if (*str1 < *str2)
		{
			return -1;
		} 
	
	else
	{
	return 0;
	}
}



/*Nimrod*/
char *StrCpy(char *cpy, const char *str)
{
	char *cpyStart = cpy;
	


	while (*str != '\0')
	{
		*++cpy = *++str;
	}
		
		*cpy = '\0';
	
	return cpyStart;
}

/* ran */
char *StrnCpy(char *cpy, const char *src , size_t n)
{
	char *cpy_start = cpy;

	assert(NULL != cpy && NULL != src);
	
	while (*src != '\0' && n > 0)
	{
		*cpy = *src;
		--n;
		++src;
	 	++cpy;
	}
	
	while (n > 0)
	{
		*cpy = '\0';
		++cpy;
		--n;
	}

	return cpy_start;
}

 /* ran */
int StrnCmp(const char *str1, const char *str2, size_t n) 
{
	assert(NULL != str1);
	assert(NULL != str2);
	
	if ( n == 0 )
    {
        return 0;
    }
    
	while (*str1 == *str2 && n>0 && *str1 != '\0')
	{
		++str1;
		++str2;
		--n;
	}
     
        return  (*str1-*str2);
}


char ToLower(char l)
{
	return ((l >= 'A' && l <= 'Z') ? l+32 : l);
}
 
 
 /* */
int Strcasecmp (const char *str1, const char *str2)
{
	assert(NULL != str1 && NULL != str2);
	
	while (ToLower(*str1) == ToLower(*str2) && '\0' != *str1 && '\0' != *str2)
 	{
 		++str1;
		++str2;
 	}
	
	return ToLower(*str1) - ToLower(*str2);
}

 
char *Strchr(const char *str, int n)
{
	char *p = (char *) str;
	assert(NULL != str);
	
	while(*p != '\0')
		{
			if(*p == n)
			{
				return p;
			}
			++p;
		}
	 
	return '\0';
}



char *Strdup(const char *str)
{
	int diff = (int)Strlen(str);
	char *cpy = malloc(diff+1);
	char *cpy_step = cpy;
	
	assert(NULL != str);
	
	while (*str != '\0')
	{
		*cpy_step = *str;
		++str;
		++cpy_step;
	}
	
	*cpy = '\0';
	
	return cpy;
}





