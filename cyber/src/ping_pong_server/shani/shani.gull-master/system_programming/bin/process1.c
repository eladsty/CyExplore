#define _POSIX_SOURCE 500
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> /*atoi*/
/*typedef struct {
	int si_signo;
	int si_code;
	union sigval si_value;
	int si_errno;
	pid_t si_pid;
	uid_t si_uid;
	void *si_addr;
	int si_status;
	int si_band;
} siginfo_t;*/

void new_handler(int signum)
{
	char *print = "Recived SIGUSR1\n";
	size_t len = strlen(print);   
	write(STDOUT_FILENO, print, len);     
}


int main(int argc, char *argv[], char *envp[])
{
	struct sigaction new_handler_sigusr1;
	int i = 0;
	pid_t pid = -2;
	new_handler_sigusr1.sa_handler = &new_handler;
	if (sigaction(SIGUSR1, &new_handler_sigusr1, NULL) < 0)
	{
		perror("sigaction");
	}

	if (argv[1])
	{
		pid = atoi(argv[1]);
		printf("%d\n", pid);
		for (i = 0; i < 3; ++i)
		{
			sleep(1);
			kill(pid, SIGUSR2);
			pause();
		}

	}
	else
	{
		for (i = 0; i < 3; ++i)
		{
			pause();
			kill(getppid(), SIGUSR2);
		}
	}
	return 0;
}