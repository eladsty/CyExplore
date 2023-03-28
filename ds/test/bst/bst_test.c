
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
    int to_insert[] = {1,2,3,5,6,7,8,9,0,4,8,20};
    size_t i = 0, size = 0;
    size = sizeof(to_insert) / sizeof(to_insert[0]);
    for (i = 0; i < size; ++i)
    {
        BSTInsert(bst, &to_insert[i]);
    }
        printf("The BSTsize is: %ld \n", BSTSize(bst));

     BSTPrint(bst, size, 3);
    return;
}
  

int main()
{
    bst_t *bst;
    compfunc_t int_cmp_p = &CompareInt;
    int x = 5, y = 100;
    bst = BSTCreate(int_cmp_p);
    printf("Is empty should be 1: %d\n", BSTIsEmpty(bst));

    if (NULL == bst)
    {
        printf("Create Failed failed\n");
        return;
    }

    printf("bst height before insert: %ld\n", BSTHeight(bst));
    InsertRemoveTest(bst);
    printf("bst height after insert: %ld\n", BSTHeight(bst));
 
    if(NULL == BSTFind(bst, &y))
    {
        printf("trying to find 100 resulted in NULL, success!");
    }
    printf("should return 5:  %d",  *(int *)BSTFind(bst, &x));
  
    printf("Is empty should be 0: %d\n", BSTIsEmpty(bst));

    BSTDestroy(bst);

    return 0;
}

 
 