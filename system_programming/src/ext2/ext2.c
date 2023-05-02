#define _XOPEN_SOURCE 500
#include <string.h> /* memcpy */
#include <unistd.h> /*  seek read */
#include <assert.h>
#include <stdlib.h>/* malloc */
#include <fcntl.h>/*open  */
#include <stdio.h>/*  */
#include "/home/elad/elad.shem-tov/system_programming/include/ext2.h"
#include "/home/elad/elad.shem-tov/system_programming/include/ext2_linux.h"
#define BASE_OFFSET 1024
#define BLOCK_SIZE 4096
#define ROOT_INODE 2
#define MAX_PATH_SIZE 4096
static char *CurrentFileName(const char *path, char *to_copy);



/* 

APPROVED BY RAN KLEIN

 */





struct process
{
    int fd;
    struct ext2_super_block *sb;
    struct ext2_group_desc *group_desc_table;
};

struct process *EXT2Open(char *device)
{
    ssize_t a = 0;
    int fd = 0;
    struct process *process = NULL;  
    unsigned group_desc_amount = 0;
    int read_status = 0;
    size_t block_size = 0;
    fd = open(device, O_RDWR);

    if(0 > fd)
    {
        return NULL;
    }
    
    process = (struct process *)malloc(sizeof(struct process));
    if (NULL == process)
    {
        return NULL;
    }

    process->fd = fd;
    process->sb = (struct ext2_super_block *)malloc(sizeof(struct ext2_super_block));

    if (NULL == process->sb)
    {
        free(process);
        process = NULL;
        return NULL;
    }
    read_status = pread(process->fd, process->sb, sizeof(struct ext2_super_block), BASE_OFFSET);
    if(-1 == read_status)
    {
        return NULL;
    }
    block_size = BASE_OFFSET << (process->sb->s_log_block_size);
    group_desc_amount = process->sb->s_blocks_count / process->sb->s_blocks_per_group + 1;
    process->group_desc_table = (struct ext2_group_desc *)malloc(sizeof(struct ext2_group_desc) * group_desc_amount);
    read_status = pread(process->fd, process->group_desc_table, sizeof(struct ext2_group_desc) * group_desc_amount, BLOCK_SIZE);

    return process;
}

int EXT2Close(struct process *process)
{
    if (NULL == process)
    {
        return -1;
    }

    close(process->fd);

    free(process->sb);
    process->sb = NULL;

    free(process->group_desc_table);
    process->group_desc_table = NULL;

    free(process);
    process = NULL;

    return 0;
}
 
int GetInodeStruct(struct process *process, struct ext2_inode *inode, inode_t inode_no)
{
    struct ext2_group_desc group_desc = { 0 };
    size_t block_size = EXT2_BLOCK_SIZE(process->sb);
    size_t inode_offset = 0;
    ssize_t read_status = 0;
    size_t group_num = 0;
 
    group_num = (inode_no - 1) / process->sb->s_inodes_per_group ;
    group_desc = process->group_desc_table[group_num];
    inode_offset = group_desc.bg_inode_table * block_size + ((inode_no - 1) % process->sb->s_inodes_per_group ) * (process->sb->s_inode_size);
    read_status = pread(process->fd, inode, sizeof(struct ext2_inode), inode_offset);

    if (-1 == read_status)
    {
        return -1;
    }

}


int SetInodeStruct(struct process *process, struct ext2_inode *inode, inode_t inode_no)
{
    struct ext2_group_desc group_desc = { 0 };
    size_t block_size = EXT2_BLOCK_SIZE(process->sb);
    size_t inode_offset = 0;
    ssize_t read_status = 0;
    size_t group_num = 0;
 
    group_num = (inode_no - 1) / process->sb->s_inodes_per_group ;
    group_desc = process->group_desc_table[group_num];
    inode_offset = group_desc.bg_inode_table * block_size + ((inode_no - 1) % process->sb->s_inodes_per_group ) * (process->sb->s_inode_size);
    read_status = pwrite(process->fd, inode, sizeof(struct ext2_inode), inode_offset);

    if (-1 == read_status)
    {
        return -1;
    }
 
}



static inode_t SearchInDirectory(char *name_to_find, struct ext2_dir_entry_2 *dir, size_t dir_size)
{
    size_t searched_bytes = 0;
    while (0 != dir->rec_len)
    {
        if (0 == strcmp(name_to_find, dir->name))
        {
            return dir->inode;
        }
        dir = (struct ext2_dir_entry_2 *)((char *)dir + dir->rec_len);
        searched_bytes += dir->rec_len;
    }
    return -1;
}

