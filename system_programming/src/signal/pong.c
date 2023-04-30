 
#define _POSIX_SOURCE 500
#define _XOPEN_SOURCE_EXTENDED 1

#include <signal.h> /* signal handling */
#include <sys/types.h> /* fork */
#include <unistd.h> /* getppid */
#include <sys/wait.h>/* wait */
#include <stdio.h> /* printf */


static void SIGHandlerPing()
{
    write(STDOUT_FILENO, "pong\n", 6);
}

int main()
{
    struct sigaction sa;
    pid_t id = 0;
    sa.sa_handler = &SIGHandlerPing;

    printf("ping pid: %d\n", getpid());
    printf("Enter a process id: "); 
    scanf("%d", &id);
    kill(id, SIGUSR2);
    
    sigaction(SIGUSR2, &sa, NULL);
    pause();

    return 0;
}

