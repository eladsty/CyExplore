#ifndef __SERVER_H_CR4__ 
#define __SERVER_H_CR4__ 

#define LOG_PATH  "server_log.txt"
/*
 * Description : creates a server for TCP and UDP connections, as well as 
					stdin input.
 * Arguments : void
 * Return : success / fail
 */
int ServerConnect(void);
#endif /* __SERVER_H_CR4__ */