#ifndef __RECURSION_H_CR4__
#define __RECURSION_H_CR4__

#include <stdio.h> /* Used for printing functions */

#include <stddef.h> /* Used for size_t type */
#include <string.h> /* Used for string functions */
#include <assert.h> /* Used for assert function */
typedef struct node node_t;
struct node
{
	node_t *next;
};
/* returns the Fibonacci value of a given index */
int FibonacciRecursively(int element_index);
int FibonacciIteratively(int element_index);
/* flips the order of a linked list */
node_t *FlipList(node_t *node);
/* returns string length */
size_t StrLenRecursive(const char *str);
/* compares two strings, returns positive, negative or 0
	if s1 is bigger, smaller or equal to s2 */
int StrCmpRecursive(const char *s1, const char *s2);
/* copies from src to dest */
char *StrCpyRecursive(char *dest, const char *src);
/* concatenate from src to dest */
char *StrCatRecursive(char *dest, const char *src);
/* finds needle in haystack NULL if didn't*/
char *StrStrRecursive(const char *haystack, const char *needle);
/* sorts unsorted stack */
void SortStack(stack_t *stack);
#endif /* __RECURSION_H_CR4__ */
