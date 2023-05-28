#include <netinet/in.h> /* sockaddr_in*/
#include <sys/socket.h> /* socket, bind, send */
#include <string.h> /* memset */
#include <strings.h> /* bzero */
#include <unistd.h> /* close */
#include <sys/select.h> /* select and macros */
#include <errno.h>

#include "../../include/pingpong_server/server.h"
#include "../../../utils/include/logger/logger.h"

#define PORT 12347
#define MAXLINE 100
#define MAX2(a, b) ((a) > (b) ? (a) : (b))
#define MAXCONNECTIONS 10

static int SocketTerm(int fd);
static int UDPSocketCreate();
static int TCPSocketCreate();
static int SocketTerm(int fd);
static int UDPHandler(int fd, struct sockaddr *serveraddr, socklen_t *len);
static int TCPHandler(int fd, int *connections, struct sockaddr *serveraddr, socklen_t *len, fd_set *read);
static int TCPConnectionHandler(int fd, int *connections, int index);
static int STDINHandler(int udp_s, int tcp_s);

/* Status : approved
 * Reviewer : Nimrod
 * Description : 
	
 * Arguments : 
	
 * Return : 
 * Time Complexity :
 * Space Complexity :
 */

static int UDPSocketCreate()
{
	int socketdf;
	struct sockaddr_in serveraddr;
	struct timeval tv;
	tv.tv_sec = 10;
	tv.tv_usec = 0;
	if (0 > (socketdf = socket(AF_INET, SOCK_DGRAM, 0)))
	{
		perror("socket()");
		exit(1);
	}
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(PORT);
	serveraddr.sin_addr.s_addr = INADDR_ANY;
	if (0 > setsockopt(socketdf, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)))
	{
		perror("setsockopt()");
		exit(1);
	}
	if (0 > (bind(socketdf, (struct sockaddr *)&serveraddr, sizeof(serveraddr))))
	{
		perror("bind()");
		close(socketdf);
		exit(2);
	}
	return socketdf;
}

/* Status : approved
 * Reviewer : Nimrod
 * Description : 
	
 * Arguments : 
	
 * Return : 
 * Time Complexity :
 * Space Complexity :
 */
static int TCPSocketCreate()
{
	int socketdf, on = 1;
	struct sockaddr_in serveraddr;
	if (0 > (socketdf = socket(AF_INET, SOCK_STREAM, 0)))
	{
		perror("socket()");
		exit(1);
	}
	if (0 > setsockopt(socketdf, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on)))
	{
		perror("setsockopt()");
		close(socketdf);
		exit(2);
	}
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(PORT);
	serveraddr.sin_addr.s_addr = INADDR_ANY;
	if (0 > (bind(socketdf, (struct sockaddr *)&serveraddr, sizeof(serveraddr))))
	{
		perror("bind()");
		close(socketdf);
		exit(2);
	}
	return socketdf;
}
/* Status : approved
 * Reviewer : Nimrod
 * Description : 
	
 * Arguments : 
	
 * Return : 
 * Time Complexity :
 * Space Complexity :
 */
static int SocketTerm(int fd)
{
	if (0 > close(fd))
	{
		perror("close()");
		return 1;
	}
	return 0;
}

/* Status : approved
 * Reviewer : Nimrod
 * Description : 
	
 * Arguments : 
	
 * Return : 
 * Time Complexity :
 * Space Complexity :
 */
static int UDPHandler(int fd, struct sockaddr *serveraddr, socklen_t *len)
{
	char buffer[MAXLINE];
	char *message = "Pong";
	bzero(buffer, MAXLINE);
	if (0 > recvfrom(fd, buffer, MAXLINE, 0, serveraddr, len))
	{
		perror("recvfrom()");

		return 1;
	}
	printf("%s\n", buffer);
	if (0 > sendto(fd, message, 5, 0, serveraddr, *len))
	{
		perror("sendto()");
		return 1;
	}
	return 0;
}
/* Status : approved
 * Reviewer : Nimrod
 * Description : 
	
 * Arguments : 
	
 * Return : 
 * Time Complexity :
 * Space Complexity :
 */
