int UDPSocketCreate()
{
	int socketdf;
	struct sockaddr_in serveraddr;
	struct timeval tv;
	tv.tv_sec = 10;
	tv.tv_usec = 0;
	if (0 > (socketdf = socket(AF_INET, SOCK_DGRAM, 0)))
	{
		perror("socket()");
		exit(1);
	}
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(PORT);
	serveraddr.sin_addr.s_addr = INADDR_ANY;
	if (0 > setsockopt(socketdf, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)))
	{
		perror("setsockopt()");
		exit(1);
	}
	if (0 > (bind(socketdf, (struct sockaddr *)&serveraddr, sizeof(serveraddr))))
	{
		perror("bind()");
		close(socketdf);
		exit(2);
	}
	return socketdf;
}


int TCPSocketCreate()
{
	int socketdf, on = 1;
	struct sockaddr_in serveraddr;
	if (0 > (socketdf = socket(AF_INET, SOCK_STREAM, 0)))
	{
		perror("socket()");
		exit(1);
	}
	if (0 > setsockopt(socketdf, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on)))
	{
		perror("setsockopt()");
		close(socketdf);
		exit(2);
	}
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(PORT);
	serveraddr.sin_addr.s_addr = INADDR_ANY;
	if (0 > (bind(socketdf, (struct sockaddr *)&serveraddr, sizeof(serveraddr))))
	{
		perror("bind()");
		close(socketdf);
		exit(2);
	}
	return socketdf;
}


int SocketTerm(int fd)
{
	if (0 > close(fd))
	{
		perror("close()");
		return 1;
	}
	return 0;
}


int TCPConnectionHandler(int fd, int *connections, int index)
{
	int temp, i;
	char buffer[MAXLINE];
	char *message = "Pong";
	bzero(buffer, MAXLINE);
	temp = recv(fd, buffer, MAXLINE, 0);
	if(0 > temp)
	{
		perror("recv()");
		return 1;
	}
	if (0 == temp)
	{
		connections[index] = -1;
		WriteToLogger(LOG_PATH, "connection ended");
		return 0;
	}
	printf("%s\n", buffer);
	i = send(fd, message, strlen(message), 0);
	if (0 > i)
	{
		if (errno == ECONNRESET)
		{
			WriteToLogger(LOG_PATH, "connection ended ubruptly");
		}
		perror("send()");
		return 1;
	}
	return 0;
}
