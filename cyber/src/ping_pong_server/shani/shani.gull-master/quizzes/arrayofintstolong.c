#include <stdio.h>

long *SumIntPairsToLongs(int ints[], size_t numofelements)
{
	size_t i = 0;

	while (i < numofelements)
	{ 
		*(ints + i) = (long)ints[i] + (long)ints[i + 1];
		++i;
	}
	return (long *)ints;
}

int main()
{
	int arr[] = {1, 6, 456, -3, 8, 12};
	long *arr2;
	arr2 = SumIntPairsToLongs(arr, 6);
	printf("%ld %ld %ld \n)", arr2[0], arr2[1], arr2[2]);
	return 0;
}