inode_t EXT2GetFileDescriptor(struct process *process, char *file_path)
{
    
    inode_t curr_inode = ROOT_INODE;
    char path_name[MAX_PATH_SIZE] = {0};
    char *curr_partial_path = NULL;
    ssize_t read_status = 0;
    size_t block_size = EXT2_BLOCK_SIZE(process->sb);
    size_t group_desc_index = 0;
    size_t curr_inode_offset = 0;
    struct ext2_group_desc *group_desc = NULL;
    struct ext2_inode found_inode;
    struct ext2_dir_entry_2 *dir = (struct ext2_dir_entry_2 *)malloc(block_size);

    if (NULL == dir)
    {
        return -1;
    }

    strcpy(path_name, file_path);
    curr_partial_path = strtok(path_name, "/");

    /* block_size indicates 1 block, but it's possible to have more than one block of data */

    while (NULL != curr_partial_path)
    {
        group_desc_index = curr_inode / process->sb->s_inodes_per_group;
        curr_inode_offset = ((process->group_desc_table)[group_desc_index].bg_inode_table * block_size)
                 + ((curr_inode - 1) * process->sb->s_inode_size);
        pread(process->fd, &found_inode, sizeof(struct ext2_inode), curr_inode_offset);

        pread(process->fd, dir, block_size, found_inode.i_block[0] * block_size);

        curr_inode = SearchInDirectory(curr_partial_path, dir, block_size);
        if (curr_inode < 0)
        {
            break;
        }
        curr_partial_path = strtok(NULL, "/");
    }

    free(dir);
    dir = NULL;
    return curr_inode;
}
 

/*
 * Description : EXT2ReadBytes reads n bytes from a file into a user buffer.
 * Arguments : process - pointer to handler returned by EXT2Open, s
 * file_descriptor - returned by EXT2GetFileDescriptor, buffer - user
 * destination buffer, nbytes - number of bytes to read from file.
 * Return : pointer to buffer, NULL if an error occured.
 * Time Complexity
*/
void *EXT2ReadBytes(handle_t *process, inode_t inode_num, void *buffer, size_t nbytes)
{
    /*
    * finds the data block of inode_num
        - find ext2_inode struct
    * pread from data block to buffer
        - read block at a time
    */
    unsigned i = 0;
    size_t block_size = EXT2_BLOCK_SIZE(process->sb);
    size_t group_desc_index = inode_num / process->sb->s_inodes_per_group;
    size_t curr_inode_offset = ((process->group_desc_table)[group_desc_index].bg_inode_table * block_size) + ((inode_num - 1) * 256);
    struct ext2_inode inode_struct = {0};

    pread(process->fd, &inode_struct, sizeof(struct ext2_inode), curr_inode_offset);
    printf("this is the current i_mode %b", inode_struct.i_mode);    
    while(inode_struct.i_block[i] != 0 && nbytes > 0 && i < 12)
    {
        pread(process->fd, buffer , (nbytes < block_size? nbytes: block_size) , inode_struct.i_block[i] * block_size);
        nbytes -= (nbytes < block_size? nbytes: block_size);
        ++i;
    }

    return buffer;
    
   /* finds the data block of inpode_num */

}
 


long EXT2GetFileSize(handle_t *process, inode_t inode_no)
{
    struct ext2_inode inode;
    int status = 0;
    status = GetInodeStruct(process, &inode, inode_no);

    if(status < 0)
    {
        return -1;
    }
 
	return inode.i_size;
}


