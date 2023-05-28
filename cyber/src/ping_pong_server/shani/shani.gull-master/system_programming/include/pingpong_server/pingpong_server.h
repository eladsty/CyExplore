#ifndef __PINGPONG_SERVER_H_CR4__ 
#define __PINGPONG_SERVER_H_CR4__ 
#include <netinet/in.h> /* sockaddr_in */

typedef struct 
{
	int tcp; /* tcp socket file descriptor */
	int udp; /* udp socket file descriptor */
	int log; /* log file descriptor */
}server_t;

typedef enum{
	TCP,
	UDP
}protocol_t;

/*
 * Description : this function constructs two sokects; TCP and UDP. alongside 
				some metadata regarding the sockets, puts them into a "select"
				API function as readable file descriptors. also creates a 
				log file to log all events into.	
 * Arguments : ntcp - number of TCP sockets, nudp - number of UDP sockets, 
				log_location - path to create and maintain log file
 * Return : pointer to list of socket structs
 */
server_t *Server(server_t *server, char *log_location);

/*
 * Description : 
	
 * Arguments : 
	
 * Return : 
 * Time Complexity :
 * Space Complexity :
 */

void Chat(server_t *server, protocol_t protocol, int interval, int ntimes);
/*
 * Description : 
	
 * Arguments : 
	
 * Return : 
 * Time Complexity :
 * Space Complexity :
 */

/*
 * Description : 
	
 * Arguments : 
	
 * Return : 
 * Time Complexity :
 * Space Complexity :
 */

#endif /* __PINGPONG_SERVER_H_CR4__ */
