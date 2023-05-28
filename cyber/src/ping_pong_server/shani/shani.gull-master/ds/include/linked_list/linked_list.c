#include "../../include/linked_list/linked_list.h"

/* helper func declaration */
static int Counter(void *a, void *b);

typedef struct node slist_node_t;

struct slist
{
	slist_node_t *head;
	slist_node_t *tail;
};


struct node
{
	void *data;
	slist_node_t *next;
};

/* -------------------------------------------------------------------------- *
 * Status : Approved 
 * Reviewer : Nave
 * Description - Creates a new empty linked list or NULL if fails
 * Arguments - Nothing.
 * Return - slist_t pointer.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */
slist_t *SListCreate(void)
{
	slist_t *new_list = (slist_t *)malloc(sizeof(slist_t));
	slist_node_t *dummy = NULL;
	if (NULL == new_list)
	{
		return NULL;
	}
	dummy = (slist_node_t *)malloc(sizeof(slist_node_t));
	if (NULL == dummy)
	{
		free(new_list);
		new_list = NULL;
		return NULL;
	}
	
	dummy->data = (void *)new_list;
	dummy->next = NULL;
	
	new_list->head = dummy;
	new_list->tail = dummy;

	dummy = NULL;
	return new_list;
}

/* -------------------------------------------------------------------------- *
 * Status : Approved
 * Reviewer : Michael A
 * Description - Terminates the list gracefully.
 * Arguments - list - the list to be freed.
 * Return - Nothing.
 * Notes - If list not valid - undefined behavior.
 * Time Complexity - O(n).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */
void SListDestroy(slist_t *list)
{
	assert(list);

	/* remove all elements */
	while (SListSize(list))
	{
		SListDelete(list->head);
	}

	free(list->head);
	list->head = NULL;
	list->tail = NULL;
	free(list);
	list = NULL;
}

/* -------------------------------------------------------------------------- *
 * Status : Approved
 * Reviewer : Michael A
 * Description - counts the number of elements currently in the list.
 * Arguments - slist_t - the list pointer.
 * Return - size_t - the size of the list.
 * Time Complexity - O(n).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */
size_t SListSize(const slist_t *list)
{
	/* NEED TO USE FOREACH */
	size_t count = 0;
	assert(list);
	SListForEach(list->head, list->tail, Counter, (void *)&count);
	return count;
}

/* helper to SListSize func */
static int Counter(void *data, void *param)
{
	*(int *)param += 1;
	return 0;
}

/* -------------------------------------------------------------------------- *
 * Status : Approved 
 * Reviewer : Nave
 * Description - Inserts new data before the given iterator. inserting before head is undefined.
   SPECIAL NOTE: iterator invalidation is a side effect of this function execution.
 * Arguments - to_insert - iterator to insert before ,data - the data to be inserted.
 * Return - the inserted slist_iter_t or NULL if it fails.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */
slist_iter_t SListInsertBefore(slist_iter_t to_insert, const void *data)
{
	slist_node_t *node = (slist_node_t *)malloc(sizeof(slist_node_t));
	assert(to_insert);
	if (NULL == node)
	{
		return NULL;
	}
	
	/* node recieves to_insert data and pointer
		to insert recieves new data and points to node */
		
	node->data = to_insert->data;
	node->next = to_insert->next;
	
	to_insert->data = (void *)data;
	to_insert->next = node;
	
	if (NULL == node->next)
	{
		/* update new tail iterator to list */
		((slist_t *)node->data)->tail = node;
	}
	
	node = NULL;
	
	return to_insert;
}

