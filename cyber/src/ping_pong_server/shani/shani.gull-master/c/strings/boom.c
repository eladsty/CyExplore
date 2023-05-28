#include <stdio.h>
int SevenBoom(int from, int to);


int main()
{
	SevenBoom(-1, 1);
	return 0;
}


int SevenBoom(int from, int to)
{
	int i, i_remainder, i_no_remainder;
	for (i = from; i <= to; i++)
	{
		if (i == 0)
		{
			printf("%d\n", i);
			continue;
		}
		if (!(i % 7))
		{
			printf("BOOM\n");
			continue;
		}
		i_no_remainder = i;
		i_remainder = (i_no_remainder % 10);
		while (i_no_remainder != 0 || i_remainder != 0)
		{
			if (i_remainder == 7 || i_remainder == (-7))
			{
				printf("BOOM\n");
				break;
			}
			if (i_remainder != 0 || i_no_remainder != 0)
			{
				i_no_remainder /= 10;
				i_remainder = (i_no_remainder % 10);
			}
		}
		if (i_no_remainder == 0 && i_remainder == 0)
		{
			printf("%d\n", i);
		}
	}
	return 0;
}
