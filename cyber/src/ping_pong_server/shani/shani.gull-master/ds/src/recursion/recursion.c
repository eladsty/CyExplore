#include "../../include/stack/stack.h"
#include "../../include/recursion/recursion.h"

#define MAX2(a, b) (a < b) ? b : a
#define MIN2(a, b) (a > b) ? b : a

int c = 0;

static int AddTwo(int a, int b, int n)
{
	if (!n)
	{
		return c;
	}
	c = a + b;
	return AddTwo(b, c, (n - 1));
}

/* Status : approved
 * Reviewer : Ran
 * Description : returns the Fibonacci value of a given index
 * Arguments : int index
 * Return : the value of Fibonacci number at given index
 */
int FibonacciRecursively(int element_index)
{
	int zero = 0;
	int one = 1;
	if (element_index < 2)
	{
		return element_index == zero ? 0 : 1;
	}
	else
	{
		return AddTwo(zero, one, (element_index - 1));
	}
}
int FibonacciIteratively(int element_index)
{
	int i = 2;
	int n = 0;
	int n_plus_one = 1;
	int result = n + n_plus_one;
	if (0 == element_index)
	{
		return 0;
	}
	while (i < element_index)
	{
		n = n_plus_one;
		n_plus_one = result;
		result = n + n_plus_one;
		++i;
	}
	return result;
}

node_t *Reverse(node_t *current, node_t *next_node)
{
	node_t *reserve = next_node->next;
	next_node->next = current;
	while (NULL != reserve)
	{
		return Reverse(next_node, reserve);
	}
	return next_node;
}

/* Status : approved
 * Reviewer : Nimrod
 * Description : flips the order of nodes in a linked list
 * Arguments : 	head node iterator
 * Return :  new head node iterator
 */
node_t *FlipList(node_t *node)
{
	node_t *next_node = node->next;
	node->next = NULL;
	return Reverse(node, next_node);
}

int StackCheckAndSwap(int value, stack_t *stack, int flag)
{
	int pop = *(int *)StackPeek(stack);
	int push = MAX2(value, pop);
	StackPop(stack);
	if (pop < value)
	{
		++flag;
	}
	if (!StackIsEmpty(stack))
	{

		StackCheckAndSwap(push, stack, flag);
		push = MIN2(pop, value);
	}
	else if (StackIsEmpty(stack))
	{
		StackPush(stack, &push);
		push = MIN2(pop, value);
	}
	StackPush(stack, &push);
	return flag;
}
/* Status : approved
 * Reviewer : Adi
 * Description : sorts an unsorted stack, recursively.
 * Arguments :
 * Return :
 */
void SortStack(stack_t *stack)
{
	int flag = 0;
	int pop = *(int *)StackPeek(stack);
	StackPop(stack);
	if (StackCheckAndSwap(pop, stack, flag))
	{
		SortStack(stack);
	}
	return;
}

/* Status : approved
 * Reviewer : Nimrod
 * Description : prints the length of a string not including null terminator.
 * Arguments : pointer to string
 * Return :  length of string.
 */
size_t StrLenRecursive(const char *str)
{
	if ('\0' == *str)
	{
		return 0;
	}
	return StrLenRecursive(++str) + 1;
}

/* Status : approved
 * Reviewer : Nimrod
 * Description : compares the two strings s1 and s2.
 * Arguments : pointer to strings
 * Return :  functions return an integer less than, equal to, or
	   greater than zero if s1 (or the first n bytes thereof) is found to be less than, to match, or be greater than s2.
 */
int StrCmpRecursive(const char *s1, const char *s2)
{
	if (*s1 != *s2 && '\0' != *s1)
	{
		return (*s1 - *s2);
	}
	return StrCmpRecursive(++s1, ++s2);
	;
}

/* Status : approved
 * Reviewer : Nimrod
 * Description : copies the string pointed to by src, including the termi‐
	   nating null byte ('\0'), to the buffer pointed to by dest. The strings
	   may not overlap,  and  the  destination string dest must be large
	   enough to receive the copy.
 * Arguments : pointer to strings
 * Return :  a pointer to the destination string.
 */
char *StrCpyRecursive(char *dest, const char *src)
{
	if ('\0' != *src)
	{
		*dest = *src;
		StrCpyRecursive(++dest, ++src);
	}
	else
	{
		*dest = '\0';
		return dest;
	}
	--dest;
	return dest;
}

/* Status : approved
 * Reviewer : Nimrod
 * Description : appends the src string to the dest string, overwriting
	   the terminating null byte ('\0') at the end of dest, and then adds
	   a terminating null byte.
 * Arguments : pointer to strings
 * Return :  a pointer to the destination string.
 */
char *StrCatRecursive(char *dest, const char *src)
{
	if ('\0' != *dest)
	{
		++dest;
		StrCatRecursive(dest, src);
	}
	else if ('\0' != *src)
	{
		StrCpyRecursive(dest, src);
	}
	--dest;
	return dest;
}

/* Status : approved
 * Reviewer : Nimrod
 * Description : finds the first occurrence of the substring needle in the
				string haystack. The terminating null bytes ('\0') are not compared.
 * Arguments : pointer to strings
 * Return : pointer to the beginning of the located substring, or NULL if the
			  substring is not found.
 */
char *StrStrRecursive(const char *haystack, const char *needle)
{
	size_t counter = 0;
	char *tmp = (char *)needle;
	if ('\0' == *haystack)
	{
		return NULL;
	}
	do
	{
		++counter;
		tmp += 1;
	} while ('\0' != *tmp); 
	if (!strncmp(haystack, needle, counter))
	{
		return (char *)haystack;
	}
	return StrStrRecursive(((char *)haystack + 1), needle);
}
