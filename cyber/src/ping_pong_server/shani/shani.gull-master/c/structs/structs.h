
#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include <stdlib.h> /* malloc */
#include <string.h> /* strcat */
#include <stdio.h> /* sprintf */

struct element 
	{
		void *pointer;
		void (*add)(void**, int);
		void (*print)(void*);
		void (*clean)(void*);
	};

void *CreateString(char *elm, int size);
void CleaUpStr(void *heap);
void CleaUpFlt(void *heap);
void CleaUpInt(void *heap);
void AddStr(void **elm, int n);
void AddFlt(void **elm, int n);
void AddInt(void **elm, int n);
void PrintStr(void *elm);
void PrintFlt(void *elm);
void PrintInt(void *elm);

/* #############################*/
/* # Ex.5                      #*/
/* # status: approved          #*/
/* # reviewer: Amir            #*/
/* # description: this macro   #*/
/* # will return the bigger var#*/
/* # return: max var           #*/
/* # special notes:            #*/
/* #############################*/
#define MAX2(a, b) (((a) > (b)) ? (a) : (b))

#define MAX3(a, b, c) ((MAX2(a, b) > (c)) ? MAX2(a, b) : (c))

/* #############################*/
/* # Ex.6                      #*/
/* # status: approved          #*/
/* # reviewer: Amir            #*/
/* # description: this macro   #*/
/* # will return the var size  #*/
/* # return: var size          #*/
/* # special notes:            #*/
/* #############################*/
#define SIZEOF_VAR(a) ((size_t)(&(a)+1) - (size_t)(&(a)))

/* #############################*/
/* # Ex.7                      #*/
/* # status: approved          #*/
/* # reviewer: Amir            #*/
/* # description: this macro   #*/
/* # will return the datatype  #*/
/* # size                      #*/
/* # return: datatype size     #*/
/* # special notes: (x*)0      #*/
/* # yields a null pointer.    #*/
/* #############################*/

#define SIZEOF_TYPE(x) (size_t)(((x*)0) + 1)
#endif
