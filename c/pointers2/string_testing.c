#include <stdio.h>
#include <assert.h>
#include <stddef.h>
#include "Strings.h"

int main()
{

	char *str = "abcde";
	char *cpy = "";
	StrCpy(cpy, str);
	assert(*cpy == 'a');



return 0;
}
