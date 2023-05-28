#ifndef __LOGGER_H_CR4__ 
#define __LOGGER_H_CR4__ 

#include <stdio.h> /* Used for printing functions */
#include <stdlib.h> /* Used for malloc and free functions */
#include <stddef.h> /* Used for size_t type */
#include <string.h> /* Used for string functions */
#include <assert.h> /* Used for assert function */

/* 
 * Description : write to logger	
 * Arguments : path to file, message to write	
 * Return : success/fail
 * Time Complexity :
 * Space Complexity :
 */
int WriteToLogger(char *path, char *message);

#endif /* __LOGGER_H_CR4__ */
