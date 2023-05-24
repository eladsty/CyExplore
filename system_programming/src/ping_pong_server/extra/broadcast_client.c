#include <arpa/inet.h> /* htonl, htons */
#include <errno.h>
#include <netinet/in.h> /* sockaddr_in */
#include <signal.h>
#include <stdio.h> /* printf */
#include <stdlib.h> /* exit, rand */
#include <string.h> /* strlen */
#include <strings.h> /* bzero */
#include <sys/select.h> /* fd_set, select */
#include <sys/time.h> /* timeval */
#include <sys/socket.h> /* socklen_t, socket operations */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* fork */
#include <fcntl.h> /* fcntl */
#include "server.h"



int main()
{
    int socket_desc;
    char buffer[MAX_LINE];
    int i = 2;
    char client_message[] = "ping";
    int broadcast_enable = 1;
    struct timeval time_check;
    

    struct sockaddr_in server_addr = {0};
    socklen_t len = sizeof(server_addr);

 
    /* Creating socket file descriptor */
    if ((socket_desc = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(0);
    }

    setsockopt(socket_desc, SOL_SOCKET, SO_BROADCAST, &broadcast_enable, 
                                                    sizeof(broadcast_enable));
    /* Filling server information */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("10.1.255.255");

    while(i)
    {
        --i;

        fgets(client_message, sizeof(client_message), stdin);
        /* Send ping message to server */

        sendto(socket_desc, (const char*)message, strlen(message), 0, 
                (const struct sockaddr*)&server_addr, sizeof(server_addr));
    
        /* receive server's response */
        printf("Message from server: ");
        recvfrom(socket_desc, (char*)buffer, MAXLINE, 0, 
                    (struct sockaddr*)&server_addr, &len);
        puts(buffer);
        sleep_count = (rand() % 8) + 3;
        printf("Sleep for %lu sec\n", sleep_count);
        sleep(sleep_count);
    }

    close(socket_desc);
}
 
 