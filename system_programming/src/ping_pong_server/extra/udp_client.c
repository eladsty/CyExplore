#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "server.h"
 


/* broadcast address 10.1.255.255 */

int main()
{
    int socket_fd;
    char buffer[] = "ping\n";
    char user_buffer[MAX_LINE];
    struct sockaddr_in server_addr;
    socklen_t len;

    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
    {
        printf("socket creation failed");
        exit(0);
    }
 
    memset(&server_addr, 0, sizeof(server_addr));
 
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    /* sending ping to server */
    while (1)
    {
        sendto(socket_fd, buffer, strlen(buffer), 0, (const struct sockaddr*)&server_addr,
            sizeof(server_addr));
    
        recvfrom(socket_fd, user_buffer, sizeof(user_buffer), 0, (struct sockaddr*)&server_addr, &len);

        fputs(user_buffer, stdout);
    }
    close(socket_fd);
    return 0;
}

