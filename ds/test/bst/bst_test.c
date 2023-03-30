#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"


#define UNUSED(x) (void)(x)
#define SIZEARR(arr) (sizeof(arr) / sizeof(arr[0]))



int cmpint(const void* a, const void* b)
{
	return (*(int *)a - *(int *)b);    
}

int ActionData(void *data, void *param)
{
    printf("%d \n", **(int **)data);
    return 0;
}

void TestUnit(bst_t *bst)
{
    int to_insert[] = {7,5,6,3,12,0,4,2,8,13,22,9,1};
    int to_remove[] = {7,5,6,3,12,0,4,2,8,13,22,9,1};
    int to_find[] = {5,6,3,12};
    int to_fail[] = {304,-3,10};
    size_t i = 0, size = 0, to_test = 0;
    int cmp = 0, flag = 0;
    void *check_null = NULL;
    size = SIZEARR(to_insert);
    for (i = 0; i < size; ++i)
    {
        printf("Size Of list %ld\n", BSTSize(bst));
        BSTInsert(bst, &to_insert[i]);
    }
    BSTPrint(bst, size, 6);
    /*BSTForEach(bst, PRE_ORDER, ActionData, (void *)10);*/
    printf("Hight Of Tree %ld\n", BSTHeight(bst));
    size = SIZEARR(to_find);
    for (i = 0; i < size; ++i)
    {
        cmp = cmpint(BSTFind(bst, &to_find[i]), &to_find[i]);
        if (cmp != 0)
        {
            printf("BSTFind failed to find %d", to_find[i]);
            ++flag;
        }
    }
    size = SIZEARR(to_fail);
    for (i = 0; i < size; ++i)
    {
       check_null = BSTFind(bst, &to_fail[i]);
        if (NULL != check_null)
        {
            printf("BSTFind returned %d insted of NULL (number doesn't exist)", to_find[i]);
            ++flag;
        }
    }
    if (flag == 0)
    {
        printf("passed FInd test\n");
    }
    printf("Now Remove\n\n");
    size = SIZEARR(to_remove);
    for (i = 0; i < size / 2; ++i)
    {
        BSTRemove(bst, &to_remove[i]);
        printf("Size Of list %ld\n", BSTSize(bst));
    }
    printf("The following items were removed:  ");
    for (i = 0; i < size / 2; ++i)
    {
        printf("%d ", to_remove[i]);
    }
    
    printf("\n\n!!!Make sure you can find:  ");
    to_test = i;
    for (; i < size; ++i)
    {
        printf("%d ", to_remove[i]);
    }

    printf("\n\n");
    BSTPrint(bst, size, 8);
    printf("Size Of list %ld\n", BSTSize(bst));
    printf("Remove entire list\n\n");
    /*for (i = to_test; i < size; ++i)
    {
        BSTRemove(bst, &to_remove[i]);
        printf("Size Of list %ld\n", BSTSize(bst));
    }*/
  /*   BSTDestroy(bst); */
    return;
}

void TestHeight()
{
    bst_t *bst = BSTCreate(cmpint);
    int to_insert[] = {10,20,30,40,50,60,70,80};
    int to_insert2[] = {21,5,25,1,9,19,40,0,4,7,12,18,22,29,50};
    size_t i = 0;

    /* test for empty tree */
    printf("When BST is Empty, highet is %lu and should be undefined\n\n", BSTHeight(bst));

    /* test for root only */
    BSTInsert(bst, &to_insert[i]);
    printf("When BST is Root Only, highet is %lu and should be 0\n", BSTHeight(bst));
    BSTPrint(bst, 1, 8);
    printf("\n******************************************\n\n");

    /* test for linear tree */
    for (i = 1; i < SIZEARR(to_insert); ++i)
    {
        BSTInsert(bst, &to_insert[i]); 
    }

    printf("When BST is Linear, highet is %lu and should be %lu\n", BSTHeight(bst), (SIZEARR(to_insert) - 1));
    BSTPrint(bst, SIZEARR(to_insert), 8);
    printf("\n******************************************\n\n");
    
    /* new tree */
    BSTDestroy(bst);
    bst = BSTCreate(cmpint);

    /* Balanced tree */
    for (i = 0; i < SIZEARR(to_insert2); ++i)
    {
        BSTInsert(bst, &to_insert2[i]);
    }
    printf("When BST is Balanced, highet is %lu and should be 3\n", BSTHeight(bst));
    BSTPrint(bst, SIZEARR(to_insert2), 8);
    printf("\n******************************************\n\n");

}


int main()
{
    bst_t *bst;
    
    bst = BSTCreate(cmpint);
    if (NULL == bst)
    {
        printf("Create Failed failed\n");
    }
    TestUnit(bst);
    printf("**** TestHeight *****\n\n\n");
    TestHeight(bst);

    return 0;
}

 
