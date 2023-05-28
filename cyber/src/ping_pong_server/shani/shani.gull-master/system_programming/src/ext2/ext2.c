#define _XOPEN_SOURCE 500				   /* pread macro requirments */
#define _POSIX_C_SOURCE 200809L			   /* pread macro requirments */
#include <fcntl.h>						   /* open */
#include <stdio.h>						   /*printf */
#include <sys/stat.h>					   /* S_ISDIR */
#include <sys/types.h>					   /* lseek */
#include <unistd.h>						   /* lseek */
#include <stdlib.h>						   /* malloc */
#include <string.h>						   /* strcpy */
#include <time.h>						   /* to print timr stamps */
#include "../../include/ext2/ext2_linux.h" /* ext2 lib */
#include "../../include/ext2/ext2.h"	   /* il-api functions */

#define MIN2(a, b) ((a) > (b) ? (b) : (a))
#define FREE_MEMORY(ptr) \
	{                    \
		free(ptr);       \
		(ptr) = NULL;    \
	} /* freeing malloced ptr */
#define SUID 04000
#define SGID 02000
#define SVTX 01000
#define RUSR 00400
#define WUSR 00200
#define XUSR 00100
#define RGRP 00040
#define WGRP 00020
#define XGRP 00010
#define ROTH 00004
#define WOTH 00002
#define XOTH 00001
#define ALLM 07777 /* all octal mode bits */
#define MASK(x) (((x) >> 12) << 12)

/* sugercode the structs */
typedef struct ext2_super_block superblock_t;
typedef struct ext2_group_desc groupd_t;
typedef struct ext2_inode inode_struct_t;
typedef struct ext2_dir_entry_2 directory_entry;
typedef unsigned short int imode_t;

struct process
{
	superblock_t superblock;
	size_t file_descriptor;
	unsigned int block_size;
};

static char *isolate_file_name_from_path(char *dest, char *src);
static int read_group_descriptor(handle_t *process, inode_t inode_no, groupd_t *group_desc);
static int read_inode(handle_t *process, inode_t inode_no, inode_struct_t *inode);
static int read_dir(handle_t *process, inode_t ino, char *file_name);

/* Status : approved
 * Reviewer : Alon
 * Description : open file descriptor and read from superblock to handle.
 * Arguments : device path.
 * Return : handler, or NULL if something failed.
 */
handle_t *EXT2Open(char *device)
{
	int fd = 0, read_fd = 0;
	handle_t *handle = (handle_t *)malloc(sizeof(handle_t));
	if (NULL == handle)
	{
		return NULL;
	}
	if (0 > (fd = open(device, O_RDWR)))
	{
		FREE_MEMORY(handle);
		return NULL;
	}
	read_fd = pread(fd, &handle->superblock, sizeof(superblock_t),
					EXT2_MIN_BLOCK_SIZE);
	if (0 > read_fd)
	{
		FREE_MEMORY(handle);
		close(fd);
		return NULL;
	}
	handle->block_size = EXT2_BLOCK_SIZE(&handle->superblock);
	handle->file_descriptor = fd;
	return handle;
}
/* Status : approved
 * Reviewer : Alon
 * Description : close file descriptor and frees malloced managing structs.
 * Arguments : handle pointer
 * Return : 0 success, non-zero fail.
 */

