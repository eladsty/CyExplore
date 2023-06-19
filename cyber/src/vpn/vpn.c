
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
 


/* static int max(int a, int b)
{
    return a > b ? a : b;
}




int udp_bind(*addr, socklen_t* addrlen) 
{
  struct addrinfo hints;
  struct addrinfo *result;
  int sock, flags;
 



  if (0 != getaddrinfo(host, NULL, &hints, &result)) {
    perror("getaddrinfo error");
    return -1;
  }

  if (result->ai_family == AF_INET)
    ((struct sockaddr_in *)result->ai_addr)->sin_port = htons(PORT);
  else if (result->ai_family == AF_INET6)
    ((struct sockaddr_in6 *)result->ai_addr)->sin6_port = htons(PORT);

  memcpy(addr, result->ai_addr, result->ai_addrlen);
  *addrlen = result->ai_addrlen;

  if (-1 == (sock = socket(result->ai_family, SOCK_DGRAM, IPPROTO_UDP))) {
    perror("Cannot create socket");
    freeaddrinfo(result);
    return -1;
  }

  if (0 != bind(sock, result->ai_addr, result->ai_addrlen)) {
    perror("Cannot bind");
    close(sock);
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

 */

/*
 * Create VPN interface /dev/tun0 and return a fd
*/


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

tun_alloc();

/* 
    configure IP address and MTU of vpn interface /dev/tun0


void ifconfig()
{
   char cmd[1024];
   snprintf(cmd, sizeof(cmd), "ifconfig tun0 10.8.0.2/16 mtu %d up", MTU);
   run(cmd);

} 

*/