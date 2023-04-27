#include <unistd.h>/*sleep*/
#include <stdlib.h>/*exit*/
#include <stdio.h> /* printf*/

 

int main()
{
 
	int i = 1;
 
	while(i <= 5)
	{
	  printf("this will last for 5 sec: %d \n", i);
	  sleep(1);
	  ++i;
	}
 
	exit(1);
	return 0;
}
