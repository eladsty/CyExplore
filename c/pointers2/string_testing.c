#include <stdio.h>
#include <assert.h>
#include <stddef.h>
#include "Strings.h"
#include <stdlib.h> 


int main()
{

	const char *str = "abcde";
	char *cpy = malloc(6);
	StrCpy(cpy, str);
	printf("%c", *cpy);
	free(cpy);
return 0;
}