static int TCPHandler(int fd, int *connections, struct sockaddr *serveraddr, socklen_t *len, fd_set *read) /* contain the tcp eventloop */
{
	int i, temp;
	temp = accept(fd, serveraddr, len);
	if (0 > temp)
	{
		if (errno != EWOULDBLOCK)
		{
			perror("accept()");
			return 1;
		}
		return 0;
	}
	for (i = 3; i < MAXCONNECTIONS; ++i)
	{
		if (-1 == connections[i])
		{
			connections[i] = temp;
			FD_SET(temp, read);
			return 0;
		}
	}
	printf("maxed out tcp connections\n");
	return 1;
}
/* Status : approved
 * Reviewer : Nimrod
 * Description : 
	
 * Arguments : 
	
 * Return : 
 * Time Complexity :
 * Space Complexity :
 */
static int TCPConnectionHandler(int fd, int *connections, int index)
{
	int temp, i;
	char buffer[MAXLINE];
	char *message = "Pong";
	bzero(buffer, MAXLINE);
	temp = recv(fd, buffer, MAXLINE, 0);
	if(0 > temp)
	{
		perror("recv()");
		return 1;
	}
	if (0 == temp)
	{
		connections[index] = -1;
		WriteToLogger(LOG_PATH, "connection ended");
		return 0;
	}
	printf("%s\n", buffer);
	i = send(fd, message, strlen(message), 0);
	if (0 > i)
	{
		if (errno == ECONNRESET)
		{
			WriteToLogger(LOG_PATH, "connection ended ubruptly");
		}
		perror("send()");
		return 1;
	}
	return 0;
}
/* Status : approved
 * Reviewer : Nimrod
 * Description : 
	
 * Arguments : 
	
 * Return : 
 * Time Complexity :
 * Space Complexity :
 */
static int STDINHandler(int udp_s, int tcp_s)
{
	char buffer[MAXLINE];
	bzero(buffer, MAXLINE);
	if (NULL == fgets(buffer, MAXLINE, stdin))
	{
		perror("fgets()");
		return 1;
	}

	if (0 == strcmp("ping\n", buffer))
	{
		printf("Pong\n");
	}
	else if (0 == strcmp("quit\n", buffer))
	{
		SocketTerm(udp_s);
		SocketTerm(tcp_s);
		exit(0);
	}
	fflush(STDIN_FILENO);
	return 0;
}


/* Status : approved
 * Reviewer : Nimrod
 * Description : 
	
 * Arguments : 
	
 * Return : 
 * Time Complexity :
 * Space Complexity :
 */
int ServerConnect()
{
	struct sockaddr_in serveraddr;
	int udp_socket, tcp_socket, val, i;
	socklen_t len = sizeof(serveraddr);
	fd_set read;
	int connections[MAXCONNECTIONS];
	struct timeval tv;
	tv.tv_usec = 0;
	
	udp_socket = UDPSocketCreate();
	tcp_socket = TCPSocketCreate();
	connections[0] = STDIN_FILENO;
	connections[1] = udp_socket;
	connections[2] = tcp_socket;
	for(i = 3; i < MAXCONNECTIONS; ++i)
	{
		connections[i] = -1;
	}

	if (0 > listen(tcp_socket, 10))
	{
		perror("listen()");
		SocketTerm(tcp_socket);
		exit(1);
	}

	do
	{
		tv.tv_sec = 7;
		FD_ZERO(&read);
		for(i = 0; i < MAXCONNECTIONS; ++i)
		{
			if (-1 != connections[i])
			{
				FD_SET(connections[i], &read);
			}
		}

		if (0 > (val = select(FD_SETSIZE, &read, NULL, NULL, &tv)))
		{
			perror("select()");
			break;
		}
		if (0 == val)
		{
			WriteToLogger(LOG_PATH, "no activity");
			fflush(STDIN_FILENO);
		}

		if (FD_ISSET(tcp_socket, &read))
		{
			TCPHandler(tcp_socket, (int *)&connections, (struct sockaddr *)&serveraddr, &len, &read);
		}
		if (FD_ISSET(udp_socket, &read))
		{
			UDPHandler(udp_socket,(struct sockaddr *)&serveraddr, &len);
		}
		if (FD_ISSET(STDIN_FILENO, &read))
		{
			STDINHandler(udp_socket, tcp_socket);
		}
		for (i = 3; i < MAXCONNECTIONS; ++i)
		{
			if (FD_ISSET(connections[i], &read))
			{
				TCPConnectionHandler(connections[i], connections, i);
			}
		}
	} while (1);
	return 0;
}

int main()
{
	ServerConnect();
	return 0;
}
