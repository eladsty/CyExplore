
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wordboundary.h"
#include "assert.h"

int main()
{
char dest[19];
char str[] = "lkajshdlksjdfasdfa";
char str2[] = "lkajshdlksjdfasdfa";
char str3[] = "aaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnn";
char str4[40];
char c = 'e';
MemSet(str, c, 9);
printf("%s\n", str);


MemCpy(dest, str2, 10);
 

printf("%s\n", dest);


 


assert(0 == strcmp(memmove(str4 - 6, str3, 16) , MemMove(str4 - 6, str3, 16)));
 


return 0;
}
