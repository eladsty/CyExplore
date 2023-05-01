

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

 

static void SIGHandlerPing(int signum, siginfo_t *info, void *ucontext)
{
    if (signum == SIGUSR1)
    {
        write(STDOUT_FILENO, "ping\n", 6);
        
        kill(info->si_pid, SIGUSR2);      /*siginfo_t *info is a pointer to struct that holds, among others, si_pid = Sending process ID . */
    }
}

/* Status :   
 * Reviewer :  
 */

int main()
{
	struct sigaction pongaction;
	pongaction.sa_sigaction = &SIGHandlerPing;  
	pongaction.sa_flags = SA_SIGINFO;     
       										  
	printf("ping's pid is %d \n" , getpid());
	
	sigaction(SIGUSR1, &pongaction ,NULL); 	
	
	while(1)
	{
		pause();
		
		sleep(1); 
		
	}

}
