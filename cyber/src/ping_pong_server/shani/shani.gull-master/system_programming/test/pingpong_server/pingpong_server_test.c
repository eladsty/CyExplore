#include <unistd.h> /* getcwd */
#include <stdlib.h> /* malloc free */
#include <stdio.h> /* printf */
#include <string.h> /* strcat */
#include "../../include/pingpong_server/pingpong_server.h"

#define FREE(ptr)                               \
    {                                           \
      free (ptr);                               \
      (ptr) = NULL;                             \
    }                                           \

int main(void)
{
	server_t server;
	char buff[1024];
	getcwd((char *)&buff, 1024);
	strcat((char *)&buff, "/log.txt");
	Server(&server, buff);
	Chat(&server, TCP, 1, 3);
	close(server.log);
	close(server.tcp);
	close(server.udp);

	return (0);
}

