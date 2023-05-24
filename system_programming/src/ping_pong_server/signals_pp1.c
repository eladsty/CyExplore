#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

volatile sig_atomic_t sig1 = 0;
volatile sig_atomic_t sig2 = 0;
char *msg1 = "FROM PARENT\n";
char *msg2 = "FROM CHILD\n";

void sig1_handler(int signum)
{
	write(STDOUT_FILENO, "FROM PARENT\n", strlen(msg1));
	/*kill(pid, SIGUSR2);*/
}

void sig2_handler(int signum)
{
	write(STDOUT_FILENO, "FROM CHILD\n", strlen(msg2));
	/*kill(getppid(), SIGUSR1);*/
}

int main(void)
{
	
	pid_t pid = 0;
	int status = 0;
	int i = 100;
	pid = fork();
	if(pid == 0)
	{
		while(i)
		{
			raise(SIGSTOP);
			printf("child %d\n" ,i);
			--i;
		}
		/*signal(SIGUSR2,sig2_handler);
		kill(getppid(), SIGUSR1);*/
		
	}
	else if(pid > 0)
	{
		while(i)
		{

			waitpid(pid, NULL, WUNTRACED);
			printf("father%d\n" ,i);
		/*signal(SIGUSR1,sig1_handler);*/
			kill(pid, SIGCONT);
			--i;
		}
		/*wait(&status);*/
	}
	return 0;
}


