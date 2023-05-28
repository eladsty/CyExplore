#define _GNU_SOURCE /* in order to include memrchr, 
						else it will be implicitly called and will not work */
#include <string.h>
#include <stdio.h>
char *ReverseWords(char *str, char *reverse);

int main()
{
	char str[100] = {"i am a student"};
	char reverse[100];
	ReverseWords(str, reverse);
	printf("%s\n", reverse);
	return 0;
}

char *ReverseWords(char *str, char *reverse)
{
	char *buffer = NULL;
	int count = strlen(str);
	
	while (buffer = (char *)(memrchr(str, ' ', count)))
	{
		count -= strlen(buffer);
		*buffer = '\0';
		++buffer;
		strcpy(reverse, buffer);
		*(reverse + strlen(buffer)) = ' ';
		reverse += strlen(buffer) + 1;
	}
	*reverse = '\0';
	strcat(reverse, str);
	
	return reverse;
}


