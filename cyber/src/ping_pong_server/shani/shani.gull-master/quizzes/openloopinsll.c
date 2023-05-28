
#include "../ds/include/linked_list/linked_list.h"

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


slist_iter_t IsLoop(slist_t *list)
{
	slist_iter_t next_node = SListStart(list);
	slist_iter_t curr_node = SListStart(list);
	while (NULL != next_node)
	{
		while (curr_node != SListNext(next_node) && curr_node != next_node)
		{
			curr_node = SListNext(curr_node);
		}
		if (curr_node == SListNext(next_node))
		{
			return next_node;
		}
		next_node = SListNext(next_node);
		curr_node = SListStart(list);
	}
	return NULL;
}

int OpenLoop(slist_t *list, slist_iter_t node)
{
	node->next = NULL;
	list->tail = node;
	return 0;
}

int main()
{
	int data[10] = {1, 3, 7, 90, -14, 56, 13, 0, 76, 7};
	slist_t *list = SListCreate();
	slist_iter_t tail = SListEnd(list), trouble;
	int i = 0;
	int *find = NULL;
	for (i = 0; i < 10; ++i)
	{
		SListInsertBefore(tail, &data[i]);
		tail = SListEnd(list);
	}
	((slist_node_t *)SListEnd(list))->next = (slist_node_t *)SListStart(list);
	trouble = IsLoop(list);
	if (NULL != trouble)
	{
		i = OpenLoop(list, trouble);
	}
	if (NULL == IsLoop(list))
	{
		printf("fixed\n");
	}
	SListDestroy(list);
	return i;
}