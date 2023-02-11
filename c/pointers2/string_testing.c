#include <stdio.h>
#include <assert.h>
#include <stddef.h>
#include "Strings.h"
#include <stdlib.h> 
 /* libraries below to */
#include <string.h>
 
 
int main()
{
		char *pali1 = "";
		char *pali2 = "";
		char pldrm[5][10] = {"goog","tartar","a010A","12321",""};
		char *word = "fox";
	  	char *sentence = "a brown fox jumped over the fence\n";
	  	char *string = "2455gerwabc43wg";
	  	char *digits = "09876454321";
	  	char *letters = "abfh";
       const char testCase[5][10] = {"","a","lower","MiXed","CAPITALS"};
 		int i = 0; 
		char *p_Strdup = Strdup(testCase[4]);  
	 	char s[] = "system";
		char od[] = "of a down";
 		char *p1 = StrStr("ver",sentence);
 		
 		for(;i<5;i++)
 		{
 			printf("%d\n", IsPalindrome(pldrm[i]));  
 		}
 		
 		i=0;
 		
 		assert(strspn(string,digits) == StrSpn(string,digits));  
 		printf("%ld\n",StrSpn(string,digits));
 		
 		
		printf("%s", p1);
 		
 		Strcat(s,od);
 		
	 	for(;i<5;i++)
	 	{
	 		Strncat(s,testCase[i],2);
	 		printf("%s\n", s);
	 	}

 
	
	printf("this is Strdup: %s\n", p_Strdup);


	 free(p_Strdup); 
	
	return 0;
}
