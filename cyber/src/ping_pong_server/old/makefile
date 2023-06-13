FLAGS = -g -ansi -pedantic-errors -Wall -Wextra

all:  server tcp udp

server:
	cc $(FLAGS) -o server server.c
	
tcp:
	cc $(FLAGS) -o tcp tcp_client.c
	
udp:
	cc $(FLAGS) -o udp udp_client.c
 
