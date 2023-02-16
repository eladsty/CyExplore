
#include <stddef.h>
#include <assert.h>
#include <stdio.h>
#include "strings.h"
#include "strings.h"
int main()
{
	const char *str = "abde";
	const char *str1 = "abdf";

	const char *str2 = "abcd";
	const char *str3 = "abcd";

	const char *str4 = "abcf";
	const char *str5 = "abce";


 	assert(-1 == Strcmp(str,str1));
 	assert( 0 == Strcmp(str2,str3));
	assert( 1 == Strcmp(str4,str5));
 	printf("%d\n",Strcmp(str,str1));
	return 0;
}
