#include <assert.h> /* for assert */
#include <stdlib.h>/*malloc and free*/
#include <stdio.h>/*printf*/

#include "bst.h"

#define MAX(a,b)(a > b ? a : b)


struct bst
{
    node_t root;
    compfunc_t cmp;
};

struct node
{
	node_t children[2]; /* left child at index 0, right child at index 1 */
	void *data;
};
/* Status : 
 * Reviewer : 
 * Description : 
	
 * Arguments : 
	
 * Return : 
 */

static void PostTraverse(node_t node, action_t ActionFunc, void *param)
{
    if (NULL != node)
    {
        PostTraverse(node->children[0], ActionFunc, param);
        PostTraverse(node->children[1], ActionFunc, param);
        ActionFunc(node, param);
    }
}

bst_t *BSTCreate(compfunc_t compfunc)
{
    bst_t *new_bst = (bst_t *)malloc(sizeof(bst_t));
    if(NULL == new_bst)
    {
        return NULL;
    }
    new_bst->root = NULL;
    new_bst->cmp = compfunc;

    return new_bst;
}

int BSTIsEmpty(const bst_t *bst)
{
    /* assert bst null ? */
    return (NULL == bst->root? 1 : 0 );
}

 
 

int FreeFunc(void *node_p, void *param)
 {
    node_t node = (node_t)node_p;
    free(node);
    (node) = NULL;
    return 0;
 }

void BSTDestroy(bst_t *bst)
{
    node_t root_node = NULL;
    if(NULL == bst)
    {
        return;
    }
    root_node = bst->root;
    PostTraverse(root_node, &FreeFunc, root_node);
    free(bst);
    bst = NULL;

}

 
static size_t Traverse(node_t node)
{
    size_t cnt = 1;
     if(NULL != node->children[0])
    {
        cnt += Traverse(node->children[0]);
    }

    if(NULL != node->children[1])
    {
        cnt += Traverse(node->children[1]);
    }
    
    return cnt;
}

/* action func for BTSSize */
static int CountFunc(void *nada, void *x)
{
     ++(*(int *)x);
     return 0;
}

/* 
 * Status : 
 * Reviewer :
 * Description : this function will count the size of the BST.
 * Arguments : bst - pointer to BST.
 * Return : the size of the BST.
 * time complexity : O(n)
 * space complexity : O(height)
 */
size_t BSTSize(const bst_t *bst)
{
    int i = 0;
    node_t node =  bst->root;

    PostTraverse(node, &CountFunc, &i);
    return i;
}
  

node_t CreateNewNode(const void *data)
{
    node_t new_node = (node_t)malloc(sizeof(struct node));
 
    assert(NULL != new_node);

 
    new_node->children[0] = NULL;
    new_node->children[1] = NULL;
    new_node->data = (void *)data;
    return new_node;
}
/* could be any type of data as long as compfunc returns 0, pos, neg nums*/
void *Insert(node_t *iter, const void *data , compfunc_t cmp, node_t node_to_insert)
{
    int cmp_result = 0 ;

    /*
     data is the integer that user wanted to insert
     if compare is negative go right(1)
     if positive go left (0)
     */
    if(NULL == (*iter))
    {
        (*iter) = node_to_insert;
        return (*iter);
    }
    cmp_result = cmp((*iter)->data, data);

    if(0 < cmp_result)
    {

        Insert( &(*iter)->children[0], data ,cmp ,node_to_insert);
    }

    if(0 > cmp_result)
    {
        Insert( &(*iter)->children[1], data ,cmp , node_to_insert);
    }
}

void *BSTInsert(bst_t *bst, const void *data)
{
     node_t node_to_insert = CreateNewNode(data);     
    if(NULL == bst || NULL == data)
    {
        return;
    }
 
    if(NULL == bst->root)
    {  
        bst->root = node_to_insert;
        return ;
    }

    Insert(&bst->root, data ,bst->cmp, node_to_insert);
}
 

static void Print(node_t node, int space, int count)
{
    int i = 0;
    if (node == NULL)
    {
        return;
    } 
    
    space += count;
 
    Print(node->children[1], space, count);
 
    printf("\n");
    for (i = count; i < space; i++)
    {
        printf(" ");
    }
    printf("%d\n", *(int *)node->data);
 
    Print(node->children[0], space, count);
}

void BSTPrint(bst_t *bst, int space, int count)
{
    if (bst->root == NULL)
    {   
        printf("Tree is empty\n");
        return;
    } 
    Print((node_t)bst->root, 11, 3);
}
 
static void HTraverser(node_t node, size_t *h_arr)
{
     if(NULL != node->children[0])
    {
        ++h_arr[0];
        h_arr[1] = MAX(h_arr[0], h_arr[1]);
        HTraverser(node->children[0], h_arr);

    }

    if(NULL != node->children[1])
    {
        ++h_arr[0];
        h_arr[1] = MAX(h_arr[0], h_arr[1]);
        HTraverser(node->children[1], h_arr);

    }
    --h_arr[0];
}

 

size_t BSTHeight(const bst_t *bst)
{
    size_t h_arr[2] = {0};
    node_t node = bst->root;
    if(NULL == bst || NULL == bst->root)
    {
        return 0;
    }

    HTraverser(node, h_arr);

    return h_arr[1];
}
 
void *Finder(node_t node,  compfunc_t cmp, const void *data )
{
    int cmp_result;
 
    if(NULL == node)
    {
        return NULL;
    }
    cmp_result = cmp(node->data, data);

    if(0 == cmp_result)
    {
        return (void *)node->data;
    }
    else if(0 < cmp_result)
    {
        Finder(node->children[0], cmp, data);
    }

    else if(0 > cmp_result)
    {   
        Finder(node->children[1], cmp, data);
    }

}
   
void *BSTFind(bst_t *bst, const void *data)
{
    node_t iter;
    int cmp_result;
    compfunc_t cmp_func;
    if(NULL == bst || NULL == bst->root)
    {
        printf("BST is empty or doesn't exist.");
        return NULL;
    }
    iter = bst->root;
    cmp_func = bst->cmp;
     /*
     data is the integer that user wanted to insert
     if compare is negative go right(1)
     if positive go left (0)
     */

    return Finder(iter, cmp_func, data);
}
 
  
/* 
bst for each will traverse the tree and will perform certain action on the tree, including but
not limited to: remove, find, inert, and print.



*/

InOrder(node_t node, action_t ActionFunc, void *param)
{

}
PreOrder()
{
    
}
PostOrder()
{

}

 /* 
 
int BSTForEach(bst_t *bst, traverse order_type, action_t ActionFunc, void *param)
{
    switch(order_type)
    {
        case: 0;

        break;
        case: 1;

        break;

        case: 2;
        break;

    }
    if()

} */