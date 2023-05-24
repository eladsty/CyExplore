#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

#include "server.h"

#define MAX(a, b) (a > b ? a : b)
 
/*
a single socket for each tcp and udp connection was created,
for multiple sockets, probably an array of sockets would be a proper solution.
currently it should be possible to get 3 sockets of each type.
 */


static void LogToFile(char *msg)
{
    FILE *log_file = fopen("server_log.txt", "a");
    fwrite(msg, 1, strlen(msg), log_file);
    fclose(log_file);
}

int main()
{
    int listen_fd, connect_fd, udp_fd, n_ready, max_fdp;
    char client_msg[MAX_LINE] = {0};
    fd_set read_fds;
    ssize_t n = 0;
    socklen_t len = 0;
    struct sockaddr_in client_addr, server_addr;
    char *server_msg = "pong\n";
    struct timeval timeout;
    int rec_result = 0;
    int send_status = 0;
    /* create listening TCP socket */
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
   
    /* bind server address structure to listen file descriptor */
    if (0 > bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)))
    {
        printf("tcp couldn't bind to the port\n");
        return -1;
    }
    printf("tcp bind successfully. \n");

    if (listen(listen_fd, 3) < 0)
    {
        printf("Error while listening\n");
        return -1;
    }
    printf("\n Listening for incoming connections.....\n ");

    /* creating udp socket */
    udp_fd = socket(AF_INET, SOCK_DGRAM, 0);

    if (0 > setsockopt(listen_fd, SOL_SOCKET, SO_BROADCAST,(char *)&len, sizeof(len)) )
    {
        perror("setsockopt failed");
    }
   
    if (0 > bind(udp_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)))
    {
        printf("udp couldn't bind to the port\n");
        return -1;
    }
    printf("udp bind successfully. \n");

    FD_ZERO(&read_fds);

    max_fdp = MAX(listen_fd, udp_fd) + 1;

    while (1)
    {
        /* set listen fd and udp fd in read set */
        FD_SET(listen_fd, &read_fds);
        FD_SET(udp_fd, &read_fds);
 
        timeout.tv_sec = 7;
        timeout.tv_usec = 0;

         /* select the ready descriptor */
        if (0 == select(max_fdp, &read_fds, NULL, NULL, &timeout))
        {
            LogToFile("no action for 7 seconds\n");
        }

        /* if tcp socket is readable then accept the conenction */

        if (FD_ISSET(listen_fd, &read_fds) )
        {
            len = sizeof(client_addr);
            bzero(client_msg, sizeof(client_msg));
            connect_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &len);

            if (connect_fd < 0)
            {
                printf("Can't accept client \n");
                return -1;
            }

            printf("Client connected at IP: %s and port: %i\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
            rec_result = recv(connect_fd, client_msg, sizeof(server_msg), 0);
            if (rec_result < 0)
            {
                printf("Couldn't receive\n");
                return -1;
            }
            if (rec_result == 0)
            {
                printf("Connection closed\n");
                LogToFile("No connections\n");
            }

            else if (0 == strncmp("ping", client_msg, 4))
            {
                if (0 > send(connect_fd, server_msg, strlen(server_msg), 0))
                {
                    printf("Couldn't send\n");
                    return -1;
                }
            }

            if (0 == strncmp("quit", client_msg, 4))
            {
                printf("closing server.\n");
                exit(0);
            }

            FD_ZERO(&read_fds);

            bzero(client_msg, sizeof(client_msg));
            close(connect_fd);
        }
        /* if udp socket is readable receive the message.  */
        if (FD_ISSET(udp_fd, &read_fds))
        {
            
            n = recvfrom(udp_fd, client_msg, 6, 0, (struct sockaddr *)&client_addr, &len);
            if (n < 0)
            {
                printf("Couldn't receive\n");
                return -1;
            }

            else if (0 == strncmp("ping\n", client_msg, 4))
            {
                fputs(client_msg, stdout);
                send_status = sendto(udp_fd, server_msg, strlen(server_msg), 0, (struct sockaddr *)&client_addr,
                 sizeof(client_addr));

                if (0 > send_status )
                {
                    printf("Couldn't send, status is: %d\n", send_status);
                    return -1;
                }
                bzero(client_msg, sizeof(client_msg));
            }

            if (0 == strncmp("quit", client_msg, 4))
            {
                printf("closing server.\n");
                /* need to add log event */
                exit(0);
            }
         }
    }

    return 0;
}
