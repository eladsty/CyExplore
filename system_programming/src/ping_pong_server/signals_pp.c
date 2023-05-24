#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

volatile sig_atomic_t sig1 = 0;
volatile sig_atomic_t sig2 = 0;

void sig1_handler(int signum)
{
	write(STDOUT_FILENO, "pong\n", 5);
	/*kill(getppid(), SIGUSR2);*/
	/*raise(SIGSTOP);*/
}

void sig2_handler(int signum)
{
	write(STDOUT_FILENO, "ping\n", 5);
	/*raise(SIGSTOP);
	kill(getppid(), SIGCONT);*/
}

int main(void)
{
	pid_t pid = 0;
	int status = 0;
	int i = 0;
	struct sigaction new_action, old_action;
	
	pid = fork();
	if(pid == 0)
	{

    		/*Set the handler in the new_action struct*/
	    	new_action.sa_handler = sig1_handler;
	    	/*Set to empty the sa_mask. It means that no signal is blocked
	    	while the handler run.*/
	    	sigemptyset(&new_action.sa_mask);
	    	/*Block the SEGTERM signal.
	    	It means that while the handler run, the SIGTERM signal is ignored
	    	sigaddset(&new_action.sa_mask, SIGTERM);
	    	Remove any flag from sa_flag. See documentation for flags allowed*/
	    	new_action.sa_flags = 0;

		/*Replace the signal handler of SIGINT with the one described by new_action*/
		sigaction(SIGUSR1,&new_action,NULL);
		kill(getppid() ,SIGUSR2);
		pause();
	}
	else
	{

    		/*Set the handler in the new_action struct*/
	    	new_action.sa_handler = sig2_handler;
	    	/*Set to empty the sa_mask. It means that no signal is blocked
	    	while the handler run.*/
	    	sigemptyset(&new_action.sa_mask);
	    	/*Block the SEGTERM signal.
	    	It means that while the handler run, the SIGTERM signal is ignored
	    	sigaddset(&new_action.sa_mask, SIGTERM);
	    	Remove any flag from sa_flag. See documentation for flags allowed*/
	    	new_action.sa_flags = 0;

		/*Replace the signal handler of SIGINT with the one described by new_action*/
		sigaction(SIGUSR2,&new_action,NULL);
		waitpid(pid, NULL, WUNTRACED);
		kill(pid ,SIGUSR1);
		wait(&status);
	}
	return 0;
}
