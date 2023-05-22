#include <netinet/in.h>  
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>  
#include <sys/types.h>
#include <string.h>

	/* 
	AF_INET host and port format 
	SOCK_STREAM - connection based protocol(tcp)
	SOCK_DGRAM - datagram based protocol 
	*/
int main()
{
	int socket_desc , client_sock, client_size;
    struct sockaddr_in server_addr, client_addr;
    char *server_message = "pong", client_message = "ping";

/* tcp socket */
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	
	if(socket_desc < 0)
	{
		print("error while creating a socket");
		return -1;
	}
	printf("socket created successfully");

/* setting port and IP */

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2345);  
    server_addr.sin_addr.s_addr = inet_addr("10.1.0.1");

	if(0 > bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) )
	{
		print("couldn't bind to the port\n");
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




	char input[6] = {0};
    struct sockaddr_in server_addr;
    int connect_status = 0;
	int clientSocket = 0;

	
	/* bind socket to the specified IP and port */
	
    listen(server_socket, 1);

    connect_status = connect(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
	
	if(connect_status == -1)
	{
		printf("error occured\n");
		return 1;
	}
  
	clientSocket = accept(server_socket, NULL, NULL);


	recv(server_socket, input, sizeof(input), 0);
	if(0 == strncmp(input, ping ,4) )
	{
    	send(clientSocket, server_msg, strlen(server_msg), 0);
 	}
    
    return 0;
}
  
  
