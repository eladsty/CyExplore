#ifndef __LINKED_LIST_H_CR4__ 
#define __LINKED_LIST_H_CR4__ 

#include <stdio.h> /* Used for printing functions */
#include <stdlib.h> /* Used for malloc and free functions */
#include <stddef.h> /* Used for size_t type */
#include <string.h> /* Used for string functions */
#include <assert.h> /* Used for assert function */

typedef struct slist slist_t;
typedef struct node *slist_iter_t;
typedef const struct node *slist_const_iter_t;

typedef int (*action_t)(void *data ,void *param);
typedef int (*is_match_t)(const void *data, void *param);



/* -------------------------------------------------------------------------- *
 * Description - Creates a new empty linked list or NULL if fails
 * Arguments - Nothing.
 * Return - slist_t pointer.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */
slist_t *SListCreate(void);

/* -------------------------------------------------------------------------- *
 * Description - Terminates the list gracefully.
 * Arguments - list - the list to be freed.
 * Return - Nothing.
 * Notes - If list not valid - undefined behavior.
 * Time Complexity - O(n).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */
void SListDestroy(slist_t *list);

/* -------------------------------------------------------------------------- *
 * Description - Inserts new data before the given iterator. inserting before head is undefined.
   SPECIAL NOTE: iterator invalidation is a side effect of this function execution.
 * Arguments - to_insert - iterator to insert before ,data - the data to be inserted.
 * Return - the inserted slist_iter_t or NULL if it fails.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */
slist_iter_t SListInsertBefore(slist_iter_t to_insert, const void *data);

/* -------------------------------------------------------------------------- *
 * Description - Deletes the node in place of the given iterator ,if the given iterator points to tail
   undefined behavior.
   SPECIAL NOTE: iterator invalidation is a side effect of this function execution.
 * Arguments - to_remove - iterator to remove
 * Return - the new iterator in the place of the given iterator. if you delete the last node it will return,  request to delete head is undefined.
   iterator to tail.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */
slist_iter_t SListDelete(slist_iter_t to_remove);

/* -------------------------------------------------------------------------- *
 * Description - The function returns the first element of the list. 
 * 		 if the list is empty we return an iterator to tail
 * Arguments - list - list
 * Return - the first element of the list.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */
slist_iter_t SListStart(const slist_t *list);

/* -------------------------------------------------------------------------- *
 * Description - The function returns the last element of the list - an invalid iterator.
 * Arguments - list - list
 * Return - the last element of the list.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */
slist_iter_t SListEnd(const slist_t *list);

/* -------------------------------------------------------------------------- *
 * Description - The function returns data in the given iterator.
 * Arguments - element - the iterator to the requested data.
 * Return - the data in the given iterator.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */
void *SListGetData(slist_const_iter_t element);

/* -------------------------------------------------------------------------- *
 * Description - The function writes over the data in the given iterator with the given data.
 * Arguments - element - the iterator to the data write operation , data - to be written.
 * Return - nothing.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */
void SListSetData(slist_iter_t elem, const void *data);

/* -------------------------------------------------------------------------- *
 * Description - The function return the iterator for next element to the given iterator.
    if user gives last iterator will return tail;
 * Arguments - element - the iterator before the requested iterator.
 * Return - slist_iter_t - the next iterator.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */
slist_iter_t SListNext(slist_const_iter_t element);

/* -------------------------------------------------------------------------- *
 * Description - counts the number of elements currently in the list.
 * Arguments - slist_t - the list pointer.
 * Return - size_t - the size of the list.
 * Time Complexity - O(n).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */
size_t SListSize(const slist_t *list);

/* -------------------------------------------------------------------------- *
 * Description - compares the given iterators.
 * Arguments - elem1 - iterator to be compared ,elem2 - iterator to be compared.
 * Return - returns 1 if equal,0 otherwise.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */
int SListIterIsEqual(slist_const_iter_t elem1, slist_const_iter_t elem2);

/* -------------------------------------------------------------------------- *
 * Description - activates the CompareFunc pointer on each node in the iterator range with the given param.
 * Arguments - slist_iter_t from start of range, slist_iter_t to end of range CompareFunc the function to compare
   with ,param - a param to send as argument to the CompareFunc .
   NOTE: from inclusive to exclusive
 * Return - iterator to the matching node or "to iterator" if not found.
 * Time Complexity - O(n).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */
slist_iter_t SListFind(slist_const_iter_t from, slist_const_iter_t to, is_match_t CompareFunc, void *param);

/* -------------------------------------------------------------------------- *
 * Description - activates the ActionFunc pointer on each node in the iterator range with the given param or
   ActionFunc fails which ever comes first.
   NOTE: from inclusive to exclusive
 * Arguments - slist_iter_t from start of range, slist_iter_t to end of range ActionFunc the function to activate
   ,param - a param to send as argument to the ActionFunc .
 * Return - 0 for success or non-zero for corresponding failure from ActionFunc.
 * Time Complexity - O(n).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */
int SListForEach(slist_iter_t from, slist_const_iter_t to, action_t ActionFunc, void *param);
#endif /* __LINKED_LIST_H_CR4__ */
