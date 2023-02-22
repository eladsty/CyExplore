#include <assert.h>
#include <string.h>/*str cmp*/
#include <stdio.h> /*printf*/

#include "atoiitoa.h"
 
main()
{
	char buffer[4] = {0};
 
 	printf("%s\n",  Itoa(312, buffer, 10));
 	printf("%s\n",  Itoa(-44, buffer, 10));
 
 	
 	
 	return 0;
}
