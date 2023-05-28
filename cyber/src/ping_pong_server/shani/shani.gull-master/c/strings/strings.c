#include "strings.h"
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>


/* reviewed by Adi */
int StrCmp(const char *arr1, const char *arr2)
{
	
	assert (arr1);
	assert (arr2);
	while (*arr1 == *arr2 && (*arr1 != '\0' && *arr2 != '\0'))
	{
		++arr1;
		++arr2;
	}
	return (*arr1 - *arr2);
}
int strcmptest(const char *arr1, const char *arr2)
{
	if (arr1 == NULL || arr2 == NULL)
	{
		return 0;
	}
	while (*arr1 == *arr2 && (*arr1 != '\0' && *arr2 != '\0'))
	{
		++arr1;
		++arr2;
	}
	return (*arr1 - *arr2);
}

size_t StrLen(const char *arr)
{
	const char *start_value = arr;
	assert (arr);
	while (*arr != '\0')
	{
		arr++;
	}
	return (arr - start_value);
}
char *StrCpy(char *dest, const char *origin)
{
	char *start_point = dest;
	assert(origin);
	while (*origin != '\0')
	{
		*dest = *origin;
		++origin;
		++dest;
	}
	*(dest + 1) = '\0';
	return start_point;
	
}
char *StrnCpy(char *dest, const char *origin, size_t n)
{
	char *start_point = dest;
	assert(origin);
	assert(dest);
	while ( n > 0 && *origin != '\0')
	{
		*dest = *origin;
		++dest;
		++origin;
		--n;
	}
	while (n > 0)
	{
		*dest = '\0';
		++dest;
		n--;
	}
	return start_point;
}

int ToLower(char c)
{
	return ((c <= 'Z' && c >= 'A') ? (c + 32): c);
}
int StrCaseCmp(const char *arr1, const char *arr2)
{
	assert (arr1);
	assert (arr2);
	while ((ToLower(*arr1) == ToLower(*arr2)) && '\0' != *arr1)
	{
		++arr1;
		++arr2;
	}
	return (ToLower(*arr1) - ToLower(*arr2));
}
/* reviewed by Amir*/
int StrnCmp(const char *arr1, const char *arr2, size_t n)
{
	assert(arr1);
	assert(arr2);
	while (*arr1 == *arr2 && (*arr1 != '\0' || *arr2 != '\0') && n > 0)
	{
		++arr1;
		++arr2;
		--n;
	}
	return (*arr1 - *arr2);
}
char *StrChr(const char *arr, int c)
{
	assert(arr);
	while ( *arr != c && '\0' != *arr)
	{
		++arr;
	}
	if ('\0' == *arr)
	{
		return NULL;
	}
	else
	{
		return (char*)arr;
	}
}
char *StrDup(const char *arr)
{ 
	char *new_array = (char*)malloc((StrLen(arr))+1);
	char *start_new_array = new_array;
	assert(arr);
	while (*arr != '\0')
	{
		*new_array = *arr;
		++new_array;
		++arr;
	}
	*new_array = '\0';
	return start_new_array;
}
char *StrCat(char *dest, const char *origin)
{
	char *temp_ptr = dest + (StrLen(dest));
	assert(dest);
	assert(origin);
	while (*origin != '\0')
	{
		*temp_ptr = *origin;
		++temp_ptr;
		++origin;
	}
	*temp_ptr = '\0';
	return dest;
}
char *StrnCat(char *dest, const char *origin, size_t n)
{
	char *temp_ptr = dest + (StrLen(dest));
	assert(dest);
	assert(origin);
	while (*origin != '\0' && n > 0)
	{
		*temp_ptr = *origin;
		++temp_ptr;
		++origin;
		--n;
	}
	temp_ptr = '\0';
	return dest;
}
char *StrStr(const char *haystack, const char *needle)
{
	size_t n = StrLen(needle);
	assert(haystack);
	assert(needle);
	while (StrChr(haystack, *needle))
	{
			haystack = StrChr(haystack, *needle);
			if ((StrnCmp(haystack, needle, n)) == 0)
			{
				return (char*)haystack;
			}
			++haystack;
	}
	return NULL;		
}
size_t StrSpn(const char *s, const char *accept)
{
	size_t counter = 0;
	assert (accept);
	assert (s);
	if ('\0' == *accept || '\0' == *s)
	{
		return 0;
	}
	while (StrChr(accept, *s))
	{
		++counter;
		++s;
	}
	return counter;
}
int IsPalindrome(char *str)
{
	char *compare = str;
	while (*compare != '\0')
	{
		compare++;
	}
	--compare;
	while (*str == *compare && str < compare)
	{

		++str;
		--compare;
	}
	return ((*compare == *str) ? 1 : 0);
}
