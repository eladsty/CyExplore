#include <unistd.h>/*sleep*/
#include <stdlib.h>/*exit*/
#include <stdio.h> /* printf*/

 

int main()
{
	char buffer[100] = {0};
	fgets(buffer, 100, stdin);
	
	printf("this will last for 5 sec: %s \n",buffer);
	
	sleep(5);
	exit(1);
	return 0;
}