int EXT2Close(handle_t *process)
{
	int ret = close(process->file_descriptor);
	FREE_MEMORY(process);
	return ret;
}
/* helpers to EXT2GetFileDescriptor */
/* isolate path directories */
static char *isolate_file_name_from_path(char *dest, char *src)
{
	int i = 0;
	for (i = 0; '/' != *src && '\0' != *src; ++i)
	{
		dest[i] = *src;
		++src;
	}
	dest[i] = '\0';
	return src;
}
/* read a group descriptor to a buffer */
static int read_group_descriptor(handle_t *process, inode_t inode_no, groupd_t *group_desc)
{
	int read_gd;
	read_gd = pread(process->file_descriptor, group_desc, sizeof(groupd_t),
					process->block_size + (process->block_size * ((inode_no - 1) /
																  process->superblock.s_inodes_per_group)));
	if (0 > read_gd)
	{
		return -1;
	}
	return 0;
}
/* read an inode to a buffer */
static int read_inode(handle_t *process, inode_t inode_no, inode_struct_t *inode)
{
	int valid = -1;
	groupd_t group_desc;
	valid = read_group_descriptor(process, inode_no, &group_desc);
	if (0 > valid)
	{
		return -1;
	}
	valid = pread(process->file_descriptor, inode,
				  sizeof(inode_struct_t), (group_desc.bg_inode_table * process->block_size) + ((inode_no - 1) * process->superblock.s_inode_size));
	return valid;
} /* reads inode by inode number */
/* read directory entries to a buffer */
static int read_dir(handle_t *process, inode_t ino, char *file_name)
{
	int inode_no;
	void *block;
	ssize_t file_size;
	inode_struct_t inode;
	directory_entry *entry;
	read_inode(process, ino, &inode);
	file_size = inode.i_size;
	if ((block = malloc(file_size + 1)) == NULL)
	{
		return -1;
	}
	EXT2ReadBytes(process, ino, block, file_size);
	entry = (directory_entry *)block;
	while (0 != entry->inode)
	{
		if (!strncmp(entry->name, file_name, entry->name_len))
		{
			inode_no = entry->inode;
			FREE_MEMORY(block);
			return inode_no;
		}
		entry = (directory_entry *)((char *)entry + entry->rec_len);
	}
	FREE_MEMORY(block);
	return -1;
}
/* Status : approved
 * Reviewer : Alon
 * Description : returns file descriptor of a file.
 * Arguments : file path, process handler.
 * Return : file descriptor, negative integer for error.
 */
inode_t EXT2GetFileDescriptor(handle_t *process, char *file_path)
{
	inode_t inode_number = EXT2_ROOT_INO;
	char *current_path = file_path;
	char path_temp[EXT2_NAME_LEN];
	/* read through the path finding the destination inode */
	while ('\0' != *current_path)
	{
		current_path += 1;
		current_path = isolate_file_name_from_path(path_temp, current_path);
		if (0 > (inode_number = read_dir(process, inode_number, path_temp)))
		{
			return -1;
		}
	}
	return inode_number;
}
/* Status : approved
 * Reviewer : Alon
 * Description : reads byte file into a buffer
 * Arguments : buffer needs to be big enough for file
 * Return : pointer to user buffer
 */
void *EXT2ReadBytes(handle_t *process, inode_t inode_no, void *buffer,
					size_t nbytes)
{
	int read_validator = -1;
	size_t i = 0;
	inode_struct_t inode;
	size_t bytes_to_read;
	size_t bytes_read = 0;
	read_validator = read_inode(process, inode_no, &inode);
	if (0 > read_validator)
	{
		return NULL;
	}

	while (0 < inode.i_block[i] && i < 12)
	{
		bytes_to_read = MIN2(nbytes, process->block_size);
		read_validator = pread(process->file_descriptor, (char *)buffer + bytes_read, bytes_to_read,
							   (inode.i_block[i] * process->block_size));
		if (0 > read_validator)
		{
			return NULL;
		}
		++i;
		nbytes -= bytes_to_read;
		bytes_read += bytes_to_read;
	}
	return buffer;
}
/* Status : approved
 * Reviewer : Alon
 * Description : find a file's size
 * Arguments : handler and an inode number
 * Return : size of a file in bytes or -1 if error
 */
long EXT2GetFileSize(handle_t *process, inode_t inode_no)
{
	inode_struct_t inode;
	int read_validator = -1;
	long size = -1;
	read_validator = read_inode(process, inode_no, &inode);
	if (0 > read_validator)
	{
		return -1;
	}
	size = inode.i_size;
	return size;
}
/* Status : approved
 * Reviewer : Alon
 * Description : prints super block content to terminal
 * Arguments : handler pointer
 * Return : nothing
 */
