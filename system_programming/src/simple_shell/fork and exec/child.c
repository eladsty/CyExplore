#define _POSIX_SOURCE 500

#include <signal.h> /* signal handling */
#include <stdio.h> /* printf */
#include <unistd.h> /* getppid */
#include <sys/wait.h>/* wait */
#include <stdlib.h>/* exit */

 
 void ping_handler(pid_t a)
{
    write(STDOUT_FILENO, "ping\n", 6);
 }
   

int main()
{
    struct sigaction sa;
    sa.sa_handler = ping_handler;

    sigaction(SIGUSR2, &sa, NULL);

    while (1)
    {
        pause();
        sleep(1);
        kill(getppid(), SIGUSR2);
         }

    return 0;
}