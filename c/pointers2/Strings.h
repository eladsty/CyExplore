
#ifndef __POINTERS_H__
#define __POINTERS_H__

#include <stddef.h>

size_t Strlen(const char *str);
 
int StrCmp(const char *str1, const char *str2);

/* change to lower casing */
char ToLower(char l);

/* copy string*/
char *StrCpy(char* cpy, const char* str);

/*copy string by counter n - if n is larger than the string length fill with \0 */
char *StrnCpy(char* cpy, const char* str, size_t);

/*find first occurence of the substring in the main string*/
int StrnCmp(const char *str1, const char *str2, size_t n);

/*lower casing both strings and comparing them*/
int Strcasecmp (const char *str1, const char *str2);

/*lower casing both strings and comparing them*/
char *Strchr(const char *str, int c);

/* copy and return pointer to that copy*/
char *Strdup(const char *str);




#endif
