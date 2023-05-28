#include <stddef.h>
#include <stdio.h>
#include <string.h>

void Swap(char *x, char *y)
{
	char temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void Permutation(char *str, size_t left, size_t right)
{
	size_t i = 0;
	if (left == right)
	{
		printf("%s\n", str);
	}
	else
	{
		for (i = left; i <=right; ++i)
		{
			Swap((str + left), (str + i));
			Permutation(str, left + 1, right);
			Swap((str + left), (str + i));
		}
	}
	return;
}

int main()
{
	char str1[] = {"ABC"};
	char str2[] = {"ABC ABC"};
	size_t right = strlen(str1);
	Permutation(str1, 0, (right - 1));
	return 0;
}