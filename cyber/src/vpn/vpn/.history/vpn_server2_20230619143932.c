


#include <linux/if_tun.h> /* tun   */
#include <sys/ioctl.h> /* for installing vnic interface */
#include <net/if.h> /* tun  */
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netdb.h>
#include <fcntl.h>
#include <signal.h>
#include <linux/if.h>
 
#define PORT 54321
#define MTU 1400
#define BIND_HOST "0.0.0.0"


static int max(int a, int b)
{
    return a > b ? a : b;
}

static void run(char *cmd) 
{
  printf("Execute `%s`\n", cmd);
  if (system(cmd)) 
  {
    perror(cmd);
    exit(1);
  }
}



int main()
{


    return 0;
}