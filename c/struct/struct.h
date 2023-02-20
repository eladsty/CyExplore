#ifndef __STRUCT_H__CR4
#define __STRUCT_H__CR4
#include <stdio.h> /* sprintf and print */
#include <stdlib.h> /* malloc  and free */
#include <string.h> /* strlen */


 

typedef struct check
{
	void *p;
	void(*add)(int x, void **p);
	void(*print)(void *p);
	void(*cleanup)(void *p);
}check;

	int IntLen(int x);

	/* Add */
	void AddInt(int x, void **p);
	void AddFloat(int x, void **p);
	void AddStr(int x, void **p);

	/* Print */
	void PrintInt(void *p);
	void PrintFloat(void *p);
	void PrintStr(void *p);

	/* Cleanup */
	void CleanStr(void *p);


#endif
