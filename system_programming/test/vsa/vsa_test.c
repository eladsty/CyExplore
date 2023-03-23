#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/vsa.h"

#define ALIGNEDUP(address) (((address) + (WORD - 1)) & ~(WORD - 1))
#define WORD sizeof(size_t)
#define SVSA sizeof(vsa_t) /*  size of managment struct */


int main(void)
{
    vsa_t *newpool = NULL;
    void *memory_p = NULL;
    size_t memory_size = 0, i = 0, tests = 0, char_mem_size = 0;
    char *pointers[10];
    char s[][100] = {"shlomke lazar ", "liraz sheliii", "the love 0f my life libyy",
                     "I love varible size allocation lists :)", "libyyyyyyyy ",
                     "I should go have fun!!", "One day we will make plenty of money :)))", "Approved?  you Wish!", "If you copy my tests and failed them, you only got yourself to blame - NOT MY TESTS!!"};

    
    tests = sizeof(s) / sizeof(s[0]);
    
    for (i = 0; i < tests; i++) 
	{
    	memory_size += ALIGNEDUP(strlen(s[i]) + WORD);
    }
    
    memory_size += (WORD * 2);
    
    memory_p = (vsa_t *)malloc(memory_size);
    newpool = VSAInit(memory_p, (memory_size));
	
	printf("VSA Largest Block Available size is --> %ld\n\n\n", VSALargestBlockAvailable(newpool)); 
	
	for (i = 0; i < tests; i++) 
	{
		char_mem_size = strlen(s[i]) + 1;
		pointers[i] = (char *)VSAAlloc(newpool, (char_mem_size));
		memcpy(pointers[i], s[i], char_mem_size);
		printf("VSA Largest Block Available size is --> %ld\n", VSALargestBlockAvailable(newpool));
	}

	for (i = 0; i < tests; i++) 
	{
		printf("%s\n", pointers[i]);
	}
	
	VSAFree(pointers[1]);
	VSAFree(pointers[3]);
	VSAFree(pointers[4]);
	printf("\n\ntest --> VSA Largest Block after freeing blocks of memory \n\n");
	printf("VSA Largest Block Available size is --> %ld\n", VSALargestBlockAvailable(newpool));	
	
	memory_p = ((char *)memory_p);
	free(memory_p);

    return 0;
}


















