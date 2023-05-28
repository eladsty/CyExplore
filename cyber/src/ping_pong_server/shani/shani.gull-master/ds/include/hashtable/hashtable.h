#ifndef __HASHTABLE_H_CR4__ 
#define __HASHTABLE_H_CR4__ 

#include <stddef.h> /* Used for size_t type */

typedef enum
{
	UP = 0,
	DOWN = 1
} resize; 

typedef int(*compfunc_t)(const void *data, const void *param);
typedef size_t(*hashfunc_t)(void *data);
typedef struct hash hash_table_t;

/*
 * Description : HASHCreate creates a hash table that can store values according
 				to their respective keys	
 * Arguments : table_size is the amount of indexes the user would like 
 				to have in the table, HashFunction is the users has function and
				cmp is a user compare func used to compare values in the table
				to values from user.	
 * Return : returns pointer to the hash table, NULL if failed.
 * time complexity : O(n)
 * space complexity : O(n)
 */
hash_table_t *HASHCreate(size_t table_size, hashfunc_t HashFunction, 
							compfunc_t cmp);


/* 
 * Description : HASHDestroy takes hash table and destroys it.
 * Arguments : table - pointer to the hash table.	
 * Return : void
 * time complexity : O(n)
 * space complexity : O(1)
 */
void HASHDestroy(hash_table_t *table);


/*
 * Description : HASHRemove removes a value from the hash table	
 * Arguments : table - pointer to the hash table, data - pointer to the 
 				value to remove
 * Return : void
 * time complexity : O(1)
 * space complexity : O(1)
 */
int HASHRemove(hash_table_t *table, const void *data);


/* 
 * Description : HASHInsert recieves a value from the user and 
					provied it with a hash and a location in the hash table.	
 * Arguments : table - a pointer to the hash table, data - pointer to value
				to insert. key will be computed using user hash function.	
 * Return : 0 if successful, 1 if not.
 * time complexity : O(1)
 * space complexity : O(1)
 */
int HASHInsert(hash_table_t *table, const void *data);


/* 
 * Description : HASHSize computes the number of elements in the hash table.
 * Arguments : table - a pointer to the hash table.
 * Return : number of elements in the hash table.
 * time complexity : O(n)
 * space complexity : O(1)
 */
size_t HASHSize(const hash_table_t *table);


/* 
 * Description : HASHIsEmpty checks if a hash table is empty	
 * Arguments : table - pointer to hash table.	
 * Return : 1 if empty, 0 if full.
 * time complexity : O(n)
 * space complexity : O(1)
 */
int HASHIsEmpty(const hash_table_t *table);


/*
 * Description : HASHFind looks for an element in the hash table.	
 * Arguments : table - a pointer to the hash table, data - a pointer to a value
 * 				to look for in the table.	
 * Return : void pointer to the value in the table if found, NULL if not found
 * time complexity : O(n)
 * space complexity : O(1)
 */
void *HASHFind(const hash_table_t *table, const void *data);


/* 
 * Description : HASHForEach applies a user action function on each element
					in the hash table.	
 * Arguments : table - pointer to the hash table, ActionFun - a user action 
				function, param - a pointer to a parameter given by user to use
				in the action function.	
 * Return : 0 if successful, 1 if not. status 1 can return after several 
 			successful operations.
 * time complexity : O(n)
 * space complexity : O(1)
 */
int HASHForEach(hash_table_t *table, int (*ActionFunc)(void *data ,void *param), void *param);

/* this function will calculate the load factor, and
	optimize the hash table accordingly */
hash_table_t *HASHReFactor(hash_table_t *table, resize updown);

double HashSD(const hash_table_t *table);
double HASHLoad(const hash_table_t *table);

#endif /* __HASHTABLE_H_CR4__ */