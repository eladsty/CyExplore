#include <string.h> /* memcpy */
 #include <unistd.h>/*  seek read */
#include <assert.h>
#include <stdlib.h>
#include <fcntl.h>/*open  */
#include <stdio.h>
#include "/home/elad/elad.shem-tov/system_programming/include/ext2.h"
#include "/home/elad/elad.shem-tov/system_programming/include/ext2_linux.h"
 
 
 static char *CurrentFileName(const char *path, char *to_copy);



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
   if(NULL == handle)
   {
        return NULL;
   }

    handle->fd = fd;
    lseek(fd, EXT2_MIN_BLOCK_SIZE, SEEK_SET);
    handle->sb = (struct ext2_super_block *)malloc( sizeof(struct ext2_super_block) );

    if(NULL == handle->sb)
    {
        printf("NULLLL35");
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

/* static size_t Get_inode_offset(handle_t *process, int inode_num)
{
    size_t offset = 0;
    ssize_t fd;
    struct ext2_group_desc *group_desc = NULL;
    unsigned block_size = BASE_OFFSET << (process->sb->s_log_block_size);
    size_t blockgroup_number = (inode_num-1) / process->sb->s_inodes_per_group;

    /* maybe it will be quicker to deduct inode no. with (inode_size * inode_per_group) *
    size_t inode_index =  (inode_num-1) % process->sb->s_inodes_per_group;
    size_t group_desc_offset = sizeof(struct ext2_group_desc) * inode_blockgroup ;

    lseek(process->fd, block_size + group_desc_offset, SEEK_SET);

    group_desc = (struct ext2_group_desc *)malloc(sizeof(struct ext2_group_desc));
    if(NULL == group_desc)
    {
        return -1;
    }
    fd = read(process->fd, group_desc, sizeof(struct ext2_group_desc));
    if(-1 == fd)
    {
        free(group_desc);
        group_desc = NULL;
        return -1;
    }
    offset = (group_desc->bg_inode_table) * block_size + inode_index*(process->sb->s_inode_size);
    free(group_desc);
    group_desc = NULL;

    return offset;
}

*/

inode_t EXT2GetFileDescriptor(handle_t *process, char *file_path)
{
  	struct ext2_inode *inode_struct = NULL; 
    char *str = NULL;
    size_t sum_rec_len = 0;
    char path_name[40];
    size_t block_size = EXT2_BLOCK_SIZE(process->sb);
    char file_name[EXT2_NAME_LEN+1];
    char buffer[4096];
	struct ext2_dir_entry_2 entry;
    ssize_t read_status = 0;
	struct ext2_group_desc *group_desc = NULL;
    size_t root_offset = 0;
    unsigned size = 0;
   
	group_desc = (struct ext2_group_desc *)malloc(sizeof(struct ext2_group_desc ));
     
    if(NULL == group_desc)  
    {
        return -1;
    }

    read_status = pread(process->fd, group_desc, sizeof(struct ext2_group_desc), block_size);

    if(-1 == read_status)
    {
        free(group_desc);
        group_desc = NULL;
        return -1;
    }  
     /* jump to inode table, by multiplying, might need to change 2 to 1 to reach root */
    root_offset = group_desc->bg_inode_table * block_size + (process->sb->s_inode_size);
    
    inode_struct = (struct ext2_inode *)malloc((process->sb->s_inode_size)); 

	if (NULL == inode_struct)
	{
		free(group_desc);
		group_desc = NULL;
		return -1; 
	}
        /* look for root inode */
    read_status = pread(process->fd, inode_struct, process->sb->s_inode_size, root_offset);

    if (-1 == read_status)
	{
        free(inode_struct);
        inode_struct = NULL;
        free(group_desc);
		group_desc = NULL;
		return -1; 
    }
    /* Go to the first entry */
    read_status = pread(process->fd, &buffer, sizeof(buffer), (inode_struct->i_block[0] * block_size));

    CurrentFileName(file_path, path_name);
    while(size <= inode_struct->i_size) 
    {
         memcpy(&entry, buffer + size, sizeof(struct ext2_dir_entry_2));
        
        if(0 == strcmp(entry.name, file_path + 1) )
        {
            free(group_desc);
            group_desc = NULL;
            free(inode_struct);
            inode_struct = NULL;
            return entry.inode;
        }
 
        size += entry.rec_len;
         printf("%d\n", size);
    }    
  
    free(group_desc);
    group_desc = NULL;
    free(inode_struct);
    inode_struct = NULL;
	return -1; 
}


static char *CurrentFileName(const char *path, char *to_copy)
{
    char *tmp = (char *)path;
    size_t offset = 0;
    tmp = index(tmp + 1, '/');
    if (NULL != tmp)
    {
        offset = tmp - (path + 1);
    }
    else
    {
        offset = strlen(path + 1);
    }
    strncpy(to_copy, path + 1, offset);
    *(to_copy + offset) = '\0';
    return to_copy;
}


/* 
 * Description : EXT2ReadBytes reads n bytes from a file into a user buffer. 
 * Arguments : process - pointer to handler returned by EXT2Open, s
 * file_descriptor - returned by EXT2GetFileDescriptor, buffer - user 
 * destination buffer, nbytes - number of bytes to read from file.
 * Return : pointer to buffer, NULL if an error occured.
 * Time Complexity
}

 
#define BLOCK_OFFSET(block) (BASE_OFFSET+(block-1)*block_size)
#define EXT2_BLOCK_SIZE(s)	(EXT2_MIN_BLOCK_SIZE << (s)->s_log_block_size)

*/