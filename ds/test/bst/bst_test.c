
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "bst.h"


int CompareInt(const void *a, const void *b)
{
    int x = *(int *)a, y = *(int *)b;
    return (x - y);
}

 

void InsertRemoveTest(bst_t *bst)
{
    int to_insert[] = {1,2,3,5,6,7,8,9,0,4,8};
    size_t i = 0, size = 0;
    size = sizeof(to_insert) / sizeof(to_insert[0]);
    for (i = 0; i < size; ++i)
    {
        BSTInsert(bst, &to_insert[i]);
    }
    BSTPrint(bst, size, 3);
    return;
}

int cmpint(const void* a, const void* b)
{
	return (*(int *)a - *(int *)b);    
}


int main()
{
    bst_t *bst;
    compfunc_t int_cmp_p = &CompareInt;

    bst = BSTCreate(int_cmp_p);
    if (NULL == bst)
    {
        printf("Create Failed failed\n");
        return;
    }

    InsertRemoveTest(bst);

    BSTDestroy(bst);

    return 0;
}

 
 