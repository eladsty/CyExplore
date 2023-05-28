#include <stdlib.h> /* malloc */
#include <string.h> /* strcat */
#include <stdio.h> /* sprintf */
#include "structs.h" /*linking*/


/* #############################*/
/* # Ex.1 - 4                  #*/
/* # status: approved          #*/
/* # reviewer: Adi             #*/
/* # description: this func    #*/
/* # will append int to str.   #*/
/* # return: ptr to str        #*/
/* # special notes:            #*/
/* #############################*/

void AddStr(void **elm, int n) /* recieve pointer to heap */
{
	char buffer[16];
	sprintf(buffer, "%d", n);
	*elm = (char*)realloc(*elm, (strlen(*elm) + strlen(buffer) + 1));
	strcat(*elm, buffer);
}

/* #############################*/
/* # Ex.1 - 4                  #*/
/* # status: approved          #*/
/* # reviewer: Adi             #*/
/* # description: this func    #*/
/* # will free dynamic ptr     #*/
/* # return: void              #*/
/* # special notes:            #*/
/* #############################*/
void CleaUpStr(void *heap)
{
	free(heap);
	heap = NULL;
}

void CleaUpFlt(void *heap){}

void CleaUpInt(void *heap){}

/* #############################*/
/* # Ex.1 - 4                  #*/
/* # status: approved          #*/
/* # reviewer: Adi             #*/
/* # description: this func    #*/
/* # will create str in heap   #*/
/* # return: ptr to str        #*/
/* # special notes:            #*/
/* #############################*/

void *CreateString(char *elm, int size) /* this func will be used by user to make a void *pointer for the first member of the struct */
{
	
	char *mem;
	mem = (char*)malloc(sizeof(char) * size);

	while ('\0' != *elm)
	{
		*mem = *elm;
		++elm, ++mem;	
	}
	
	*mem = '\0';
	mem -= --size;
	return (void*)mem;
}

/* #############################*/
/* # Ex.1 - 4                  #*/
/* # status: approved          #*/
/* # reviewer: Adi             #*/
/* # description: this func    #*/
/* # will print an int         #*/
/* # return: void              #*/
/* # special notes:            #*/
/* #############################*/

void PrintInt(void *elm)
{
	printf("%d\n", *(int*)elm);
}

/* #############################*/
/* # Ex.1 - 4                  #*/
/* # status: approved          #*/
/* # reviewer: Adi             #*/
/* # description: this func    #*/
/* # will print a float        #*/
/* # return: void              #*/
/* # special notes:            #*/
/* #############################*/

void PrintFlt(void *elm)
{
	printf("%f\n", *(float*)elm);
}

/* #############################*/
/* # Ex.1 - 4                  #*/
/* # status: approved          #*/
/* # reviewer: Adi             #*/
/* # description: this func    #*/
/* # will print a str          #*/
/* # return: void              #*/
/* # special notes:            #*/
/* #############################*/

void PrintStr(void *elm)
{
	printf("%s\n", (char*)elm);
}

/* #############################*/
/* # Ex.1 - 4                  #*/
/* # status: approved          #*/
/* # reviewer: Adi             #*/
/* # description: this func    #*/
/* # will add two ints         #*/
/* # return: void              #*/
/* # special notes:            #*/
/* #############################*/

void AddInt(void **elm, int n)
{
	*(int*)elm += n;
}

/* #############################*/
/* # Ex.1 - 4                  #*/
/* # status: approved          #*/
/* # reviewer: Adi             #*/
/* # description: this func    #*/
/* # will add int and float    #*/
/* # return: void              #*/
/* # special notes:            #*/
/* #############################*/

void AddFlt(void **elm, int n)
{
	*(float*)elm += n;
}

