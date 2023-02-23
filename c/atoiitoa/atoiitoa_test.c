 

#include <string.h>/*str cmp*/
#include <stdio.h> /*printf*/

#include "atoiitoa.h"
 
int main()
{
	char buffer[5] = {0};
	int i = 0;
 	char *strings[] = {"-1424","14-24","0","99","","53a22"}; 
 	 
 	char *arr1[] = {"heeelllo lords","filter","123456","123456"};
 	char *arr2[] = {"hallo world","filter","123456",""};
 	char *arr3[] = {"hahaha","filter","23456","123456"};
 	
 	
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
	i = 0;
 
	for(;i<4;++i)
	{
		InTwoOutOfThree(arr1[i], arr2[i], arr3[i]);
	}
 
	
	
	InTwoOutOfThree("abc","bcd","dfg");
 	return 0;
}
