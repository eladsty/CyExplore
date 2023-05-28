#ifndef __EXT2_H_CR4__ 
#define __EXT2_H_CR4__ 

#include <stddef.h> /* size_t */

typedef struct process handle_t;
typedef long inode_t;
/* 
 * Description : EXT2Open opens a process in a device's ext2 filesystem. 	
 * Arguments : device - device path name.
 * Return : pointer to process handler, NULL if an error occured.
 * Time Complexity : O(n)
 * Space Complexity : O(1)
 */
handle_t *EXT2Open(char *device);
/* 
 * Description : EXT2Close closes a process opened at EXT2Open.
 * Arguments : process - handler recieved when user call EXT2Open.
 * Return : 0 for success, non-zero for failure
 * Time Complexity : O(1)
 * Space Complexity : O(1)
 */
int EXT2Close(handle_t *process);
/* 
 * Description : EXT2GetFileDescriptor returns a file descriptor to user in 
 * read-write mode
 * Arguments : process - pointer to handler returned by EXT2Open, file_path
 * - complete fila path originating in fs root directory.
 * Return : file descriptor in read-write mode. negative integer indicates an 
 * error
 * Time Complexity : O(n)
 * Space Complexity : O(1)
 */
inode_t EXT2GetFileDescriptor(handle_t *process, char *file_path);

/* 
 * Description : EXT2ReadBytes reads n bytes from a file into a user buffer. 
 * Arguments : process - pointer to handler returned by EXT2Open, 
 * file_descriptor - returned by EXT2GetFileDescriptor, buffer - user 
 * destination buffer, nbytes - number of bytes to read from file.
 * Return : pointer to buffer, NULL if an error occured.
 * Time Complexity : O(n)
 * Space Complexity : O(1)
 */
void *EXT2ReadBytes(handle_t *process, inode_t file_descriptor, void *buffer, 
					size_t nbytes);
/* 
 * Description : EXT2GetFileSize returns a given file size.
 * Arguments : process - pointer to handler returned by EXT2Open, 
 * file_descriptor - returned by EXT2GetFileDescriptor.
 * Return : number of used bytes in a file.
 * Time Complexity : O(n)
 * Space Complexity : O(1)
 */
long EXT2GetFileSize(handle_t *process, inode_t file_descriptor);

/*
 * Description : EXT2PrintSuperblock prints the content of a device's superblock.	
 * Arguments : process - pointer to handler returned by EXT2Open.	
 * Return : if a valid superblock is found, this function will print it's 
 * content to user's stdout. if not, it will print an error massege.
 * Time Complexity : O(1)
 * Space Complexity : O(1)
 */
void EXT2PrintSuperblock(handle_t *process);

/*
 * Description : EXT2PrintGroupDescriptor prints the content of a file's group 
 * descriptor.	
 * Arguments : process - pointer to handler returned by EXT2Open, file_descriptor - returned by EXT2GetFileDescriptor.	
 * Return : if a valid group descriptor is found, this function will print it's content to stdout. if not, it will print an error massege.
 * Time Complexity : O(n)
 * Space Complexity : O(1)
 */
void EXT2PrintGroupDescriptor(handle_t *process, inode_t file_descriptor);

/*
 * Description : EXT2ChangeMode changes the file
       mode bits of each given file according to mode, which can be either  a  symbolic
       representation  of changes to make, or an octal number representing the bit pat‐
       tern for the new mode bits.
 * Arguments : req_change is either zero or more letters from the set rwxXst, or a single letter from the set
       ugo. Multiple symbolic modes can be given, separated by commas. 
	  -The user who owns it (u), other users in the file's group (g), other
       users not in the file's group (o), or all users  (a).   If  none  of  these  are
       given,  the  effect  is as if (a) were given. 
	-The operator + causes the selected file mode bits to be added  to  the  existing
       file  mode  bits of each file; - causes them to be removed; and = causes them to
       be added and causes unmentioned bits to be removed except that a directory's un‐
       mentioned set user and group ID bits are not affected.
	-read (r), write (w), execute (or search for directories) (x), execute/search only if the file is
       a  directory  or  already  has execute permission for some user (X), set user or
       group ID on execution (s), restricted deletion flag or sticky bit (t).   Instead
       of one or more of these letters, you can specify exactly one of the letters ugo:
       the permissions granted to the user who  owns  the  file  (u),  the  permissions
       granted  to other users who are members of the file's group (g), and the permis‐
       sions granted to users that are in neither of the two preceding categories (o).
	-A numeric mode is from one to four octal digits (0-7), derived by adding up  the
       bits  with  values 4, 2, and 1.  Omitted digits are assumed to be leading zeros.
       The first digit selects the set user ID (4) and set group ID (2) and  restricted
       deletion or sticky (1) attributes.  The second digit selects permissions for the
       user who owns the file: read (4), write (2), and execute (1); the third  selects
       permissions  for  other users in the file's group, with the same values; and the
       fourth for other users not in the file's group, with the same values.
 * Return : 
 * Time Complexity : O(n)
 * Space Complexity : O(1)
 */

int EXT2ChangeMode(handle_t *process, inode_t inode_no, size_t req_change);

#endif /* __EXT2_H_CR4__ */
