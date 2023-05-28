#ifndef __SIGNAL_H_CR4__ 
#define __SIGNAL_H_CR4__ 

#include <stdio.h> /* Used for printing functions */
#include <stdlib.h> /* Used for malloc and free functions */
#include <stddef.h> /* Used for size_t type */
#include <string.h> /* Used for string functions */
#include <assert.h> /* Used for assert function */


void ForkExecShell(char *command);

void SystemShell(char *command);

#endif /* __SIGNAL_H_CR4__ */
