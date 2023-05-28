#define _POSIX_SOURCE 500
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char *argv[], char *envp[])
{
	pid_t i = getpid();
	sleep(1);
	printf("1\n");
	sleep(1);
	printf("2\n");
	sleep(1);
	printf("3\n");
	sleep(1);
	printf("4\n");
	sleep(1);
	printf("5\n");
	system("ps");
	kill(0, SIGKILL);
	return 0;
}