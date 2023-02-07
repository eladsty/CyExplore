#include <stddef.h>
#include <assert.h>
#include "Strings.h"

char *StrCpy(char *cpy, const char *str)
{
	char *cpyStart = cpy;
	
	assert(NULL != cpy);
	assert(NULL != str);

	while (*str != '\0')
		{
			*cpy = *str;
			++cpy;
			++str;
		}
		
		*++cpy = '\0';
	
	return cpyStart;
}



