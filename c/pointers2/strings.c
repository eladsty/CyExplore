#include <stddef.h>
#include <assert.h>
#include "Strings.h"
#include <stdlib.h>

size_t Strlen(const char *str)
{
	const char *stre_p = str;
	 
	while (*str != '\0')
		{
			++str;
		}
	
	return (str - stre_p);
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
		*cpy = *str;
		++cpy;
 		++str;
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
    
	while (*str1 == *str2 && n > 0 && *str1 != '\0')
	{
		if(*str1 != *str2)
		{
			return (*str1 - *str2);
		}
		++str1;
		++str2;
		--n;
	}
     
        return  0;
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
	
	char *cpy = NULL;
	assert(NULL != str);
	cpy = (char*)malloc(Strlen(str)+1);
	
	StrCpy(cpy, str);
	
	return cpy;
}

  
char *Strcat(char *destination, const char *source)
{
	char *dest_begin_p = destination; 
	
	while(*destination != '\0')
	{
		++destination;
	}
 
	while(*source != '\0')
	{
		*destination = *source;
		++source;
		++destination;
	}
	
	*destination = '\0';

	return dest_begin_p;
}
 
char *Strncat(char *destination, const char *source, size_t n)
{
	char *dest_begin_p = destination; 
	assert(NULL != destination && NULL != source);
	
	while(*destination != '\0')
	{
		++destination;
	}
 
	
	while(n > 0 && *source != '\0')
	{
		*destination = *source;
		++source;
		++destination;
		--n;
	}
	
	*destination = '\0';
	
	return dest_begin_p;
}


char *StrStr(const char* kw, const char* str)
{	
	size_t kw_len = Strlen(kw);
	assert(NULL != kw && NULL != str);
		
	while(*str != '\0')
	{
		if(*kw==*str)
		{
			if (0 == StrnCmp(kw, str, kw_len))
			{
				return (char *)str;
			}
		}
		
		++str;
	}
	
	return NULL;
}


size_t StrSpn(const char *str1, const char *str2)
{
	size_t cnt = 0;
	const char *p_start = str2;
	
	assert(NULL != str1 && NULL != str2);
			
	while('\0' != *str1)
	{
		while('\0' != *str2)
		{
			if(*str1 == *str2)
			{
				cnt++;
				break;		
			} 
			else
			{
				if('\0' == *(str2+1))
				{
					return cnt;
				}
			}
			++str2;
		}
		
		str2 = p_start;
		++str1;		
	}

	return cnt;
}

 int IsPalindrome(const char *str)
 {
 	const char *p_end_str =  (str + Strlen(str)-1);
 	 
 	assert(NULL != str);
 		
 	while(0 <= (p_end_str-str))
 	{
 		if( ToLower(*str) != ToLower(*p_end_str))
 		{
 			return 0;
 		}

 		++str;
 		--p_end_str;
 	} 
 	
 	return 1;
 }




























