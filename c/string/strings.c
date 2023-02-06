
#include <stddef.h>
#include <assert.h>


size_t Strlen(const char *str)
{
	const char *stre_p = NULL;
	assert(str != NULL);
	 
	for (stre_p = str; *stre_p != '\0'; ++stre_p){}
	
	return stre_p - str;
}




 int Strcmp(const char *str1, const char *str2)
{

	assert(str1 != NULL);
    assert(str2 != NULL);
	
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
