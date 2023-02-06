#include <stdio.h>
#include <stdlib.h>


int main()
{
	char *arr = malloc(4);
	if(*arr)
	{
		printf("value of arr: %c", *arr);
	} 
	else
	{
		printf("memory not existed %c", (*arr)+1);
	}

								

	return 0;
}

/*
	int arr[10]={0,1,2,3,4,5,6,7,8,9};
	1. malloc(20); or int *p = (int*)malloc(20); do I get allocated with no l-value?
 	2. int arr[10];
	3. read the 11 value , try to write to 11 value by GDB,try not to use printf
gedit main.c &
 vlg ./main.out
gd -g main.c -o main.out
gdb -tui ./main.out

*/
