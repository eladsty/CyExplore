#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

sig_atomic_t sender_pid = 0;

void sig_handler(int signum ,siginfo_t *info, void *context)
{
	write(STDOUT_FILENO, "ping\n", 5);
	sender_pid = info->si_pid;
}

int main(void)
{
	struct sigaction sa;
	sigset_t empty_mask ,old_mask;
	int i = 0;
	sigemptyset(&empty_mask);
	sigemptyset(&sa.sa_mask);
    	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1,&sa,NULL);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigprocmask(SIG_SETMASK, &sa.sa_mask, &old_mask);	
	printf("%d\n" ,getpid());
	while(i < 10)
	{
		sigsuspend(&empty_mask);
		kill(sender_pid ,SIGUSR2);
		++i;
	}
	return 0;
}
