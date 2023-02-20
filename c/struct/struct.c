 
/* Status: READY;
 * Reviewer:  
 * Description:  
 * Return : void - none , int
 */


#include "struct.h"

int IntLen(int x)
{
	int len = 0;
	while(0 != x)
	{
		x /= 10;
		++len;
	}
	return len;
}



void AddInt(int x, void **p)
{
	**((int **)p) += x;
}

void AddFloat(int x, void **p)
{
	**((float **)p) += x;
}

void AddStr(int x, void **p)
{
	char *new_p;
    int length = IntLen(x);
    new_p = malloc(length + 1);
    sprintf(new_p, "%d" , x);
    *p = realloc(*p, strlen(*p) + length + 1);
    strcat(*p, new_p);
    free(new_p);
}

 

void PrintInt(void *p)
{
	printf("Int: %d\n", *((int *)p));
}

void PrintFloat(void *p)
{
	printf("Float: %f\n", *((float*)p));
}

void PrintStr(void *p)
{
	printf("String: %s\n", (char *)p);
}

void CleanStr(void *p)
{
	free(p);
}
 
  

 
 

