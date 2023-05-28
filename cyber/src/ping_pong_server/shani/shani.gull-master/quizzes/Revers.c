#include <stdio.h>
#include <ctype.h> /* tolower */
#include <string.h> /* strlen */
void Reverse(char *str);

int main()
{
	char i[] = "Well Hello";
	Reverse(i);
	printf("%s\n", i);
	return 0;
}

void Reverse(char *str)
{
	char *end = str + strlen(str) - 1, tmp = '\0';
	
	while (end > str)
	{
		tmp = tolower(*str);
		*str = tolower(*end);
		*end = tmp;
		--end;
		++str;
	}
	*end = tolower(*end);
}
	

