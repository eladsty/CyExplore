#include <assert.h> /* for assert */
#include <stdlib.h>/*malloc and free*/
#include <stdio.h>/*printf*/

#include "bst.h"

#define MAX(a,b)(a > b ? a : b)
  
 
 int FreeFunc(void *node_p, void* unused);


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
/* 
 static void PostTraverse(node_t node, action_t ActionFunc, void *param)
{
    if (NULL != node)
    {
        PostTraverse(node->children[0], ActionFunc, param);
        PostTraverse(node->children[1], ActionFunc, param);
        ActionFunc(node, param);
    }    
} */
 
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

 

int FreeFunc(void *node_p, void* unused)
 {
     if(NULL == (node_t)node_p)
    {
        return -1;
    }
    
    free(node_p);
    node_p = NULL;
    return 0;
 }
 
/*  Approved by Ran
 */  
void BSTDestroy(bst_t *bst) 
{
    node_t root_node = NULL;
    if(NULL == bst || NULL == bst->root)
    {
        return;
    }
    root_node = bst->root;


    BSTForEach( (bst_t *)bst, POST_ORDER, &FreeFunc, root_node);

    free(bst);
    bst = NULL;

}
 

 
/* 
 * Status : APPROVED
 * Reviewer : Hen
 * Description : this function will count the size of the BST.
 * Arguments : bst - pointer to BST.
 * Return : the size of the BST.
 * time complexity : O(n)
 * space complexity : O(height)
 */
/* size_t BSTSize(const bst_t *bst)
{
    int i = 0;
    node_t node =  bst->root;
    PostTraverse(node, &CountFunc, &i);
 
     return i;
} */
  

node_t CreateNewNode(const void *data)
{
    node_t new_node = (node_t)malloc(sizeof(struct node));
   if (NULL == new_node)
   {
        return NULL;
   }
 
    new_node->children[0] = NULL;
    new_node->children[1] = NULL;
    new_node->data = (void *)data;
    return new_node;
}

/*******************************************************************************************************************/
 void *Insert(node_t *iter, const void *data , compfunc_t cmp, node_t node_to_insert)
{
     node_t *node_p_p;
 
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
    cmp((*iter)->data, data);
    node_p_p = ((cmp((*iter)->data, data)) > 0 ? (&(*iter)->children[0]): &(*iter)->children[1]);

     
    Insert(node_p_p ,data ,cmp ,node_to_insert);
}
 
#define GO_TO_CHILD(res) ((res) > 0 ? (&(*iter)->children[0]): &(*iter)->children[1]))


/* 
 * Status : APPROVED
 * Reviewer : Hen
*/
void *BSTInsert(bst_t *bst, const void *data)
{
    node_t node_to_insert = CreateNewNode(data);     
    if(NULL == bst || NULL == data)
    {
        return NULL;
    }
 
    if(NULL == bst->root)
    {  
        bst->root = node_to_insert;
        return;
    }

    Insert(&bst->root, data ,bst->cmp, node_to_insert);
}
 