void EXT2PrintSuperblock(handle_t *process)
{
	int i;
	time_t stamp;
	char categories[40][255] = {"Filesystem volume name: ",
								"Last mounted on: ",
								"Filesystem UUID: ",
								"Filesystem magic number: ",
								"Filesystem revision #: ",
								"Filesystem features: ",

								"Filesystem state: ",
								"Errors behavior: ",
								"Filesystem OS type: ",
								"Inode count: ",
								"Block count: ",
								"Reserved block count: ",
								"Free blocks: ",
								"Free inodes: ",
								"First block: ",
								"Block size: ",
								"Fragment size: ",
								"Blocks per group: ",
								"Fragments per group: ",
								"Inodes per group: ",
								"Last mount time: ",
								"Last write time: ",
								"Mount count: ",
								"Maximum mount count: ",
								"Last checked: ",
								"Check interval: ",
								"Reserved blocks uid: ",
								"Reserved blocks gid: ",
								"First inode: ",
								"Inode size: "};

	printf("%s%s \n", categories[0], process->superblock.s_volume_name);
	printf("%s%s \n", categories[1], process->superblock.s_last_mounted);
	printf("%s%x", categories[2], process->superblock.s_uuid[0]);
	for (i = 1; i < 16; ++i)
	{
		printf("%x", process->superblock.s_uuid[i]);
	}
	printf("\n");
	printf("%s0x%X \n", categories[3], process->superblock.s_magic);
	printf("%s%u \n", categories[4], process->superblock.s_rev_level);
	printf("%s%u %u %u \n", categories[5],
		   process->superblock.s_feature_ro_compat,
		   process->superblock.s_feature_compat,
		   process->superblock.s_feature_incompat);
	printf("%s%s \n", categories[6], (process->superblock.s_state) ? "unknown" : "not-clean");
	printf("%s%s \n", categories[7], (process->superblock.s_errors) ? "continue" : "unknown");
	printf("%s%s \n", categories[8], (process->superblock.s_creator_os) ? "unknown" : "Linux");
	printf("%s%u \n", categories[9], process->superblock.s_inodes_count);
	printf("%s%u \n", categories[10], process->superblock.s_blocks_count);
	printf("%s%u \n", categories[11], process->superblock.s_r_blocks_count);
	printf("%s%u \n", categories[12], process->superblock.s_free_blocks_count);
	printf("%s%u \n", categories[13], process->superblock.s_free_inodes_count);
	printf("%s%u \n", categories[14], process->superblock.s_first_data_block);
	printf("%s%u \n", categories[15], EXT2_BLOCK_SIZE(&process->superblock));
	printf("%s%d \n", categories[16], EXT2_FRAG_SIZE(&process->superblock));
	printf("%s%u \n", categories[17], process->superblock.s_blocks_per_group);
	printf("%s%u \n", categories[18], process->superblock.s_frags_per_group);
	printf("%s%u \n", categories[19], process->superblock.s_inodes_per_group);
	stamp = process->superblock.s_mtime;
	printf("%s%s", categories[20], asctime(gmtime(&stamp)));
	stamp = process->superblock.s_wtime;
	printf("%s%s", categories[21], asctime(gmtime(&stamp)));
	printf("%s%u \n", categories[22], process->superblock.s_mnt_count);
	printf("%s%d \n", categories[23], process->superblock.s_max_mnt_count);
	stamp = process->superblock.s_lastcheck;
	printf("%s%s", categories[24], asctime(gmtime(&stamp)));
	printf("%s%u \n", categories[25], process->superblock.s_checkinterval);
	printf("%s%u \n", categories[26], process->superblock.s_def_resuid);
	printf("%s%u \n", categories[27], process->superblock.s_def_resgid);
	printf("%s%u \n", categories[28], process->superblock.s_first_ino);
	printf("%s%u \n", categories[29], process->superblock.s_inode_size);
}
/* Status : approved
 * Reviewer : Alon
 * Description : prints group descriptor content to terminal
 * Arguments : handle pointer and inode number
 * Return : nothing
 */
