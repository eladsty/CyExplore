#include <stdio.h>
/* globals */
size_t ascii[125] = {0};
size_t max = 0;
/* func declaration */
void OneMillionChars(char c);


int main()
{
	char c[] = {'a', 'b', 'a', 'r', '0', 'a', 'b', 'a', 'r', '0'};
	int i = 0;
	for ( ; i < 10; ++i)
	{
		OneMillionChars(c[i]);
	}

	return 0;
}





void OneMillionChars(char c)
{
	int i = 0;
	ascii[c] +=1;
	if (('0' != c) && (ascii[c] > max))
	{
		max = ascii[c];
	}
	else if ('0' == c)
	{
		printf("%ld\n", max);
		max = 0;
		for (i = 0; i < 125; ++i)
		{
			ascii[i] = 0;
		}
	}
}
