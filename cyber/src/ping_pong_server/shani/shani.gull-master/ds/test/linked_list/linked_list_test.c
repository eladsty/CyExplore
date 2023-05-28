#include "../../include/linked_list/linked_list.h"
int CompareFunc(const void *data, void *param);
int ActionFunc(void *data ,void *param);


int main(void)
{
	int n[] = {15, 41, 50}, i = 0;
	float f = 3.5;
	char l[] = "hi";
	slist_iter_t elem = NULL;

	/* create a list */
	slist_t *my_slist = SListCreate();
	/*find head and tail of list */
	slist_iter_t tail = SListEnd(my_slist);
	
	/* size of list is 0 */
	printf("size 0 : %ld\n", SListSize(my_slist));
	
	/* insert some elements */
	for (i = 0; i < 3; ++i)
	{
		tail = SListInsertBefore(tail, (const void *)&n[i]);
	}
	
	while (tail != SListEnd(my_slist))
	{
		printf("%d\n", *(char *)SListGetData(tail));
		tail = SListNext(tail);
	}
	/* get data from all elements */
	/*SListForEach(SListStart(my_slist), SListEnd(my_slist), ActionFunc, NULL);
	printf("get last input : %d\n", *(char *)SListGetData(tail)); */
	
	if (SListFind(SListStart(my_slist), SListEnd(my_slist), CompareFunc, (void *)&i))
	{
		printf("did not find it\n");
	}
	
	/* set new data */	
	tail = SListStart(my_slist);
	SListSetData(tail, (const void *)&i);
	
	/* get data from set element */
	printf("get last input : %d\n", *(char *)SListGetData(tail));
	
	
	/* size of list */
	printf("size of list is : %lu\n", SListSize(my_slist));
		
	/* find an int */
	if (SListFind(SListStart(my_slist), SListEnd(my_slist), CompareFunc, (void *)&n[2]))
	{
		printf("found it\n");
	}
	
	
	/* find equal elements */
	elem = SListFind(SListStart(my_slist), SListEnd(my_slist), CompareFunc, (void *)&n[2]);
	if (SListIterIsEqual(elem, tail))
	{
		printf("not equal\n");
	}
	
	/* delete an element */	


	/* size is reduced */
	printf("size 1 : %ld\n", SListSize(my_slist));
	
	
	
	
	/* destroy list */
	SListDestroy(my_slist);
	return (0);
}


int ActionFunc(void *data ,void *param)
{
	printf("list element = %d\n", *(int *)data);
	return 0;
}
int CompareFunc(const void *data, void *param)
{
	return ((data == param) ? 1 : 0);
}

