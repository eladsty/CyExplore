#ifndef __PROD_CONS_H_CR4__ 
#define __PROD_CONS_H_CR4__ 

#include <stdio.h> /* Used for printing functions */
#include <stdlib.h> /* Used for malloc and free functions */
#include <stddef.h> /* Used for size_t type */
#include <string.h> /* Used for string functions */
#include <assert.h> /* Used for assert function */

typedef void *(actionfunc_t)(void *);



/* 
 * Description : creates two threads, one produces numbers into a global array
					the other reads them and prints them.	
 * Arguments : void.	
 * Return : void. will print to stdout.
 * important : this program will allow up to and not including 300 threads.
 * Time Complexity : 
 * Space Complexity :
 */
void Ex1SingleProdCons(size_t ncycles, void *produce, actionfunc_t Actprod, actionfunc_t Actcons);
/* 
 * Description : 
	
 * Arguments : 
	
 * Return : 
 * important : this program will allow up to and not including 300 threads.
 * Time Complexity :
 * Space Complexity :
 */
void Ex2MultiProdCons(size_t nconsumer, size_t nproducer, size_t ncycles, char *produce, actionfunc_t ActConsumer);
/* 
 * Description : 
	
 * Arguments : 
	
 * Return :
 * important : this program will allow up to and not including 300 threads. 
 * Time Complexity :
 * Space Complexity :
 */
void Ex3MultiProdCons(size_t nconsumer, size_t nproducer, size_t ncycles, char *produce, actionfunc_t ActConsumer);
/* 
 * Description : 
	
 * Arguments : 
	
 * Return : 
 * important : this program will allow up to and not including 300 threads. 
 * Time Complexity :
 * Space Complexity :
 */
void Ex4FSQ(size_t nconsumer, size_t nproducer, size_t ncycles, size_t nbytes, char **produce, actionfunc_t ActConsumer);
/* 
 * Description : 
	
 * Arguments : 
	
 * Return : 
 * important : this program will allow up to and not including 300 threads.
 * Time Complexity :
 * Space Complexity :
 */
void Ex5FSQ(size_t nconsumer, size_t nproducer, size_t ncycles, size_t nbytes, char **produce, actionfunc_t ActConsumer);
/* 
 * Description : 
	
 * Arguments : 
	
 * Return : 
 * important : this program will allow up to and not including 300 threads.
 * Time Complexity :
 * Space Complexity :
 */
void Ex6Barrier(const size_t consumers, const size_t data_len, char **produce, const size_t ncycles, actionfunc_t *ActConsumer);
#endif /* __PROD_CONS_H_CR4__ */
