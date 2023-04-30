#define _POSIX_SOURCE 500

#include <signal.h> /* signal handling */
#include <stdio.h> /* printf */
#include <unistd.h> /* getppid */
#include <sys/wait.h>/* wait */
#include <stdlib.h>/* exit */

#include "/home/elad/elad.shem-tov/system_programming/include/signal.h"

#define CMD_BUFF_SIZE 255 
 
void pong_handler(pid_t a)
{
    write(STDOUT_FILENO, "pong\n", 6);
    sleep(1);
 }

void ping_handler(pid_t a)
{
    write(STDOUT_FILENO, "ping\n", 6);
}
 
 

int PingPong()
{
    struct sigaction sa;
    struct sigaction sa2;
    pid_t pid = 0;
    int i = 0;
    sa.sa_handler = ping_handler;
    sa2.sa_handler = pong_handler;

    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa2, NULL);

    pid = fork(); 
    
    if( pid < 0)
    {
        printf("fork failed");
        return pid;
    }
       
    if(0 == pid)
    {
        sigaction(SIGUSR2, &sa  ,NULL);
        while(1)
        {
            pause();
            sleep(1);
            kill(getppid(), SIGUSR2);
         }
     }

     else
    {   
        sigaction(SIGUSR1, &sa2, NULL);
        while(i < 5)
        {
            sleep(1);
            kill(pid, SIGUSR1);
            wait(0);
            ++i;
            pause();
        }
    } 
    return 0;
}



void ForkExec(int max_signals)
{
	struct sigaction sa;
    struct sigaction sa2;

	pid_t pid = 0;
	
	sa.sa_handler = ping_handler; 
    sa2.sa_handler = pong_handler; 
    
	
    pid = fork();
	
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa2, NULL);

    if(0 > pid)
    {
        printf("fork failed");
    }
    if(0 == pid)
    {
        execlp("/home/elad/elad.shem-tov/system_programming/src/signal/child.out", "/home/elad/elad.shem-tov/system_programming/src/signal/child.out");
    }

     else
    {   
        
        sleep(1);
        kill(pid, SIGUSR1);
        pause();
        wait(0);
    } 
 
}




void NoFork(int max_signals)
{
	struct sigaction sa;
    struct sigaction sa2;
    char cmd_buffer[CMD_BUFF_SIZE] = {0}; 
	pid_t pid = 0;
	
	sa.sa_handler = ping_handler; 
    sa2.sa_handler = pong_handler; 
    	
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa2, NULL);
    if (NULL != fgets(cmd_buffer, CMD_BUFF_SIZE, stdin))
    {
	    system();
    }
    
        
        sleep(1);
        kill(pid, SIGUSR1);
        pause();
        wait(0);
    
 
}

int main()
{
    ForkExec(20);
     return 0;
}