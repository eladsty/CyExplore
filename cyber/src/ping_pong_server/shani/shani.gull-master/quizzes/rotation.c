#include <string.h>
#include <stdio.h>
#include <assert.h>
int Rotation(char *s1, char *s2);

int main()
{
	char s1[] = {"121234"}, s2[] = {"123412"};
	printf("%d\n", Rotation(s1, s2));
	return 0;
}

int Rotation(char *s1, char *s2)
{
	char *s2_start = s2, *s1_start = s1;
	s2 = strchr(s2, *s1);
	
	while (*s1 != '\0')
	{
		assert(s2);
		if ('\0' == *s2)
		{
			s2 = s2_start;
		}
		else if (*s1 != *s2)
		{
			s2 = strchr(s2, *s1_start);
		}
		++s1, ++s2;
	}
	return 1;
}
