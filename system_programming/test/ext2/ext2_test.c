
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>


#include "/home/elad/elad.shem-tov/system_programming/include/ext2.h"
#include "/home/elad/elad.shem-tov/system_programming/include/ext2_linux.h"

int main()
{
    char buff[4096] = {0};
    inode_t fd = open("/dev/ram0", O_RDWR);
    lseek(fd, 1024, SEEK_SET);
     
    read(fd, buff, 4096);
    printf("%s\n", buff);
    
    



    close(fd);
    return 0;
}