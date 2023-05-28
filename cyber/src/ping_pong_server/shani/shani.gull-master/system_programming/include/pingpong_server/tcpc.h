#ifndef __CLIENT_H_CR4__ 
#define __CLIENT_H_CR4__ 

#define LOG_PATH  "client_log.txt"
/*
 * Description : creates a TCP client, accepting stdin input for ping 
					amount and interval.	
 * Arguments : void	
 * Return : seccess / fail
 */
int TCPCommumication(void);

#endif /* __CLIENT_H_CR4__ */