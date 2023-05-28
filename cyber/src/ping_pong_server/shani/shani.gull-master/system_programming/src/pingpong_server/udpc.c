
#include <netinet/in.h> /* sockaddr_in*/
#include <sys/socket.h> /* socket, bind, send */
#include <string.h> /* memset */
#include <strings.h> /* bzero */
#include <unistd.h> /* close */
#include <bits/types/struct_timeval.h> /* timeval */
#include <arpa/inet.h> /* inet_ntoa */
#include "../../include/pingpong_server/udpc.h"
#include "../../../utils/include/logger/logger.h"

#define PORT 12347
#define MAXLINE 100
static int SendUDPUnicast();
static int SendUDPBroadcast();
static int DestroyUDPSocket(int sockfd);
static int CreateUDPSocket();

/* Status : approved
 * Reviewer : Nimrod
 * Description : 
	
 * Arguments : 
	
 * Return : 
 * Time Complexity :
 * Space Complexity :
 */
static int CreateUDPSocket()
{
	int sockfd;
	
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("socket()");
		exit(1);
	}
	
	return sockfd;
}

/* Status : approved
 * Reviewer : Nimrod
 * Description : 
	
 * Arguments : 
	
 * Return : 
 * Time Complexity :
 * Space Complexity :
 */
static int DestroyUDPSocket(int sockfd)
{
	int ret = close(sockfd);
	if (0 > ret)
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
static int SendUDPBroadcast()
{
	
	struct sockaddr_in servaddr;
	char *message = "Ping", buffer[MAXLINE];
	socklen_t len = 0;
	int on = 1;
	int socketfd = CreateUDPSocket();
	bzero(buffer, MAXLINE);
	/* clean garbage */
	memset(&servaddr, 0, sizeof(servaddr));
	/* server info */
	servaddr.sin_addr.s_addr = INADDR_BROADCAST;
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	if (0 > setsockopt(socketfd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on)))
	{
		perror("setsockopt()");
		exit(1);
	}

	if (0 > (sendto(socketfd, message, strlen(message) + 1, 0, 
							(struct sockaddr *)&servaddr, sizeof(servaddr))))
	{
		perror("sendto()");
		exit(1);
	}
	WriteToLogger(LOG_PATH, "sent echo request to udp server");
	if (0 > recvfrom(socketfd, buffer, MAXLINE, 0, (struct sockaddr *)&servaddr, &len))
	{
		perror("recvfrom()");
		return 1;
	}
	printf("%s\n", buffer);
	if (1 == DestroyUDPSocket(socketfd))
	{
		printf("udp socket did not close\n");
		return 1;
	}
	bzero(buffer, MAXLINE);
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
static int SendUDPUnicast()
{
	struct sockaddr_in servaddr;
	char *message = "Ping", buffer[MAXLINE];
	socklen_t len = 0;
	struct timeval tv;
	int socketfd = CreateUDPSocket();
	tv.tv_sec = 10;
	tv.tv_usec = 0;
	bzero(buffer, MAXLINE);
	/* clean garbage */
	memset(&servaddr, 0, sizeof(servaddr));
	/* server info */
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	
	if (0 > setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)))
	{
		perror("setsockopt()");
		exit(1);
	}

	if (0 > (sendto(socketfd, message, strlen(message) + 1, 0, 
							(struct sockaddr *)&servaddr, sizeof(servaddr))))
	{
		perror("sendto()");
		exit(1);
	}
	WriteToLogger(LOG_PATH, "sent echo request to udp server");
	if (0 > recvfrom(socketfd, buffer, MAXLINE, 0, (struct sockaddr *)&servaddr, &len))
	{
		perror("recvfrom()");
		return 1;
	}
	printf("%s\n", buffer);
	if (1 == DestroyUDPSocket(socketfd))
	{
		printf("udp socket did not close\n");
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
int UDPCommumication()
{
	int counter = 0;
	while(counter != 10)
	{
		SendUDPUnicast();
		sleep(2);
		++counter;
	}
	/* SendUDPBroadcast();*/
	
	return 0;
}

int main()
{
	UDPCommumication();
	return 0;
}