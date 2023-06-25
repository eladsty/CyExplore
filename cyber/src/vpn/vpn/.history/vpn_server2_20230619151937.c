


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
 
#define PORT 5054
#define MTU 1400
#define BIND_HOST "0.0.0.0"
#define MAX_LINE 1024

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

void setup_route_table() 
{
    run("iptables ");


    run("iptables -t nat -A POSTROUTING -s 10.8.0.0/16 ! -d 10.8.0.0/16 -m comment --comment 'elad_vpn' -j MASQUERADE");
    run("iptables -A FORWARD -s 10.8.0.0/16 -m state --state RELATED,ESTABLISHED -j ACCEPT");
    run("iptables -A FORWARD -d 10.8.0.0/16 -j ACCEPT");
}

int tun_alloc() 
{
  struct ifreq ifr;
  int fd, e;
  fd = open("/dev/net/tun",  O_RDWR);
  if (fd < 0) 
  {
    perror("Cannot open /dev/net/tun");
    return fd;
  }

  memset(&ifr, 0, sizeof(ifr));

/* IFF_NO_PI - don't provide packet info */

  ifr.ifr_flags = IFF_TUN | IFF_NO_PI;

  strncpy(ifr.ifr_name, "tun0", IF_NAMESIZE);
  e = ioctl(fd, TUNSETIFF, (void *) &ifr);

  if (e < 0) 
  {
    perror("ioctl[TUNSETIFF]");
    close(fd);
    return e;
  }

  return fd;
}


int main()
{


    return 0;
}