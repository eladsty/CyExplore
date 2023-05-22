#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>


	/* 
	AF_INET host and port format 
	SOCK_STREAM - connection based protocol(tcp)
	SOCK_DGRAM - datagram based protocol 
	*/
int main()
{
	int socket_desc , client_socket, client_size;
    struct sockaddr_in server_addr, client_addr;
    char *server_message = "pong", client_message[10] = {0};

/* tcp socket */
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	
	if(socket_desc < 0)
	{
		printf("error while creating a socket");
		return -1;
	}
	printf("socket created successfully");

/* setting port and IP */

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(43434);  
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(0 > bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) )
	{
		printf("couldn't bind to the port\n");
		return -1;
	}
    printf("bind successfully\n");

	/* listen to clients */

	if(listen(socket_desc, 1) < 0)
	{
		printf("Error while listening\n");
        return -1;
	}
    printf("\n Listening for incoming connections.....\n ");


	/* accept incoming connection */
	client_size = sizeof(client_addr);
	client_socket = accept(socket_desc, (struct sockaddr*)&client_addr, (socklen_t *)&client_size);
	if(client_socket < 0)
	{
		printf("Can't accept client \n");
        return -1;
	}
	printf("Client connected at IP: %s and port: %i\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

 	if (recv(client_socket, client_message, sizeof(client_message), 0) < 0)
	{
        printf("Couldn't receive\n");
        return -1;
    }
	else if(0 == strncmp("ping", client_message, 4))
	{
		if(0 > send(client_socket, server_message, strlen(server_message), 0))
		{
			printf("Couldn't send\n");
			return -1;
		}
	}
 
    close(client_socket);
    close(socket_desc);


	return 0;
}
  
  
