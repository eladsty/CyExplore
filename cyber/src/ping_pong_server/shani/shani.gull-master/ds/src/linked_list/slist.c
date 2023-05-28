#include <stdlib.h> /* dynamic allocation */
#include <assert.h> /* self explenatory :) */

#include "../../include/linked_list/linked_list.h"

typedef struct node slist_node_t;

struct node
{
	void* data;
	struct node* next;
};

struct slist
{
	slist_node_t* head;
	slist_node_t* tail;
};

/* -------------------------------------------------------------------------- *
 * status: approved
 * reviewer: Michael A
 * Description - Creates a new empty linked list or NULL if fails
 * Arguments - Nothing.
 * Return - slist_t pointer.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */
slist_t *SListCreate(void)
{
	slist_t *newlist = NULL;
	slist_node_t *dummy = NULL;

	newlist = (slist_t *)malloc(sizeof(slist_t));
	if(!newlist)
	{
	    return NULL;
	}
  
	dummy = (slist_node_t *)malloc(sizeof(slist_node_t));
	if(!dummy)
	{
	    free(newlist);
	    return NULL;
	}
  
	newlist->tail = dummy;
	newlist->head = dummy;	
	dummy->data = newlist;
	dummy->next = NULL;	

	return newlist;
}

/* -------------------------------------------------------------------------- *
 * status: approved
 * reviewer: Michael A
 * Description - Terminates the list gracefully.
 * Arguments - list - the list to be freed.
 * Return - Nothing.
 * Notes - If list not valid - undefined behavior.
 * Time Complexity - O(n).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */

void SListDestroy(slist_t *list)
{
	/* delete all nodes except head */
	assert(list);
	while (NULL != list->head->next)
	{
		SListDelete(list->head);
	}
	
	
	free(list->head);
	list->head = NULL;
	free(list);
	list = NULL;
	return;
}

/* --------------------------------------------------------------------------   
 * status: approved
 * reviewer: Michael A
 * Description - Deletes the node in place of the given iterator ,if 
 * the given iterator points to tail
 * undefined behavior.
 * SPECIAL NOTE: iterator invalidation is a side effect of this 
 * function execution.
 * Arguments - to_remove - iterator to remove
 * Return - the new iterator in the place of the given iterator. if 
 *		you delete the last node it will return iterator to tail.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */

slist_iter_t SListDelete(slist_iter_t to_remove)
{
	slist_node_t *tmp = NULL;
	/* checking that head is not also tail (dummy) */
	if (NULL == to_remove->next)
	{
		return ((slist_t *)to_remove->data)->tail;
	}
	
	/* Holding next node to keep the next link */
	tmp = to_remove->next;
	to_remove->data = (to_remove->next)->data;
	to_remove->next = (to_remove->next)->next;
	free(tmp);
	tmp = NULL;
	
	return (to_remove);
}

/* -------------------------------------------------------------------------- *
 * status: approved
 * reviewer: Michael A
 * Description - Inserts new data before the given iterator.
   SPECIAL NOTE: iterator invalidation is a side effect of this function execution.
 * Arguments - to_insert - iterator to insert before ,data - the data to be inserted.
 * Return - the inserted slist_iter_t.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */

slist_iter_t SListInsertBefore(slist_iter_t to_insert, const void *data)
{
	slist_node_t *new_node = NULL;
	
	assert(to_insert);

	new_node = (slist_node_t *)malloc(sizeof(slist_node_t));
	if (new_node == NULL)
	{
		return NULL;
	}
		
	if (to_insert->next == NULL)
	{	
		((slist_t *)to_insert->data)->tail = (slist_node_t *)new_node;	
	}
	
	new_node->next = to_insert->next;
	to_insert->next = new_node;
	
	new_node->data = to_insert->data;
	to_insert->data = (void *)data;
	
	return to_insert;		
}

/* -------------------------------------------------------------------------- *
 * status: approved
 * reviewer: Michael A
 * Description - The function returns the first element of the list. 
 * 		 if the list is empty we return an iterator to tail
 * Arguments - list - list
 * Return - the first element of the list.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */

slist_iter_t SListStart(const slist_t *list)
{	
	return list->head;
}