/* *********************************************************************************************** */
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
/* 
 * Status : APPROVED
 * Reviewer : Hen
*/
void BSTPrint(bst_t *bst, int space, int count)
{
    if (bst->root == NULL)
    {   
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

 
/* 
 * Status : APPROVED
 * Reviewer : Hen
*/
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
 


static void *DataFinder(node_t node, compfunc_t cmp, const void *data)
{
    node_t iter_node = node;
    if(node == NULL)
    {
        return NULL;
    }
    if ( cmp( iter_node->data , data ) == 0 )
    {
        return (void *)(node->data);
    }

    else if ( cmp( iter_node->data , data ) > 0 )
    {
        DataFinder(iter_node->children[0], cmp, data);
    }
    else if ( cmp(node->data, data ) < 0 )
    {
        DataFinder(iter_node->children[1], cmp, data);
    }
}

/* 
 * Status : APPROVED
 * Reviewer : Hen
*/
void *BSTFind(bst_t *bst, const void *data)
{
    node_t iter;
   
    return (void *)DataFinder(bst->root, bst->cmp, data);
}

/* 
bst for each will traverse the tree and will perform certain action on the tree, including but
not limited to: remove, find, inert, and print.

*/

static int InOrderTraverse(node_t node, action_t ActionFunc, void *param)
{
    /* maybe I should check the node children. also should i change from void to int????  */
    if (NULL != node)
    {
        InOrderTraverse(node->children[0], ActionFunc, param);
        return ActionFunc(node, param);
        InOrderTraverse(node->children[1], ActionFunc, param);
    }
}

 static int PreOrderTraverse(node_t node, action_t ActionFunc, void *param)
{
      /* maybe I should check the node children. also should i change from void to int????  */
    if (NULL != node)
    {
        return ActionFunc(node, param);
        PreOrderTraverse(node->children[0], ActionFunc, param);
        PreOrderTraverse(node->children[1], ActionFunc, param);
    }
}

 static int PostOrderTraverse(node_t node, action_t ActionFunc, void *param )
{
    if (NULL != node)
    {
        PostOrderTraverse(node->children[0], ActionFunc, param);
        PostOrderTraverse(node->children[1], ActionFunc, param);
        return ActionFunc(node, param);
    }
}
/* 
 * Status : APPROVED
 * Reviewer : Hen
*/
int BSTForEach( bst_t *bst, traverse order_type, action_t ActionFunc, void *param)
{
    switch (order_type)
    {
    case PRE_ORDER:
        return PreOrderTraverse(bst->root, ActionFunc, param );
        break;

    case IN_ORDER:
        return InOrderTraverse(bst->root, ActionFunc, param );
        break;

    case POST_ORDER:
        return PostOrderTraverse(bst->root, ActionFunc, param );
        break;

    default:
        return PreOrderTraverse(bst->root, ActionFunc, param );
        break;
    }

	return -1;
}  


node_t GoLeft(node_t current_node)
{
    node_t temp = NULL;
    if (NULL == current_node->children[0])  /*if no more left left...*/
    {
        return current_node; 
    }
    temp = GoLeft(current_node->children[0]);  /*else go left until no left left*/
    return temp;
}


node_t Remove(node_t iter_node, compfunc_t compfunc, const void *user_data)
{
	int comp_result;  
	node_t temp = NULL; 

   if(NULL == iter_node || NULL == user_data)
    {
         return NULL;
    }  
    comp_result = compfunc(iter_node->data, user_data); 

	if (0 < comp_result)    /* if node data bigger than user data, go left */
	{
		iter_node->children[0] = Remove(iter_node->children[0], compfunc, user_data);
	}
	
	else if (0 > comp_result)  /* if node data smaller than user data, go right */
	{
		iter_node->children[1] = Remove(iter_node->children[1], compfunc, user_data);
	}
	
	else if (0 == comp_result)   /* if node data equals user data: */
	{
		if (NULL == iter_node->children[0])   /* if left empty, return pointer to right and free current node.   */
		{
			temp = iter_node->children[1];
			free(iter_node);
			return temp;
		}
		else if (NULL == iter_node->children[1])
		{
			temp = iter_node->children[0];
			free(iter_node);
			return temp;
		}
		else
		{
			temp = GoLeft(iter_node->children[1]); 
			iter_node->data = temp->data; 
			iter_node->children[1] = Remove(iter_node->children[1], compfunc, temp->data);
		}
	}
	return iter_node;
}
/* 
 * Status : APPROVED
 * Reviewer : Hen
*/
void BSTRemove(bst_t *bst, void *data)
{
	node_t ptr_root = bst->root;
	
	if (1 == BSTIsEmpty(bst))  /*if tree is empty*/
	{
		return;
	}
	Remove(ptr_root, bst->cmp, data);
}


/* action func for BTSSize */
static int CountFunc(void *nada, void *x)
{
     ++(*(int *)x);
     return 0;
}

/* 
 * Status : APPROVED
 * Reviewer : Hen
*/
size_t BSTSize(const bst_t *bst)
{
    int i = 0;
    node_t node;
    if(NULL == bst || NULL == bst->root)
    {
        return 0;
    }
    node = bst->root;
    return BSTForEach((bst_t *)bst, POST_ORDER, &CountFunc, &i);
}