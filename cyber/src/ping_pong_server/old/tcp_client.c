#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "server.h"

int main(void)
{
    int socket_desc;
    struct sockaddr_in server_addr;
    char server_message[MAX_LINE];
    char client_message[] = "ping\n";
    int i;
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_desc < 0)
    {
        printf("Unable to create socket\n");
        return -1;
    }

    printf("Socket created successfully\n");

    /*  Set port and IP the same as server-side */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    /* Send connection request to server: */
    connect(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr));
    


    printf("Connected with server successfully \n");

    /*  send message so server */
    for (i = 0; i < 10; i++)
    {
        int ret = 0;
        ret = send(socket_desc, client_message, strlen(client_message), 0);
        if (ret < 0)
        {
            printf("Unable to send message\n");
            return -1;
        }

        /* receive the server response */

        if (recv(socket_desc, server_message, sizeof(server_message), 0) < 0)
        {
            printf("Error while receiving server's msg\n");
            return -1;
        }
        sleep(2);
    }

    close(socket_desc);

    return 0;
}
