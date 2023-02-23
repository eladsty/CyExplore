#ifndef __ATOIITOA_H__CR4
#define __ATOIITOA_H__CR4

#include <assert.h>

/*integer to string tested up to base 36*/
char* Itoa(int num, char* str, int base);

/*string to integer*/
int Atoi(const char *str);

/* convert string to number up to base*/
int Atoi36(const char *str, int base);

#endif
