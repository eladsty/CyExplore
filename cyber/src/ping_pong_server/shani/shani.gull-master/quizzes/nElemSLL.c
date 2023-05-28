
#include "../ds/include/linked_list/linked_list.h"


void *RecFind(slist_iter_t head, size_t size)
{
	if (!size)
	{
		return SListGetData(head);
	}
	return RecFind(SListNext(head), (size - 1));
}
void *FindElem(slist_t *list, size_t size, size_t n)
{
	size_t elem_iter = size - n;
	void *result = RecFind(SListStart(list), elem_iter);
	return result;
}
int main()
{
	int data[10] = {1, 3, 7, 90, -14, 56, 13, 0, 76, 7};
	slist_t *list = SListCreate();
	slist_iter_t tail = SListEnd(list);
	int i = 0;
	int *find = NULL;
	for (i = 0; i < 10; ++i)
	{
		SListInsertBefore(tail, &data[i]);
		tail = SListEnd(list);
	}
	find = (int *)FindElem(list, SListSize(list), 3);
	printf("%d\n", *find);
	return 0;
}