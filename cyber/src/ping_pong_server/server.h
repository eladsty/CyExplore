int UDPSocketCreate();
int TCPSocketCreate();
int SocketTerm(int fd);
int TCPConnectionHandler(int fd, int *connections, int index);