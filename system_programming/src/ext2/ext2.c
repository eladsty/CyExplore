
 #include <unistd.h>/*  seek read */
#include <assert.h>
#include <stdlib.h>
#include <fcntl.h>/*open  */
#include <stdio.h>
#include "/home/elad/elad.shem-tov/system_programming/include/ext2.h"
#include "/home/elad/elad.shem-tov/system_programming/include/ext2_linux.h"
 
#define BASE_OFFSET
#define BASE_OFFSET 1024
#define BLOCK_OFFSET(block) (BASE_OFFSET+(block-1)*block_size)

 struct process 
{
    int fd;
    struct ext2_super_block *sb;
};

handle_t *EXT2Open(char *device)
{
    ssize_t a = 0;
    inode_t fd = open(device, O_RDWR);
    handle_t *handle = (handle_t *)malloc( sizeof(handle_t) );
    assert(NULL != handle);

    handle->fd = fd;
    lseek(fd, BASE_OFFSET, SEEK_SET);
    handle->sb = (struct ext2_super_block *)malloc( sizeof(struct ext2_super_block) );


    printf("file descriptor is %ld\n",fd);

    if(NULL == handle->sb)
    {
        free(handle);
        handle = NULL;
        return NULL;
    }

    a = read(fd, handle->sb, sizeof(struct ext2_super_block));
    if(-1 == a )
    {
        return NULL;
    }  
    return handle;
}

int EXT2Close(handle_t *process)
{
    if (NULL == process)
	{
		return -1;
	}
    
    close(process->fd);

    free(process->sb);
    process->sb = NULL;

    free(process);
    process = NULL;
 
    return 0;
}

inode_t EXT2GetFileDescriptor(handle_t *process, char *file_path)
{

    BASE_OFFSET
 
}