
#define _POSIX_C_SOURCE 200809L
#define _POSIX_SOURCE 500
#define _XOPEN_SOURCE_EXTENDED 1

#include <signal.h>    /* signal handling */
#include <sys/types.h> /* fork */
#include <unistd.h>    /* getppid */
#include <sys/wait.h>  /* wait */
#include <stdio.h>     /* printf */
#include <string.h> /* strel */
void SIGHandlerPong(int signum)
{
    if (signum == SIGUSR2)
    {
        write(STDOUT_FILENO, "pong\n", 6);
    }
}



/* Status :
 * Reviewer :
 */
int main()
{
    char pingbuffer[255];
    pid_t ping_pid = 0;
    struct sigaction pongaction;

    pongaction.sa_handler = &SIGHandlerPong;
    printf("enter the pid of ping \n");
    fgets(pingbuffer, 255, stdin);

    *(pingbuffer + strlen(pingbuffer) - 1) = '\0'; 

    ping_pid = atoi(pingbuffer);

    sigaction(SIGUSR2, &pongaction, NULL);

    while (1)
    {
        kill(ping_pid, SIGUSR1);
        pause();
        sleep(1);
    }
    return 0;
}
