#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>        
#include <arpa/inet.h>
#include <stdio.h>

#include "http_server.h"
#define CLIENT_BUFF_SIZE 1000
/* libcurl??? */

int main(void)
{
    char *server_res = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\n Hello World!";
    char client_msg[CLIENT_BUFF_SIZE] = {0};
     int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int client_fd;
    struct sockaddr_in server_addr; 

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
 

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    if ( listen(server_fd, 1) < 0 )
    {
        printf("listen failed.\n");
        return -1;
    }

    printf("listening");
    while (1)
    {
        int n = 0;
        client_fd = accept(server_fd, (SA *)NULL, NULL);
        memset(client_msg, 0 , CLIENT_BUFF_SIZE);
        n = read(client_fd, client_msg, CLIENT_BUFF_SIZE-1);
        if (n < 0)
        {
            printf("failed to read");
            return;
        }
        if ( send(client_fd, server_res, strlen(server_res), 0) < 0)
        {
            printf("send to client failed... \n");
            break;
        }
       
        close(client_fd);
    }
    return 0;
}
 