void EXT2PrintGroupDescriptor(handle_t *process, inode_t inode_no)
{
	groupd_t group;
	int read_val = read_group_descriptor(process, inode_no, &group);
	if (0 > read_val)
	{
		return;
	}
	printf("group #: %ld \n", ((inode_no - 1) /
							   process->superblock.s_inodes_per_group));
	printf("%s%u \n", "blocks bitmap at: ", group.bg_block_bitmap);
	printf("%s%u \n", "inodes bitmap at: ", group.bg_inode_bitmap);
	printf("%s%u \n", "inode table at: ", group.bg_inode_table);
	printf("%s%u \n", "free blocks: ", group.bg_free_blocks_count);
	printf("%s%u \n", "free inodes: ", group.bg_free_inodes_count);
	printf("%s%u \n", "used directories: ", group.bg_used_dirs_count);
}
/* helpers to chmod */
static size_t decimal_to_octal(size_t decimal)
{
	imode_t octal = 0;
	int i = 0, remainder = 0;

	while (decimal != 0)
	{
		/* decimals remainder is calculated */
		remainder = decimal % 8;

		/* storing the octalvalue */
		octal += remainder * i;

		/* storing exponential value */
		i *= 10;
		decimal /= 8;
	}
	return octal;
}
static size_t octal_to_decimal(size_t octal)
{
	int decimal = 0;
	int base = 1;
	int temp;
	while (octal)
	{

		temp = octal % 10;
		octal = octal / 10;
		decimal += temp * base;
		base = base * 8;
	}
	return decimal;
}
static imode_t octal_to_mode(imode_t octal)
{
	/* Help the compiler optimize the usual case where mode_t uses
	   the traditional octal representation.  */
	return ((S_ISUID == SUID && S_ISGID == SGID && S_ISVTX == SVTX && S_IRUSR == RUSR && S_IWUSR == WUSR && S_IXUSR == XUSR && S_IRGRP == RGRP && S_IWGRP == WGRP && S_IXGRP == XGRP && S_IROTH == ROTH && S_IWOTH == WOTH && S_IXOTH == XOTH)
				? octal
				: (mode_t)((octal & SUID ? S_ISUID : 0) | (octal & SGID ? S_ISGID : 0) | (octal & SVTX ? S_ISVTX : 0) | (octal & RUSR ? S_IRUSR : 0) | (octal & WUSR ? S_IWUSR : 0) | (octal & XUSR ? S_IXUSR : 0) | (octal & RGRP ? S_IRGRP : 0) | (octal & WGRP ? S_IWGRP : 0) | (octal & XGRP ? S_IXGRP : 0) | (octal & ROTH ? S_IROTH : 0) | (octal & WOTH ? S_IWOTH : 0) | (octal & XOTH ? S_IXOTH : 0)));
}
/* Status : approved
 * Reviewer : Nimrod
 * Description : changes file bit mode
 * Arguments : handle pointer, file name and requested mode change in an octal representation.
 * Return : 0 success, 1 fail.
 */
int EXT2ChangeMode(handle_t *process, inode_t inode_no, size_t req_change)
{
	inode_struct_t inode;
	int valid;
	imode_t base;
	imode_t mode;
	groupd_t group_desc;
	valid = read_inode(process, inode_no, &inode); /*for validation purpose*/
	if (0 > valid)
	{
		return 1;
	}
	valid = read_group_descriptor(process, inode_no, &group_desc); /*for validation purpose*/
	if (0 > valid)
	{
		return 1;
	}
	if (512 < req_change)
	{
		printf("%d\n", req_change);
		req_change = octal_to_decimal(req_change);
		printf("%d\n", req_change);
	}
	base = MASK(inode.i_mode); /* this is only type, no permissions */
	mode = base | octal_to_mode(req_change);
	valid = pwrite(process->file_descriptor, &mode, sizeof(imode_t),
				   (group_desc.bg_inode_table *
					process->block_size) +
					   ((inode_no - 1) *
						process->superblock.s_inode_size));
	return valid;
}
