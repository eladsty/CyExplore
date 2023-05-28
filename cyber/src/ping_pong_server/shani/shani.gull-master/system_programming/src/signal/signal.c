#define _POSIX_C_SOURCE 199309L

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h> /* wait */

#include "../../include/signal/signal.h"


static volatile pid_t signaling = 0;

void new_handler2(int signum, siginfo_t *info, void *n)
{
	char *print = "Recived SIGUSR2\n";
	size_t len = strlen(print);
	write(STDOUT_FILENO, print, len);
	signaling = info->si_pid;
}


/* Status : approved
 * Reviewer : Adi
 * Description : implement process spawning using fork and exec function
 * Arguments : string as a command line argument
 * Return : void
 * Time Complexity : O(1)
 * Space Complexity : O(1)
 */
void ForkExecShell(char *command)
{
	pid_t child;
	int i = 0;
	char *command_line_args[256] = {NULL};
	int child_status;	
	struct sigaction new_handler_sigusr2;
	new_handler_sigusr2.sa_sigaction = new_handler2;

	if (sigaction(SIGUSR2, &new_handler_sigusr2, NULL) < 0)
	{
		perror("sigaction");
	}

	
	if (0 > (child = fork()))
	{
		perror("fork");
	}
	if (0 == child)
	{
		/* this is child process. */
		child_status = execvp(command, command_line_args);
		perror("an error occured: ");
		exit(-1);
	}
	else
	{
		/* this is parent */
		for (i = 0; i < 3; ++i)
		{
			sleep(1);
			kill(child, SIGUSR1);
			pause();
		}		
	}
	wait(&child_status);
	return;
}

void SystemShell(char *command)
{
	int ret;
	int i = 0;
	char parent_pid[64];
	char command_line[255];
	pid_t parent = getpid();
	struct sigaction new_handler_sigusr2;
	new_handler_sigusr2.sa_sigaction = new_handler2;
	new_handler_sigusr2.sa_flags = SA_SIGINFO;

	if (sigaction(SIGUSR2, &new_handler_sigusr2, NULL) < 0)
		{
			perror("sigaction");
		}	
	

	sprintf(parent_pid, " %d &", parent);
	strcat(command_line, command);
	strcat(command_line, parent_pid);
	ret = system(command_line);
	if (127 == ret || -1 == ret)
	{
		perror("error occured: ");
	}
	for (i = 0; i < 3; ++i)
	{
		pause();
		kill(signaling, SIGUSR1);
	}

}

