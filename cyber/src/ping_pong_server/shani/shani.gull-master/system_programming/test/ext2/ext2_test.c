#include "../../include/ext2/ext2.h"
#include <fcntl.h> /* open */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
void Program(void)
{
	handle_t *handle;
	inode_t ino;
	char path[1024];
	char select[2] = {"1"};
	char *buffer = (char *)malloc(8192);
	size_t temp;
	printf("Hello user, please enter a file's path: ");
	scanf("%s", path);
	printf("\n");

	handle = EXT2Open("/dev/ram0");
	while('\0' != select)
	{
		ino = EXT2GetFileDescriptor(handle, path);
		printf("What would you like to do?\n1 - read a file\n2 - get file size\n3 - read superblock\n4 - read file's group descriptor\n5 - change permissions\n0 - leave\n");
		scanf("%s", select);
		switch (select[0])
		{
		case '0':
			free(buffer);
			buffer = NULL;
			return;
		case '1':
			printf("write number of bytes to read,\nwe support up to 8192 bytes: ");
			scanf("%ld", &temp);
			buffer = (char *)EXT2ReadBytes(handle, ino, buffer, temp);
			buffer[temp] = '\0';
			printf("%s\n\n", buffer);
			break;
		case '2':
			printf("file %s size is %ld\n\n\n", path, EXT2GetFileSize(handle, ino));
			break;
		case '3':
			EXT2PrintSuperblock(handle);
			printf("\n\n");
			break;
		case '4':
			EXT2PrintGroupDescriptor(handle, ino);
			printf("\n\n");
			break;
		case '5':
			printf("write a 4 letter octal number: ");
			scanf("%ld", &temp);
			EXT2ChangeMode(handle, ino, temp);
		default:
			break;
		}
	}
	free(buffer);
	buffer = NULL;
}
int main(void)
{
	handle_t *handle = EXT2Open("/dev/ram0");
	long size_fd;
	int i = 0;
	size_t oct = 7777;
	void *buffer;
	inode_t fd = EXT2GetFileDescriptor(handle, "/test.txt");
	/*size_fd = EXT2GetFileSize(handle,fd);
	buffer = malloc(size_fd + 1);
	printf("%s\n", (char *)buffer);
	if(buffer == NULL)
	{
		return 1;
	}
	buffer = EXT2ReadBytes(handle, fd, buffer, size_fd);
	*((char *)buffer + size_fd) = '\0';
	printf("%s\n", (char *)buffer);
	free(buffer);
	buffer = NULL;
	i = EXT2ChangeMode(handle, fd, oct);
	if (0 > i)
	{
		return 1;
	}
	i = EXT2Close(handle);
	if (0 > i)
	{
		return -1;
	}*/
	Program();

	return (0);
}

