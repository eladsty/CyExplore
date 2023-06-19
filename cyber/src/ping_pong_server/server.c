

#include "server.h"

int ServerConnect()
{
	struct sockaddr_in serveraddr;
	int udp_socket, tcp_socket, val, i;
	socklen_t len = sizeof(serveraddr);
	fd_set read;
	int connections[3 + MAXCONNECTIONS];
	struct timeval tv;
	tv.tv_usec = 0;
	
	udp_socket = UDPSocketCreate();
	tcp_socket = TCPSocketCreate();
	connections[0] = STDIN_FILENO;
	connections[1] = udp_socket;
	connections[2] = tcp_socket;
	for(i = 3; i < MAXCONNECTIONS; ++i)
	{
		connections[i] = -1;
	}

	if (0 > listen(tcp_socket, 10))
	{
		perror("listen()");
		SocketTerm(tcp_socket);
		exit(1);
	}

	do
	{
		tv.tv_sec = 7;
		FD_ZERO(&read);
		for(i = 0; i < MAXCONNECTIONS; ++i)
		{
			if (-1 != connections[i])
			{
				FD_SET(connections[i], &read);
			}
		}

		if (0 > (val = select(FD_SETSIZE, &read, NULL, NULL, &tv)))
		{
			perror("select()");
			break;
		}
		if (0 == val)
		{
			WriteToLogger(LOG_PATH, "no activity");
			fflush(STDIN_FILENO);
		}

		if (FD_ISSET(tcp_socket, &read))
		{
			TCPHandler(tcp_socket, (int *)&connections, (struct sockaddr *)&serveraddr, &len, &read);
		}
		if (FD_ISSET(udp_socket, &read))
		{
			UDPHandler(udp_socket,(struct sockaddr *)&serveraddr, &len);
		}
		if (FD_ISSET(STDIN_FILENO, &read))
		{
			STDINHandler(udp_socket, tcp_socket);
		}
		for (i = 3; i < MAXCONNECTIONS; ++i)
		{
			if (FD_ISSET(connections[i], &read))
			{
				TCPConnectionHandler(connections[i], connections, i);
			}
		}
	} while (1);
	return 0;
}

int main()
{
	ServerConnect();
	return 0;
}