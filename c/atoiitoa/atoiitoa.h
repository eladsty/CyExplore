#ifndef __ATOIITOA_H__CR4
#define __ATOIITOA_H__CR4

#include <assert.h>

/*integer to string tested up to base 36*/
char* Itoa(int num, char* str, int base);

/*string to integer*/
int Atoi(const char *str);

/* convert string to number up to base*/
int Atoi36(const char *str, int base);

/* compares output of Atoi to atoi */
int AtoiVsAtoi(const char *str);

/* compares output of Atoi and atoi with test cases included */
int TestAtoi();

/*  return only letters that appear on first 2 arrays but not on the third */
char *InTwoOutOfThree(char arr1[], char arr2[], char arr3[]);


#endif
