#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void sig2_handler(int signum)
{
	write(STDOUT_FILENO, "ping\n", 5);
}

void test(void)
{
	int x = 5;
	++x;
}

int main(int argc, char *argv[])
{
	pid_t pid = 0;
	int wstatus = 0;
	int i = 0;
	struct sigaction sa;
	sigset_t old_mask ,empty_mask;
	sigemptyset(&sa.sa_mask);
	sigemptyset(&empty_mask);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigprocmask(SIG_SETMASK, &sa.sa_mask, &old_mask);
	
	while(i < 10)
	{
		pid = fork();
		if(pid == 0)
		{
		    	execv("./exec.out" ,argv);
		}
		else
		{
		    	sa.sa_handler = sig2_handler;
		    	sa.sa_flags = 0;
			sigaction(SIGUSR2,&sa,NULL);
			/*sigdelset(&sa.sa_mask, SIGUSR2);*/
			/*sigprocmask(SIG_SETMASK, &sa.sa_mask, &old_mask);*/
			sigsuspend(&empty_mask);
			test();
			kill(pid ,SIGUSR1);
			/*printf("From father%d\n" ,getpid());*/
			wait(&wstatus);
		}
		++i;
	}	
	return 0;
}

/*int main(int argc, char *argv[])
{
	pid_t pid = 0;
	int wstatus = 0;
	int i = 0;
	struct sigaction new_action, old_action;
	sigset_t old_mask;
	sigemptyset(&old_mask);
	sigemptyset(&new_action.sa_mask);
	sigprocmask(SIG_SETMASK, &new_action.sa_mask, &old_mask);
	
	pid = fork();
	if(pid == 0)
	{
	    	execv("./exec.out" ,argv);
	}
	else
	{

	    	new_action.sa_handler = sig2_handler;
	    	new_action.sa_flags = 0;
		sigaction(SIGUSR2,&new_action,NULL);
		sleep(1);
		kill(pid ,SIGUSR1);
		sigsuspend(&old_mask);
		printf("From father%d\n" ,getpid());
		wait(&wstatus);
	}
	return 0;
}*/


/*int main(int argc, char *argv[])
{
	pid_t pid = 0;
	int wstatus = 0;
	int i = 0;
	struct sigaction new_action, old_action;
	sigset_t old_mask;
	sigemptyset(&old_mask);
	sigemptyset(&new_action.sa_mask);
	sigaddset(&new_action.sa_mask, SIGUSR1);
	sigprocmask(SIG_SETMASK, &new_action.sa_mask, &old_mask);
	
	pid = fork();
	if(pid == 0)
	{
	    	execv("./exec.out" ,argv);
	}
	else
	{

	    	new_action.sa_handler = sig2_handler;
	    	new_action.sa_flags = 0;
		sigaction(SIGUSR2,&new_action,NULL);
		kill(pid ,SIGUSR1);
		sigsuspend(&new_action.sa_mask);
		printf("From father%d\n" ,getpid());
		wait(&wstatus);
	}
	return 0;
}*/

