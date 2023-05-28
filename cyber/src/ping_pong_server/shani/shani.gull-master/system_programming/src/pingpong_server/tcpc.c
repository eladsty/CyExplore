
#include <netinet/in.h> /* sockaddr_in*/
#include <sys/socket.h> /* socket, bind, send */
#include <string.h> /* memset */
#include <strings.h> /* bzero */
#include <unistd.h> /* close */
#include <bits/types/struct_timeval.h> /* timeval */
#include <arpa/inet.h> /* inet_ntoa */
#include "../../include/pingpong_server/tcpc.h"
#include "../../../utils/include/logger/logger.h"

#define PORT 12347
#define MAXLINE 100

static int CreateTCPSocket();
static int DestroyTCPSocket(int sockfd);
static int ConnectTCPToServer(int ping_num, int ping_interval);


/* Status : approved
 * Reviewer : Nimrod
 * Description : 
	
 * Arguments : 
	
 * Return : 
 * Time Complexity :
 * Space Complexity :
 */
static int CreateTCPSocket()
{
	int sockfd;
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
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
static int DestroyTCPSocket(int sockfd)
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
static int ConnectTCPToServer(int ping_num, int ping_interval)
{
	int i = 0, sockfd = CreateTCPSocket();
	char buffer[MAXLINE];
	char *message = "Ping";
	struct sockaddr_in servaddr;
	bzero(buffer, MAXLINE);
	
	/* clean garbage */
	memset(&servaddr, 0, sizeof(servaddr));
	/* server info */
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	if (0 > connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)))
	{
		perror("connect()");
		return 1;
	}
	while (i < ping_num)
	{
		if (0 > send(sockfd, message, strlen(message), 0))
		{
			perror("send()");
			break;
		}
		WriteToLogger(LOG_PATH, "sent echo request to tcp server");
		if (0 > recv(sockfd, buffer, MAXLINE, 0))
		{
			perror("recv()");
			break;
		}
		printf("%s\n", buffer);
		sleep(ping_interval);
		++i;
		bzero(buffer, MAXLINE);
	}
	if (1 == DestroyTCPSocket(sockfd))
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
int TCPCommumication()
{
	int ping_num, ping_interval;
	printf("Enter number of pings\n");
	scanf("%d", &ping_num);
	printf("Enter interval between pings\n");
	scanf("%d", &ping_interval);
	if(1 == ConnectTCPToServer(ping_num, ping_interval))
	{
		return 1;
	}
	return 0;
}


int main()
{
	TCPCommumication();
	return 0;
}