/* -------------------------------------------------------------------------- *
 * status: approved
 * reviewer: Michael A
 * Description - The function returns the last element of the list - an invalid iterator.
 * Arguments - list - list
 * Return - the last element of the list.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */

slist_iter_t SListEnd(const slist_t *list)
{
  assert(list);
  return list->tail;
}

/* -------------------------------------------------------------------------- *
 * status: approved
 * reviewer: Michael A
 * Description - The function returns data in the given iterator.
 * Arguments - element - the iterator to the requested data.
 * Return - the data in the given iterator.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */

void *SListGetData(slist_const_iter_t element)
{
	assert(element);
	return (void *)(element->data);
}

/* -------------------------------------------------------------------------- *
 * status: approved
 * reviewer: Michael A
 * Description - The function writes over the data in the given iterator with the given data.
 * Arguments - element - the iterator to the data write operation , data - to be written.
 * Return - nothing.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */

void SListSetData(slist_iter_t elem, const void *data)
{
	assert(elem);
	elem->data = (void *)data;
}

/* -------------------------------------------------------------------------- *
 * status: approved
 * reviewer: Michael A
 * Description - The function return the iterator for next element to the given iterator.
    if user gives last iterator will return tail;
 * Arguments - element - the iterator before the requested iterator.
 * Return - slist_iter_t - the next iterator.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */

slist_iter_t SListNext(slist_const_iter_t element)
{
	assert(element);
	return (slist_node_t *)element->next;
}

/* -------------------------------------------------------------------------- *
 * status: approved
 * reviewer: Michael A
 * Description - counts the number of elements currently in the list.
 * Arguments - slist_t - the list pointer.
 * Return - size_t - the size of the list.
 * Time Complexity - O(n).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */

size_t SListSize(const slist_t *list)
{
	size_t count = 0;
	slist_node_t *i = NULL;
	assert(list);

	i = SListStart(list);
	/* counts node excluding tail */
	while ( i->next != NULL)
	{
			++count;
			i = SListNext(i);
	}
	return count;
}

/* -------------------------------------------------------------------------- *
 * status: approved
 * reviewer: Michael A
 * Description - compares the given iterators.
 * Arguments - elem1 - iterator to be compared ,elem2 - iterator to be compared.
 * Return - returns 1 if equal,0 otherwise.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */

int SListIterIsEqual(slist_const_iter_t elem1, slist_const_iter_t elem2)
{
	return ((elem1 == elem2) ? 1 : 0);
}

/* -------------------------------------------------------------------------- *
 * status: approved
 * reviewer: Michael A
 * Description - activates the CompareFunc pointer on each node in the iterator range with the given param.
 * Arguments - slist_iter_t from start of range, slist_iter_t to end of range CompareFunc the function to compare
   with ,param - a param to send as argument to the CompareFunc .
   NOTE: from inclusive to exclusive
 * Return - iterator to the matching node or NULL if not found.
 * Time Complexity - O(n).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */

slist_iter_t SListFind(slist_const_iter_t from, slist_const_iter_t to, is_match_t CompareFunc, void *param)
{
  while((NULL != from->next) && ((size_t)from != (size_t)to) && 			 
					(CompareFunc(from->data ,param)))
  {
    from = SListNext(from);
  }
  return (CompareFunc(from->data ,param) ? NULL : (slist_iter_t)from);
}

/* -------------------------------------------------------------------------- *
 * status: approved
 * reviewer: Michael A
 * Description - activates the ActionFunc pointer on each node in the iterator range with the given 
   param or ActionFunc fails which ever comes first.
   NOTE: from inclusive to exclusive
 * Arguments - slist_iter_t from start of range, slist_iter_t to end of range ActionFunc the function 
	to activate ,param - a param to send as argument to the ActionFunc .
 * Return - 0 for success or non-zero for corresponding failure from ActionFunc.
 * Time Complexity - O(n).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */

int SListForEach(slist_iter_t from, slist_const_iter_t to, action_t ActionFunc, void *param)
{
	slist_node_t *i = from;
	int error_flag = 0;
	while ( i != to && (0 == error_flag))
	{
			error_flag = ActionFunc((SListGetData(i)), param);
			i = SListNext(i);
	}
	
	return error_flag;
}
















