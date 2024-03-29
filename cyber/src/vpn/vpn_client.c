#define _POSIX_C_SOURCE 2
#define _GNU_SOURCE
#include <linux/if_tun.h> /* tun   */
#include <sys/ioctl.h>    /* for installing vnic interface */
#include <net/if.h>       /* tun  */
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
#define SERVER_HOST "192.168.56.1"

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

void ifconfig()
{
  char cmd[1024];
  /* write to cmd buffer the formatted text */
  snprintf(cmd, sizeof(cmd), "ifconfig tun0 10.0.0.4/16 mtu %d up", MTU);
  run(cmd);
}
void encrypt(char *plaintext, char *ciphertext, int len)
{
  memcpy(ciphertext, plaintext, len);
}

void decrypt(char *ciphertext, char *plaintext, int len)
{
  memcpy(plaintext, ciphertext, len);
}
/*
 * Setup route table via `iptables` & `ip route`
 */

/* first allow forwarding, (what will happen if forwarding is disabled?



) */

void setup_route_table()
{
  char cmd[1024];
  run(cmd);
  /* run("ip route flush table main"); */
  run("sysctl -w net.ipv4.ip_forward=1");
  /* all address via tun0 */
  run("ip route add 0/0 dev tun0");
  /* except server address */
  run("ip route add 192.168.56.1 dev enp0s3");

  run("route -n");
}

/*
 * Bind UDP port
 */
int udp_bind(struct sockaddr *addr, socklen_t *addrlen)
{
  struct addrinfo hints;
  struct addrinfo *result;
  int sock, flags, reuse = 1;
  const char *host = SERVER_HOST;

  memset(&hints, 0, sizeof(hints));
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_protocol = IPPROTO_UDP;


  if (0 != getaddrinfo(host, NULL, &hints, &result))
  {
    perror("getaddrinfo error");
    return -1;
  }
  
  if (result->ai_family == AF_INET)
    ((struct sockaddr_in *)result->ai_addr)->sin_port = htons(PORT);
  else if (result->ai_family == AF_INET6)
    ((struct sockaddr_in6 *)result->ai_addr)->sin6_port = htons(PORT);
  else
  {
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
  if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0)
  {
    perror("setsockopt");
    return -1;
  }
  /* printf("server ip? ---> %s\n%s\n%s\n", result->ai_addr->sa_data, result->ai_socktype, result->ai_canonname); */
  /* freeaddrinfo(result); */

  flags = fcntl(sock, F_GETFL, 0);
  if (flags != -1)
  {
    if (-1 != fcntl(sock, F_SETFL, flags | O_NONBLOCK))
      return sock;
  }
  perror("fcntl error");

  close(sock);
  return -1;
}

/*
 * Create VPN interface /dev/tun0 and return a fd
 */

int tun_alloc()
{
  struct ifreq ifr;
  int fd, e;
  fd = open("/dev/net/tun", O_RDWR);
  if (fd < 0)
  {
    perror("Cannot open /dev/net/tun");
    return fd;
  }

  memset(&ifr, 0, sizeof(ifr));

  /* IFF_NO_PI - don't provide packet info */

  ifr.ifr_flags = IFF_TUN | IFF_NO_PI;

  strncpy(ifr.ifr_name, "tun0", IF_NAMESIZE);
  e = ioctl(fd, TUNSETIFF, (void *)&ifr);

  if (e < 0)
  {
    perror("ioctl[TUNSETIFF]");
    close(fd);
    return e;
  }

  return fd;
}

/* void cleanup_route_table()
{
  run("iptables -t nat -D POSTROUTING -o tun0 -j MASQUERADE");
  run("iptables -D FORWARD -i tun0 -m state --state RELATED,ESTABLISHED -j ACCEPT");
  run("iptables -D FORWARD -o tun0 -j ACCEPT");
  char cmd[1024];
  snprintf(cmd, sizeof(cmd), "ip route del %s", SERVER_HOST);
  run(cmd);
  run("ip route del 0/1");
  run("ip route del 128/1");
} */

int main()
{
  int tun_fd, udp_fd;
  struct sockaddr_storage client_addr;
  socklen_t client_addrlen = sizeof(client_addr);
  char tun_buf[MTU], udp_buf[MTU];

  tun_fd = tun_alloc();

  ifconfig();
  setup_route_table();
  udp_fd = udp_bind((struct sockaddr *)&client_addr, &client_addrlen);

  /*
   * tun_buf - memory buffer read from/write to tun dev - is always plain
   * udp_buf - memory buffer read from/write to udp fd - is always encrypted
   */
  bzero(tun_buf, MTU);
  bzero(udp_buf, MTU);

  while (1)
  {
    fd_set readset;
    int max_fd;
    FD_ZERO(&readset);
    FD_SET(tun_fd, &readset);
    FD_SET(udp_fd, &readset);
    max_fd = max(tun_fd, udp_fd) + 1;
    printf("socket set susseccfully!!!!!!!\n");
    if (-1 == select(max_fd, &readset, NULL, NULL, NULL))
    {
      perror("select error");
      break;
    }

    int r;
    if (FD_ISSET(tun_fd, &readset))
    {
      r = read(tun_fd, tun_buf, MTU);
      if (r < 0)
      {
        // TODO: ignore some errno
        perror("read from tun_fd error");
        break;
      }

      encrypt(tun_buf, udp_buf, r);
      printf("Sending to UDP %d bytes ... from tun\n", r);

      r = sendto(udp_fd, udp_buf, r, 0, (const struct sockaddr *)&client_addr, client_addrlen);
      if (r < 0)
      {
        // TODO: ignore some errno
        perror("sendto udp_fd error");
        break;
      }
    }

    if (FD_ISSET(udp_fd, &readset))
    {
      r = recvfrom(udp_fd, udp_buf, MTU, 0, (struct sockaddr *)&client_addr, &client_addrlen);
      if (r < 0)
      {
        // TODO: ignore some errno
        perror("recvfrom udp_fd error");
        break;
      }

      decrypt(udp_buf, tun_buf, r);
      printf("Writing to tun %d bytes ...\n", r);

      r = write(tun_fd, tun_buf, r);
      if (r < 0)
      {
        // TODO: ignore some errno
        perror("write tun_fd error");
        break;
      }
    }
  }

  close(tun_fd);
  close(udp_fd);

  /* cleanup_route_table(); */

  return 0;
}
