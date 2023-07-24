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
    run("iptables -t nat -A POSTROUTING -o tun0 -j MASQUERADE");
    run("iptables -I FORWARD  -i tun0 -m state --state RELATED,ESTABLISHED -j ACCEPT");
    run("iptables -I FORWARD  -o tun0 -j ACCEPT"); 
 
    /* all address via tun0 */ 

    run("ip route add 0/1 dev tun0");
    run("ip route add 128/1 dev tun0");
}

int udp_bind(struct sockaddr *addr, socklen_t* addrlen) 
{
  struct addrinfo hints;
  struct addrinfo *result;
  int sock, flags;

  memset(&hints, 0, sizeof(hints));
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_protocol = IPPROTO_UDP;
 
  const char *host = SERVER_HOST;
 
  if (0 != getaddrinfo(host, NULL, &hints, &result)) 
  {
    perror("getaddrinfo error");
    return -1;
  }

  if (result->ai_family == AF_INET)
    ((struct sockaddr_in *)result->ai_addr)->sin_port = htons(PORT);
  else if (result->ai_family == AF_INET6)
    ((struct sockaddr_in6 *)result->ai_addr)->sin6_port = htons(PORT);
  else {
    fprintf(stderr, "unknown ai_family %d", result->ai_family);
    freeaddrinfo(result);
    return -1;
  }
  memcpy(addr, result->ai_addr, result->ai_addrlen);
  *addrlen = result->ai_addrlen;

  if (-1 == (sock = socket(result->ai_family, SOCK_DGRAM, IPPROTO_UDP)))
  {
    perror("Cannot create socket");
    freeaddrinfo(result);
    return -1;
  }

  freeaddrinfo(result);

  flags = fcntl(sock, F_GETFL, 0);
  if (flags != -1) {
    if (-1 != fcntl(sock, F_SETFL, flags | O_NONBLOCK))
      return sock;
  }
  perror("fcntl error");

  close(sock);
  return -1;
}


int main()
{
    
    tun_alloc();
    ifconfig();
    setup_route_table();

    return 0;
}