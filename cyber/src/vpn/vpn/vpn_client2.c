
#define _POSIX_C_SOURCE 200112L


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
#define SERVER_HOST "server's  ip"
#define SA_RESTART 0


void cleanup(int sigNum) {
  printf("Goodbye, cruel world....\n");
  if (sigNum == SIGHUP || sigNum == SIGINT || sigNum == SIGTERM) {
    cleanup_route_table();
    exit(0);
  }
}


void CleanExit() 
{
    struct sigaction sa;
    sa.sa_handler = &cleanup;
    sa.sa_flags = SA_RESTART;
    sigfillset(&sa.sa_mask);

    if (sigaction(SIGHUP, &sa, NULL) < 0) 
    {
        perror("Cannot handle SIGHUP");
    }
    if (sigaction(SIGINT, &sa, NULL) < 0) 
    {
        perror("Cannot handle SIGINT");
    }
    if (sigaction(SIGTERM, &sa, NULL) < 0) 
    {
        perror("Cannot handle SIGTERM");
    }
}

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

int tun_alloc() 
{
    struct ifreq ifr;
    int fd, e;
    fd = open("/dev/net/tun", O_RDWR);
    if (fd < 0) 
    {
        perror("Cannot open /dev/net/tun");
        return -1;
    }

    memset(&ifr, 0, sizeof(ifr));

    ifr.ifr_flags = IFF_TUN | IFF_NO_PI;
    strncpy(ifr.ifr_name, "tun0", IFNAMSIZ);
    e = ioctl(fd, TUNSETIFF, (void *) &ifr);
    if (e < 0) 
    {
        perror("ioctl[TUNSETIFF]");
        close(fd);
        return -1;
    }

  return fd;
}


void set_route_table() 
{
    run("sysctl -w net.ipv4.ip_forward=1");
    run("ifconfig tun0 10.0.0.10/24 mtu 1400 up");

   /*
    run("iptables -t nat -A POSTROUTING -o tun0 -j MASQUERADE");
    run("iptables -I FORWARD  -i tun0 -m state --state RELATED,ESTABLISHED -j ACCEPT");
    run("iptables -I FORWARD  -o tun0 -j ACCEPT"); 
    
    */

 
    /* all address via my tun0 */ 

    run("ip route add 0/1 dev tun0");
    run("ip route add 128/1 dev tun0");
}


int main()
{
    tun_alloc();
    ifconfig();
    setup_route_table();
    cleanup_when_sig_exit();

    return 0;
}