#include <stdio.h>
void TF(int num);

int main()
{
	TF(10);
	return 0;
}

void TF(int num)
{
	int i = 1;
	for( ; i <= num; i++)
	{
		if (!(i%3))
		{
			if (!(i%5))
			{
				printf("TF\n");
			}
			else
			{
				printf("T\n");
			}
		}
		else if (!(i%5) && (i%3))
		{
			printf("F\n");
		}
		else
		{
			printf("%d\n", i);
		}
	}
}
