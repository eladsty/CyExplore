


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
#define SERVER_HOST "server's public ip"


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
    run("sysctl -w net.ipv4.ip_forward=1");

    
    run("iptables -t nat -A POSTROUTING -o tun0 -j MASQUERADE");
    run("iptables -I FORWARD 1 -i tun0 -m state --state RELATED,ESTABLISHED -j ACCEPT");
    run("iptables -I FORWARD 1 -o tun0 -j ACCEPT");

    char cmd[1024];
    run(cmd);

    /* all address via my tun0 */ 
    run("ip route add 0/1 dev tun0");
    run("ip route add 128/1 dev tun0");
}


int main()
{


    return 0;
}