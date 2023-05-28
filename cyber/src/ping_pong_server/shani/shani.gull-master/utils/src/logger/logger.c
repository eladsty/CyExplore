#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include "../../include/logger/logger.h"


/* Status : 
 * Reviewer : 
 * Description : 
	
 * Arguments : 
	
 * Return : 
 * Time Complexity :
 * Space Complexity :
 */
int WriteToLogger(char *path, char *message)
{
	int fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	char entry[1024];
	time_t now;
	time(&now);
	if (fd < 0)
	{
		perror("open()");
		return fd;
	}
	sprintf(entry, "%s%s\n", ctime(&now), message);
	if (0 > write(fd, entry, strlen(entry)))
	{
		perror("write()");
		close(fd);
		return -1;
	}
	close(fd);
	return 1;
}
