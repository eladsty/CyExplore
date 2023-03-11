#include <stdio.h>
#include <string.h>


void ReverseString(char *str )
{
	size_t len = strlen(str);
	size_t i = 0, j = 0, len = 0, startIndex = 0, endIndex = 0;
	char temp_word[100];
 
  	len = strlen(str);
  	endIndex = len - 1;
  	
  	for(i = len - 1; i >= 0; i--)
	{

	}		 
}
 
int main()
{
    char string[] = "This string is not reversed.";
	printf("%s\n",string);
    ReverseString(string);
	printf("after reverseing: %s\n",string);
    return 0;
}

/*
	map each word, each word end when encountering a space.
	copy each 50-100 character from the string to avoid overriding existing words in 						the original string.
	now, starting from end of string, find the starting_point of the last word.
	and copy it until encountering " " or ".", 
 "This" "string" "is" "not" "reversed"."
 "is not reversed This string  ."

*/
