#include <stddef.h>
#include <stdio.h>

int main(void)
{
 	size_t block_size = 12;
    size_t block_count = 10;
    printf("%ld\n", FSASuggestSize(block_size, block_count)); 
 
	return 0;
}

