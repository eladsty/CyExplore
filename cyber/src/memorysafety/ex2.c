#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
extern int LLVMFuzzerTestOneInput(const char *Data, size_t Size)
{
    char *buffer = calloc(64, Size);

    if (!buffer) {
        printf("Allocation failed\n");
        return -1;
    }

    strncpy(buffer, Data, Size);
    
    free(buffer);
    buffer = NULL;
    return 0;
}




/*
1. don't provide another argument when opening the object file or overwrite the buffer size.
use any symbol


*/
