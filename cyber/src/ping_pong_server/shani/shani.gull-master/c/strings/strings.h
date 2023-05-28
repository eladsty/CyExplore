#ifndef __STRINGS_H__
#define __STRINGS_H__

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>



int StrCmp(const char *arr1, const char *arr2);
size_t StrLen(const char *arr);
char *StrCpy(char *dest, const char *origin);
char *StrnCpy(char *dest, const char *origin, size_t n);
int ToLower(char c);
int StrCaseCmp(const char *arr1, const char *arr2);
int StrnCmp(const char *arr1, const char *arr2, size_t n);
char *StrChr(const char *arr, int c);
char *StrDup(const char *arr);
char *StrCat(char *dest, const char *origin);
char *StrnCat(char *dest, const char *origin, size_t n);
char *StrStr(const char *haystack, const char *needle);
size_t StrSpn(const char *s, const char *accept);
int strcmptest(const char *arr1, const char *arr2);


#endif
