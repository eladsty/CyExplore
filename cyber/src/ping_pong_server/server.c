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
#include <errno.h>

#include "server.h"

#define MAX_TCP_CONNECTIONS 10
#define MAX(a, b) (a > b ? a : b)
/*
a single socket for each tcp and udp connection was created,
for multiple sockets, probably an array of sockets would be a proper solution.
currently it should be possible to get 3 sockets of each type.
 */

void HandleTcpCon(int fd_tcp_client, int *fd_arr, int i, char *server_msg)
{
    char buff[MAX_LINE];
    int retval = 0;
    retval = recv(fd_tcp_client, buff, MAX_LINE, 0);

    if (retval < 0)
    {
        printf("couldnt receive message");
        return;
    }
    if (retval == 0)
    {
        fd_arr[i] = -1;
        close(fd_tcp_client);
        return;
    }
    send(fd_tcp_client, server_msg, MAX_LINE, 0);
}

int HandleTcpServer(int server_fd, int *fd_arr, fd_set *fd_set, struct sockaddr_in *client_addr, socklen_t *len)
{

    int connect_fd = accept(server_fd, (struct sockaddr *)&client_addr, len);
    int i = 0;
    if (connect_fd < 0)
    {
        printf("Can't accept client \n");
        return -1;
    }

    for (i = 0; i < MAX_TCP_CONNECTIONS; ++i)
    {
        if (-1 == fd_arr[i])
        {
            fd_arr[i] = connect_fd;
            FD_SET(connect_fd, fd_set);
            return 0;
        }
    }

    printf("no connections availbele");
    return -1;
}

static void LogToFile(char *msg)
{
    FILE *log_file = fopen("server_log.txt", "a");
    fwrite(msg, 1, strlen(msg), log_file);
    fclose(log_file);
}

int main()
{
    int select_status = 0;
    int server_socket_fd, connect_fd, udp_fd, n_ready, max_fdp;
    char client_msg[MAX_LINE] = {0};
    fd_set read_fds;
    ssize_t n = 0;
    socklen_t len = 0;
    struct sockaddr_in client_addr, server_addr;
    char *server_msg = "pong\n";
    struct timeval timeout;
    int rec_result = 0;
    int send_status = 0;
    int fd_arr[MAX_TCP_CONNECTIONS];
    int i = 0;
    /* create listening TCP socket */
    server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    /* bind server address structure to listen file descriptor */
    if (0 > bind(server_socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)))
    {
        printf("tcp couldn't bind to the port\n");
        return -1;
    }
    printf("tcp bind successfully. \n");

    if (listen(server_socket_fd, 100) < 0)
    {
        printf("Error while listening\n");
        return -1;
    }
    printf("\n Listening for incoming connections.....\n ");

    /* creating udp socket */
    udp_fd = socket(AF_INET, SOCK_DGRAM, 0);

    if (0 > bind(udp_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)))
    {
        printf("udp couldn't bind to the port\n");
        return -1;
    }
    printf("udp bind successfully. \n");

    FD_ZERO(&read_fds);

    for (i = 0; i < MAX_TCP_CONNECTIONS; ++i)
    {
        fd_arr[i] = -1;
    }

    FD_SET(server_socket_fd, &read_fds);
    FD_SET(udp_fd, &read_fds);
    FD_SET(STDIN_FILENO, &read_fds);

    while (1)
    {
        /* set listen fd and udp fd in read set */
        /*  timeout.tv_sec = 7;
         timeout.tv_usec = 0; */
        printf("here");
        /* select the ready descriptor */
        FD_ZERO(&read_fds);
        FD_SET(server_socket_fd, &read_fds);
        FD_SET(udp_fd, &read_fds);
        FD_SET(STDIN_FILENO, &read_fds);
        for (i = 0; i < MAX_TCP_CONNECTIONS; ++i)
        {
            if(fd_arr[i] > -1)
            {
                FD_SET(fd_arr[i], &read_fds);
            }
        }

        select_status = select(FD_SETSIZE, &read_fds, NULL, NULL, NULL);
        if (0 == select_status)
        {
            LogToFile("no action for 7 seconds\n");
            printf("o in select");
        }

        if (select_status < 0)
        {
            LogToFile("select failed. exiting. the loop");
            break;
        }

        /* if tcp socket is readable then accept the conenction */
        if (FD_ISSET(server_socket_fd, &read_fds))
        {
            HandleTcpServer(server_socket_fd, fd_arr, &read_fds, &client_addr, &len);
        }

        if (FD_ISSET(udp_fd, &read_fds))
        {
            bzero(client_msg, sizeof(client_msg));
            n = recvfrom(udp_fd, client_msg, MAX_LINE, 0, (struct sockaddr *)&client_addr, &len);

            if (n < 0)
            {
                printf("Couldn't receive\n");
                LogToFile("couldn't receive client message.\n");

                return -1;
            }

            printf("received message from udp client: %s", client_msg);

            send_status = send(udp_fd, server_msg, sizeof(server_msg), 0);
            printf("here");
        }

        if (FD_ISSET(STDIN_FILENO, &read_fds))
        {
            char buff[MAX_LINE];
            fgets(buff, MAX_LINE, stdin);
            if (0 == strcmp("ping\n", buff))
            {
                printf("pong\n");
            }
            if (0 == strcmp("quit\n", buff))
            {
                LogToFile("exiting.\n");
                exit(0);
            }
        }

        for (i = 0; i < MAX_TCP_CONNECTIONS; ++i)
        {
            printf("%d", fd_arr[i]);
            if (-1 == fd_arr[i] && FD_ISSET(fd_arr[i], &read_fds))
            {
                HandleTcpCon(fd_arr[i], fd_arr, i, server_msg);
            }
        }
    }
    return 0;
}
