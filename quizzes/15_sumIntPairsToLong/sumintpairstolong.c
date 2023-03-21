#include <stddef.h>/*size_t*/
#include <stdio.h> /*printf*/ 

/*
summing 2 ints and turning them into single long int.
return pointer to long
aprroved by Shlomi.

*/

long *sumIntPairsToLong(int ints[], size_t numOfElements)
{
	 size_t i = 0;
	 while (i < numOfElements)
	 {
	 	*((long *)(ints + i)) = (long)(*(ints + i)) + (long)(*(ints + i + 1));
	 	i += 2;
	 }
	 
	 return (long *)ints;

}


int main()
{
	int i = 0;
	int ints[] = {1,6,456,-3,8,12};
	long *long_arr = NULL;  
	
	long_arr = sumIntPairsToLong(ints, 6);
	
	for (i = 0; i < 3; ++i)
	{
		printf("%ld\n", long_arr[i]);
	}
	
	
	return 0;
}

