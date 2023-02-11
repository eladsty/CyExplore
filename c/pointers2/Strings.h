
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

/* concatenates strings*/
char *Strcat(char *destination, const char *source);

/* find first occurence of needle*/
char *StrStr(const char *haystack, const char *needle);

/* return size of the matching characters from the letters banks*/
size_t StrSpn(const char *str1, const char *charactersToMatch);

/* check if a string is a palindrom, 0 means false, 1 means true*/
int IsPalindrome(const char *str);

