#include <string.h> /*strlen*/
#include <stdio.h>
/*
int StrCmpInRotation(char *str1, char *str2, int len)
{
	int i = 0;
	while('\0' != str1[i] && str2[i % len] == str1[i])
	{
		 ++i;
	}
	
	if('\0' == str1[i])
	{
		return 1;
	}
	
	return 0;
}
*/
int IsRotation(char *str1, char *str2)
{
	int len = strlen(str1); 
	int len2 = strlen(str2);
	int i = 0, int j = 0; 
	if(len != len2)
	{
		return 0;
	}

	while('\0' != str2[j])
	{
		if( str1[i] == str2[j])
		{
			 
		}
		++j;
	}	
	
	 
	return 0;
}

int main()
{
	char *arr_match[] = {"abcde","deabc","cdeab","cdeab","cdeab" };
	char *arr_no_match[] = {"", "abcde","deabc","cdeab","deacbd" };
	int i = 0;
	
	printf("should be 1: %d",IsRotation("abcde","deabc"));  
	/*
	for(i = 0;i < 4 ; ++i)
	{
		printf("should be 1: %d\n",IsRotation(arr_match[i],arr_match[i+1]));
	}
	for(i = 0;i < 4 ; ++i)
	{
		printf("should be 0: %d\n",IsRotation(arr_no_match[i],arr_no_match[i+1]));
	}
	*/
	return 0;
}