/* -------------------------------------------------------------------------- *
 * Status : Approved
 * Reviewer : Michael A
 * Description - Deletes the node in place of the given iterator.
   SPECIAL NOTE: iterator invalidation is a side effect of this function execution.
 * Arguments - to_remove - iterator to remove
 * Return - the new iterator in the place of the given iterator. if requested to delete tail will return iterator to tail.
. request to delete head is undefined.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */
slist_iter_t SListDelete(slist_iter_t to_remove)
{
	slist_node_t *keep_address = to_remove->next;
	assert(to_remove);
	if (NULL == to_remove->next)
	{
		return ((slist_t *)to_remove->data)->tail;
	}
	
	
	to_remove->data = to_remove->next->data;
	to_remove->next = to_remove->next->next;
	
	free(keep_address);
	keep_address = NULL;
	return to_remove;
}

/* -------------------------------------------------------------------------- *
 * Status : Approved
 * Reviewer : Michael A
 * Description - activates the ActionFunc pointer on each node in the iterator range with the given param or
   ActionFunc fails which ever comes first.
   NOTE: from inclusive to exclusive
 * Arguments - slist_iter_t from start of range, slist_iter_t to end of range ActionFunc the function to activate
   ,param - a param to send as argument to the ActionFunc .
 * Return - 0 for success or non-zero for corresponding failure from ActionFunc.
 * if from is after to then undefined behavior
 * Time Complexity - O(n).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */
int SListForEach(slist_iter_t from, slist_const_iter_t to, action_t ActionFunc, void *param)
{
	int boolean = 0;
	assert(from);
	assert(to);
	while ((size_t)to != (size_t)from)
	{
		boolean += ActionFunc(from->data, param);
		from = SListNext(from);
	}
	return boolean;
}

/* -------------------------------------------------------------------------- *
 * Status : Approved
 * Reviewer : Michael A
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
 * Status : Approved 
 * Reviewer : Nave
 * Description - The function returns the first element of the list. 
 * 		 if the list is empty we return an iterator to tail
 * Arguments - list - list
 * Return - the first element of the list.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */
slist_iter_t SListStart(const slist_t *list)
{
	assert(list);
	return list->head;
}

/* -------------------------------------------------------------------------- *
 * Status : Approved 
 * Reviewer : Nave
 * Description - The function returns data in the given iterator.
 * Arguments - element - the iterator to the requested data.
 * Return - the data in the given iterator, NULL .
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */
void *SListGetData(slist_const_iter_t element)
{
	assert(element);
	if (NULL == element->next)
	{
		return NULL;
	}
	return element->data;
}

/* -------------------------------------------------------------------------- *
 * Status : Approved 
 * Reviewer : Nave
 * Description - The function writes over the data in the given iterator with the given data.
 * Arguments - element - the iterator to the data write operation , data - to be written.
 * Return - nothing.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */
void SListSetData(slist_iter_t elem, const void *data)
{
	assert(elem);
	if (NULL == elem->next)
	{
		return;
	}
	elem->data = (void *)data;
}

/* -------------------------------------------------------------------------- *
 * Status : Approved 
 * Reviewer : Nave 
 * Description - The function return the iterator for next element to the given iterator.
    if user gives last iterator will return tail;
 * Arguments - element - the iterator before the requested iterator.
 * Return - slist_iter_t - the next iterator.
 * Time Complexity - O(1).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */
slist_iter_t SListNext(slist_const_iter_t element)
{
	if (NULL == element->next)
	{
		return (slist_iter_t)element;
	}
	return element->next;
}

/* -------------------------------------------------------------------------- *
 * Status : Approved 
 * Reviewer : Nave
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
 * Status : Approved 
 * Reviewer : Nave 
 * Description - activates the CompareFunc pointer on each node in the iterator range with the given param.
 * Arguments - slist_iter_t from start of range, slist_iter_t to end of range CompareFunc the function to compare
   with ,param - a param to send as argument to the CompareFunc .
   NOTE: from inclusive to exclusive
 * Return - iterator to the matching node or "to iterator" if not found.
 * Time Complexity - O(n).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */
slist_iter_t SListFind(slist_const_iter_t from, slist_const_iter_t to, is_match_t CompareFunc, void *param)
{
	while (0 != CompareFunc(from->data, param) && from != to)
	{
		from = SListNext(from);
	}
	return (slist_iter_t)from;
}
























