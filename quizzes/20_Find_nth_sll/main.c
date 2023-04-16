
#include <stdio.h>/* printf */

#include "/home/elad/elad.shem-tov/ds/include/slist.h"
 
 slist_iter_t Find(slist_iter_t node, int *n, slist_iter_t end)
{
    slist_iter_t tmp = NULL;
    if (node == end)
    {
        return NULL;
    }
    tmp = Find(SListNext(node), n, end);
    if (*n == 1)
    {
        *n = -1;
        return node;
    }
    *n = *n - 1;
    return tmp;
}

void *FindNthElem(slist_t *list, int n)
{
    slist_iter_t node = SListStart(list); 
    slist_iter_t end = SListEnd(list);
    node = Find(node, &n, end);
    return SListGetData(node);
}


int main()
{
   slist_t *list = SListCreate();
   int arr[] = {1,2,3,4,5,6,7,8,9};
   unsigned len = sizeof(arr) / sizeof(int), i = 0;
   slist_iter_t node = SListStart(list);
    int elem_i = 3;
 
   for(i = 0; i < len; ++i)
   {
         SListInsertBefore(node, &arr[i]);
   } 
 
   
 
   
    printf("should return 7: %d", *(int *)FindNthElem( list, elem_i ));

 
   SListDestroy(list);
   return 0;
}
