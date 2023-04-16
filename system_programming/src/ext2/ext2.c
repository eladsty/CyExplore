
 #include <unistd.h>/* read */

#include "/home/elad/elad.shem-tov/system_programming/include/ext2.h"
#include "/home/elad/elad.shem-tov/system_programming/include/ext2_linux.h"
 
 struct session_handler 
{
    struct ext2_super_block *sb;
};

/* struct process
{

};  
 */

/* handle_t *EXT2Open(char *device)
{
    char buff[4097] = {0};
    fd = open("/dev/ram0", O_RDWR);
    lseek(fd, 1024, SEEK_SET);

    read(fd, buff, 4097);
    printf("%s\n", buff);
    close(buff);
}

  */