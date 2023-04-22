
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>


#include "/home/elad/elad.shem-tov/system_programming/include/ext2.h"
#include "/home/elad/elad.shem-tov/system_programming/include/ext2_linux.h"

int main()
{
    handle_t *process = NULL;
    size_t fd = 0;
    char buffer[100];
    process = EXT2Open("/dev/ram0");
    fd = EXT2GetFileDescriptor(process , "/elad1");

    printf("size of file is %ld\n", EXT2GetFileSize(process ,fd));

    EXT2ReadBytes(process, fd, buffer, 30);
    EXT2PrintSuperblock(process);
    printf("%s", buffer);
    EXT2PrintGroupDescriptor(process, fd);
 
    EXT2Chmod(process, fd, 3666);
     
    EXT2Close(process);
    return 0;
}