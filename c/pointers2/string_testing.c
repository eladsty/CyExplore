#include <stdio.h>
#include <assert.h>
#include <stddef.h>
#include "Strings.h"
#include <stdlib.h> 
#include <string.h>
#include <strings.h>

int main()
{
	  

	 	char *s1 = "L";
		char *s2 = "elad";
		char *s3 = "ela";
		char *s4 = "elad";
		char *s5 = "elae";
		char *mixCase =  "VaniLLa CakE";
		char *mixCase1 = "VaniLla CakE";
		char *mixCase2 = "onlylower";
		char *mixCase3 = "onlylowerz";
		char *mixCase4 = "";
		char *mixCase5 = "a";
	 	char cpy1[20];
	    char src[10] = "abcde";		
	    char src2[10] = "nimrod";			 	
	    char src3[10] = "wefio";		
	
 	assert(strchr(s2, 'a') == Strchr(s2, 'a') );
  
	/*
	 
	assert(StrnCmp(s2, s3,3) == strncmp(s2, s3,3));
 	assert(StrnCmp(s2, s3,5) == strncmp(s2, s3,5));

	test strcasecmp  			
	
 */
 /* check if length is the same*/
 	

 
 	
 	
	assert(*strchr(s2, 'a') == *Strchr(s2, 'a') );

 

	printf("%c",*Strchr(s2, 'a'));
	assert(Strcasecmp(mixCase,mixCase1) == strcasecmp(mixCase,mixCase1));
	assert(Strcasecmp(mixCase2,mixCase3) == strcasecmp(mixCase2,mixCase3));
	
 
	
	
	
	printf("success");
 
	return 0;
}
