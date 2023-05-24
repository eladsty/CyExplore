#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>


void sig_handler(int signum)
{
	write(STDOUT_FILENO, "pong\n", 5);
}

int main(int argc, char *argv[])
{
	struct sigaction sa;
	sigset_t empty_mask ,old_mask;
	int i = 0;
	sigemptyset(&empty_mask);
	sigemptyset(&sa.sa_mask);
    	sa.sa_handler = sig_handler;
	sa.sa_flags = 0;
	sigaction(SIGUSR2,&sa,NULL);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigprocmask(SIG_SETMASK, &sa.sa_mask, &old_mask);
	while(i < 10)
	{	
		kill(atoi(argv[1]),SIGUSR1);
		sigsuspend(&empty_mask);
		++i;	
	}	
	return 0;
}
