#ifndef __RECURSION_H_CR4__ 
#define __RECURSION_H_CR4__

#include "stack.h"

 struct Node
{
    int x;
    struct Node *next;
};

typedef struct Node Node;
 
 

int FibonacciIteratively(int element_index);
int FibonacciRecursively(int element_index);
Node *FlipList(Node *node);
size_t StrLenRecursive(const char *str);

/*compare 2 strings if equal return 0 else return other int(difference)*/
int  StrCmpRecursive(char *str1, char *str2);

char *StrCpyRecursive(char *dest, const char *src);
char *StrCatRecursive(char *destination, const char *source);
char *StrStrRecursive(const char *haystack, const char *needle);
void SortStack(stack_t *stack);


#endif /* __RECURSION_H_CR4__ */
