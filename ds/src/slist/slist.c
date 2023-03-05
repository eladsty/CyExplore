#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "slist.h"


 
struct slist
{
	node_t *tail;
	node_t *head;
};


struct node
{
	void *data;
	node_t *next;
};


 

slist_t *SListCreate(void)
{
	struct slist *new_list = malloc(sizeof(struct slist));
	struct node *dummy_node = malloc(sizeof(struct node));

	if(NULL == new_list && NULL == dummy_node)
	{
		return NULL;
	}
	
	dummy_node->data = (slist_t *)new_list;
	dummy_node->next = NULL;
	
	new_list->head = dummy_node;
	new_list->tail = dummy_node;

	return new_list;
}


 

void SListDestroy(slist_t *list)
{
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


/*
	create new node, copy next and data from the given node(to_insert)
	change data of given node(to_insert) to given data, and change next to
	the new node
	if the give node is the dummy, it will update the list tail with the newly 
	created dummy
*/
  
 slist_iter_t SListInsertBefore(slist_iter_t to_insert, const void *data)
{
	slist_iter_t new_node = malloc(sizeof(struct node));
	assert(NULL != to_insert && NULL != new_node);
	new_node->data = to_insert->data;
	new_node->next = to_insert->next; 
	if(NULL == to_insert->next)
	{
		((slist_t *)(to_insert->data))->tail = new_node;
	}
	
	to_insert->data = (void *)data;
  	to_insert->next = new_node;
	
	return to_insert;
}

/*deletes the node pointed by next in the give iterator*/

slist_iter_t SListDelete(slist_iter_t to_remove)
{
	slist_iter_t temp = NULL;
	
	if (NULL == to_remove->next)
	{
		return ((slist_t *)to_remove->data)->tail;
	}
 
	temp = to_remove->next;
	to_remove->data = (to_remove->next)->data;
	to_remove->next = (to_remove->next)->next;
	free(temp);
	temp = NULL;
	
	printf("node removed \n");
	return to_remove;
}

slist_iter_t SListStart(const slist_t *list)
{
	return list->head;
}

 
slist_iter_t SListEnd(const slist_t *list)
{
	return list->tail;
}



void *SListGetData(slist_const_iter_t element)
{
	return (element->data);
}

void SListSetData(slist_iter_t elem, const void *data)
{
	elem->data = (void *)data;
}


slist_iter_t SListNext(slist_const_iter_t element)
{
	if (NULL == element->next)
	{
		return ((slist_t *)(element->data))->tail;
	}
	return (slist_iter_t)element->next;
}

 
size_t SListSize(const slist_t *list)
{
	size_t cnt = 0;
	slist_iter_t iter = SListStart(list);
	
	while ( iter->next != NULL)
	{
			++cnt;
			iter = SListNext(iter);
	}
	return cnt;
}



int SListIterIsEqual(slist_const_iter_t elem1, slist_const_iter_t elem2)
{
	return ((elem1 == elem2) ? 1 : 0);
}


slist_iter_t SListFind(slist_const_iter_t from, slist_const_iter_t to, is_match_t CompareFunc, void *param)
{
	
	slist_iter_t iter = SListNext(from);
	while ( iter != to )
	{
			if ( 0 == CompareFunc((SListGetData(iter)), param))
			{
				return iter;
			}
			iter = SListNext(iter);
	}
	
	return iter;
}


int SListForEach(slist_iter_t from, slist_const_iter_t to, action_t ActionFunc, void *param)
{
	slist_iter_t iter = SListNext(from);
	int error_flag = 0;
	while (iter != to && (0 == error_flag))
	{
			error_flag = ActionFunc((SListGetData(iter)), param);
			iter = SListNext(iter);
	}
	
	return error_flag;
}











