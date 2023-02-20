#ifndef __STRUCT_H__CR4
#define __STRUCT_H__CR4
#include <stdio.h> /* sprintf and print */
#include <stdlib.h> /* malloc  and free */
#include <string.h> /* strlen */

/* Status: READY;
 * Reviewer: Hen 
 * Description:  
 * Return : maximum number and size of var and size of type
 */
#define MAX2(a,b) a > b ? a : b
 
#define MAX3(a,b,c) ( MAX2(a,b) > c?  MAX2(a,b) :c)

#define SIZEOF_VAR(var) (size_t)(&var+1) - (size_t)&var

#define SIZEOF_TYPE(var) (size_t)(((var*)0)+1)
 struct X 
 {
  	double d;
 	int i;
 	short s;
 	char c;
 
 };

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

union car 
 	{
 		char name[49];
 		double price;
 	};
 	
 	
#endif

