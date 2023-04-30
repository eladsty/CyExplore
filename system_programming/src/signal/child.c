
#define _POSIX_SOURCE 500
#define _XOPEN_SOURCE_EXTENDED 1

#include <signal.h> /* signal handling */
#include <sys/types.h> /* fork */
#include <unistd.h> /* getppid */
#include <sys/wait.h>/* wait */

#include "/home/elad/elad.shem-tov/system_programming/include/signal.h"



  void ping_handler(pid_t a)
{
    write(STDOUT_FILENO, "ping\n", 6);
}
   
 
 void pong_handler(pid_t a)
{
    write(STDOUT_FILENO, "pong\n", 6);
}
   

int main()
{
    struct sigaction sa;
    sa.sa_handler = ping_handler;

    sigaction(SIGUSR1, &sa, NULL);
    pause();
    sleep(1);
    kill(getppid(), SIGUSR2);
 
    return 0;
}