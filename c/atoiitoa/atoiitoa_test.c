 

#include <string.h>/*str cmp*/
#include <stdio.h> /*printf*/

#include "atoiitoa.h"
 
int main()
{
	char buffer[5] = {0};
	int i = 0;
 	char *strings[] = {"-1424","14-24","0","99","","53a22"};  
 
 	printf("%s\n",  Itoa(312, buffer, 10));
 	printf("%s\n",  Itoa(-144, buffer, 10));
 	
 	printf("%d\n", Atoi("124"));
 	printf("%d\n", Atoi("-141"));
 	printf("%d\n", Atoi("1tg24"));
 	
 	printf("%s\n",  Itoa(35, buffer, 36));
 	printf("%s\n",  Itoa(24, buffer, 16));
 	 

	printf("1c in base 36 is 48: %d \n",Atoi36("1C", 36));  
	printf(" Atoi36 %d \n",Atoi36("B-B", 16)); 
	printf(" Atoi36 %d \n",Atoi36("-B", 16));     
	printf("Atoi36  %d \n",Atoi36("80", 10));   
	printf("Atoi36  %d \n",Atoi36("1030", 2));   
  	
  	for(;i<6; i++) 
  	{ 
	assert(1 == AtoiVsAtoi(strings[i]));
	}
	
	assert(1 == TestAtoi());
	
 	return 0;
}