void EXT2PrintSuperblock(handle_t *process)
{
    printf("\n\n******** Print Super Block ********\n\n");
    printf("s_inodes_count:\t\t\t%u\n", process->sb->s_inodes_count);
    printf("s_blocks_count:\t\t\t%u\n", process->sb->s_blocks_count);
    printf("s_r_blocks_count:\t\t%u\n", process->sb->s_r_blocks_count);
    printf("s_free_blocks_count:\t\t%u\n", process->sb->s_free_blocks_count);
    printf("s_free_inodes_count:\t\t%u\n", process->sb->s_free_inodes_count);
    printf("s_first_data_block:\t\t%u\n", process->sb->s_first_data_block);
    printf("s_log_block_size:\t\t%u\n", process->sb->s_log_block_size);
    printf("s_log_frag_size:\t\t%d\n", process->sb->s_log_frag_size);
    printf("s_blocks_per_group:\t\t%u\n", process->sb->s_blocks_per_group);
    printf("s_frags_per_group:\t\t%u\n", process->sb->s_frags_per_group);
    printf("s_inodes_per_group:\t\t%u\n", process->sb->s_inodes_per_group);
    printf("s_mtime:\t\t\t%u\n", process->sb->s_mtime);
    printf("s_wtime:\t\t\t%u\n", process->sb->s_wtime);
    printf("s_mnt_count:\t\t\t%u\n", process->sb->s_mnt_count);

    printf("s_max_mnt_count:\t\t%d\n", process->sb->s_max_mnt_count);
    printf("s_magic:\t\t\t%u\n", process->sb->s_magic);
    printf("s_state:\t\t\t%u\n", process->sb->s_state);
    printf("s_errors:\t\\tt%u\n", process->sb->s_errors);
    printf("s_minor_rev_level:\t\t%u\n", process->sb->s_minor_rev_level);
    printf("s_lastcheck:\t\t\t%u\n", process->sb->s_lastcheck);
    printf("s_checkinterval:\t\t%u\n", process->sb->s_checkinterval);
    printf("s_creator_os:\t\t\t%u\n", process->sb->s_creator_os);
    printf("s_rev_level:\t\t\t%u\n", process->sb->s_rev_level);
    printf("s_def_resuid:\t\t\t%u\n", process->sb->s_def_resuid);
    printf("s_def_resgid:\t\t\t%u\n", process->sb->s_def_resgid);
    printf("s_first_ino:\t\t\t%u\n", process->sb->s_first_ino);
    printf("s_inode_size:\t\t\t%u\n", process->sb->s_inode_size);
    printf("s_block_group_nr:\t\t%u\n", process->sb->s_block_group_nr);
    printf("s_feature_compat:\t\t%u\n", process->sb->s_feature_compat);
    printf("s_feature_incompat:\t\t%u\n", process->sb->s_feature_incompat);
    printf("s_feature_ro_compat:\t\t%u\n", process->sb->s_feature_ro_compat);


}
static int read_group_descriptor(handle_t *process, inode_t inode_no, struct ext2_group_desc *group_desc)
{
	int read_gd;
    size_t block_size = 0; 
    size_t g_desc_offset = block_size + (block_size * ((inode_no - 1) / process->sb->s_inodes_per_group));
    block_size = BASE_OFFSET << (process->sb->s_log_block_size);

	read_gd = pread(process->fd, group_desc, sizeof(struct ext2_group_desc), g_desc_offset);
	if (0 > read_gd)
	{
		return -1;
	}
	return 0;
}

void EXT2PrintGroupDescriptor(handle_t *process, inode_t inode_no)
{
	struct ext2_group_desc group;
	int read_val = read_group_descriptor(process, inode_no, &group);
	if (0 > read_val)
	{
		return;
	}
	printf("group #: %ld \n", ((inode_no - 1) / process->sb->s_inodes_per_group));
	printf("%s%u \n", "blocks bitmap at: ", group.bg_block_bitmap);
	printf("%s%u \n", "inodes bitmap at: ", group.bg_inode_bitmap);
	printf("%s%u \n", "inode table at: ", group.bg_inode_table);
	printf("%s%u \n", "free blocks: ", group.bg_free_blocks_count);
	printf("%s%u \n", "free inodes: ", group.bg_free_inodes_count);
	printf("%s%u \n", "used directories: ", group.bg_used_dirs_count);
}
 

/* 
approved by Mr. Evanov.M
 */
 
int EXT2Chmod(handle_t *process, inode_t file_inode, size_t new_mod)
{
    int i = 0;
    struct ext2_inode inode = {0};
    size_t temp_new_mod = 0;

    unsigned short s_bits = 0 , u_bits = 0, g_bits = 0, o_bits = 0;

/* if octal value verification is required it's possible to check each value before deviding */
    o_bits |= (new_mod % 10);    
    new_mod /= 10;
    g_bits |= (new_mod % 10);
    new_mod /= 10;
    u_bits |= (new_mod % 10);
    new_mod /= 10;
    
    if(new_mod != 0)
    {
      s_bits |= (new_mod % 10);
    }
 
    if(-1 == GetInodeStruct(process, &inode, file_inode))
    {
        return -1;
    }
    
    /* zero all 12 leftmost bits */
    inode.i_mode >>= 12;
    
    inode.i_mode <<= 3;
    inode.i_mode |= s_bits;
    inode.i_mode <<= 3;
    inode.i_mode |= u_bits;
    inode.i_mode <<= 3;
    inode.i_mode |= g_bits;
    inode.i_mode <<= 3;
    inode.i_mode |= o_bits;

    if( -1 == SetInodeStruct(process, &inode, file_inode) )
    {
        return -1;
    }
    
    return 0;
} 