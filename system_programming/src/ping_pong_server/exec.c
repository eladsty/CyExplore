#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void sig1_handler(int signum)
{
	write(STDOUT_FILENO, "pong\n", 5);
	/*kill(getppid(), SIGUSR2);*/
	/*raise(SIGSTOP);*/
}

int main(int argc, char *argv[])
{
	struct sigaction sa;
	sigset_t old_mask;
	sa.sa_handler = sig1_handler;
	sa.sa_flags = 0;
	sigaction(SIGUSR1,&sa,NULL);
	sigemptyset(&sa.sa_mask);
	sigprocmask(SIG_SETMASK, &sa.sa_mask, &old_mask);
	kill(getppid() ,SIGUSR2);
	sigsuspend(&sa.sa_mask);
	/*printf("From child%d\n" ,getpid());*/
	return 0;
}

/*int main(int argc, char *argv[])
{
	struct sigaction new_action, old_action;
	sigset_t mask;
    	new_action.sa_handler = sig1_handler;
	new_action.sa_flags = 0;
	sigaction(SIGUSR1,&new_action,NULL);
	sigemptyset(&mask);
	sigsuspend(&mask);
	printf("From child%d\n" ,getpid());
	kill(getppid() ,SIGUSR2);
	return 0;
}*/


/*
	struct sigaction new_action, old_action;
	sigset_t old_mask;
    	new_action.sa_handler = sig1_handler;
	new_action.sa_flags = 0;
	sigaction(SIGUSR1,&new_action,NULL);
	sigdelset(&new_action.sa_mask, SIGUSR1);
	sigprocmask(SIG_SETMASK, &new_action.sa_mask, &old_mask);
	printf("From child%d\n" ,getpid());
	kill(getppid() ,SIGUSR2);
*/
