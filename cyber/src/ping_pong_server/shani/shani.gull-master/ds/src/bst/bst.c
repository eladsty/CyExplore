#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <limits.h> /* MAX INT */
#include <stdio.h> /* printf for tree printing */
#include "../../include/bst/bst.h"



typedef struct node node_t;
typedef int (*chosen_order)(node_t *, action_t, void *);
typedef enum{
			NO_CHILDREN = -1,
			LEFT = 0,
			RIGHT = 1,
			TWO_CHILDREN = 2
			}children;

struct bst
{
	node_t *root;
	compfunc_t cmp;
};
struct node
{
	void *data;
	node_t *children[TWO_CHILDREN]; /* left child at index 0, right child at index 1 */
};

static void Print(node_t *node, int space, int count);
static node_t *RecursiveRemove(bst_t *bst, node_t *node);
static int PreOrder(node_t *root, action_t act, void *param);
static int PostOrder(node_t *root, action_t act, void *param);
static int InOrder(node_t *root, action_t act, void *param);




#define CHILD(x, cmp, data_p) (0 < (cmp)((x), (data_p)) ? LEFT : RIGHT)
#define DATA_IN_LEFT_CHILD(x, cmp, data_p) (0 == (cmp)((x), (data_p)) ? 0 : 1)
#define ISLEAF(x, y) (NULL == (x) && NULL == (y) ? 1 : 0)
#define HASLEFT(x) (NULL != (x) ? 1: 0)
#define HASRIGHT(x) (NULL != (x) ? 1: 0)

static chosen_order tree_traverse[3] = {PreOrder, InOrder, PostOrder};

/* Status : Approved
 * Reviewer : Adi
 * Description : creates struct with node pointer
 * 				to root and a function pointer to a user's compare function
 * Arguments : compare function pointer
 * Return : pointer to the tree struct
 */
bst_t *BSTCreate(compfunc_t compfunc)
{
	bst_t *bst = (bst_t *)malloc(sizeof(*bst));
	if (NULL == bst)
	{
		exit(1);
	}
	bst->root = NULL;
	bst->cmp = compfunc;
	return bst;
}


/* Status : Approved
 * Reviewer : Adi
 * Description : checks if tree is empty, if not - empties and destroys the tree.
 * Arguments :pointer to tree
 * Return : nothing
 */
void BSTDestroy(bst_t *bst)
{
	while (!BSTIsEmpty(bst))
	{
		BSTRemove(bst, bst->root->data);
	}
	free(bst);
	bst = NULL;
	return;
}

/* Status : Appreved
 * Reviewer : Adi
 * Description : checks if tree has nodes or not.
 * Arguments : pointer to tree.
 * Return : 0 if full, 1 if empty
 */
int BSTIsEmpty(const bst_t *bst)
{
	return (NULL == (node_t *)bst->root) ? 1 : 0;
}

/* helper to BSTFind & BSTRemove -
	this function returns the parent-node to the node
	containing the seeked out data*/
static node_t *RecursiveFind(node_t *root, compfunc_t cmp, void *data)
{
	if (!cmp(root->data, data))
	{
		return root;
	}
	if (NULL == root->children[CHILD(root->data, cmp, data)])
	{
		return NULL;
	}
	/* if found parent, return pointer to it */
	if (cmp(root->children[CHILD(root->data, cmp, data)]->data, data))
	{
		root = RecursiveFind(root->children[CHILD(root->data, cmp, data)], cmp, data);
	}
	return root;
}
/* Status : Appreved
 * Reviewer : Adi
 * Description : finds a node containing certain data
 * Arguments : pointer to tree and pointer to data to look for in tree
 * Return : pointer to data in tree, null if tree is empty/node cannot be found.
 */
void *BSTFind(bst_t *bst, const void *data)
{
	node_t *found = NULL;
	if (2 > BSTSize(bst)) /* i.e. list has root or empty */
	{
		return ((1 == BSTSize(bst)) ? bst->root->data : NULL);
	}
	found = RecursiveFind(bst->root, bst->cmp, (void *)data);
	if (bst->root == found) /* if root holds value - only case i wouldnt get the perant */
	{
		return found->data;
	}
	return ((NULL == found) ? NULL : (found->children[CHILD(found->data, bst->cmp, data)])->data);
}



static node_t *LeftMostNodeRightSub(node_t *node)
{
	node_t *temp = node->children[LEFT];
	if (NULL != temp)
	{
		if (temp->children[LEFT])
		{
			LeftMostNodeRightSub(node->children[LEFT]);
		}
		else if (temp->children[RIGHT])
		{
			return temp;
		}
	}
	return node;
}

static node_t *RecursiveRemove(bst_t *bst, node_t *node)
{
	node_t *temp = NULL, *to_free = NULL;
	if (ISLEAF(node->children[LEFT], node->children[RIGHT]))
	{
		free(node);
		node = NULL;
		return NULL;
	}
	else if (!(node->children[RIGHT]))
	{
		temp = node->children[LEFT];
		free(node);
		node = NULL;
		return temp;
	}
	else if ((!(node->children[LEFT])))
	{
		temp = node->children[RIGHT];
		free(node);
		node = NULL;
		return temp;
	}
	else
	{
		temp = LeftMostNodeRightSub(node->children[RIGHT]); /* if i return 
			parent of leftmost, i can copt the data and then point the parent 
			to the next node after that if there is one, and free the leftmost*/
		if (temp->children[LEFT] && ISLEAF(temp->children[LEFT]->children[LEFT], temp->children[LEFT]->children[RIGHT])) /* leftmost is leaf*/
		{
			node->data = temp->children[LEFT]->data;
			free(temp->children[LEFT]);
			temp->children[LEFT] =NULL;
		}
		else if (temp->children[LEFT])
		{
			node->data = temp->children[LEFT]->data;
			to_free = temp->children[LEFT];
			free(to_free);
			to_free = NULL;
		}
		else if (!(temp->children[RIGHT]))
		{
			node->data = temp->data;
			free(temp);
			temp = NULL;
		}
		else
		{
			free(node);
			node = NULL;
			return temp;
		}
	}
	return node;
}

/* Status : Approved
 * Reviewer : Adi
 * Description : removes a node by recorsivly finding it's leaf and copying
 * 					the data backwords while freeing the next node
 * Arguments : pointer to tree, and pointer to data to find and remove
 * Return : nothing
 */
void BSTRemove(bst_t *bst, void *data)
{
	node_t *parent_node = NULL;
	parent_node = RecursiveFind(bst->root, bst->cmp, data);
	if (bst->root->data == data) /* if parent is root node */
	{
		bst->root = RecursiveRemove
			(bst, parent_node);
	}
	else if (parent_node->children[LEFT])
	{
		if (parent_node->children[LEFT]->data == data)
		{
			parent_node->children[LEFT] = RecursiveRemove(bst, 
			parent_node->children[LEFT]);
		}
	}
	else 
	{
		parent_node->children[RIGHT] = RecursiveRemove(bst, 
			parent_node->children[RIGHT]);
	}
	return;
}


/* helper to BSTInsert - 
	creates a node
*/
static void *CreateNode(node_t *new_node, void *data)
{
	new_node = (node_t *)malloc(sizeof(node_t));
	if (NULL == new_node)
		{
			return NULL;
		}
	new_node->data = data;
	new_node->children[LEFT] = NULL;
	new_node->children[RIGHT] = NULL;
	return new_node;
}
/* helper to BSTInsert -
	using the compare function,
	decides on which branch to put the new
	value inserted, and insertes it
*/
static node_t *RecursiveInsert(node_t *node, compfunc_t cmp, void *data, 
								node_t *new_node)
{
	if (NULL != node->children[CHILD(node->data, cmp, data)])
	{
		return RecursiveInsert(node->children[CHILD(node->data, cmp, data)], 
								cmp, data, new_node);
	}
	else
	{
		new_node = CreateNode(new_node, data);
		node->children[CHILD(node->data, cmp, data)] = new_node;
	}
	return new_node;
}
/* Status : Approved
 * Reviewer : Adi
 * Description : inserts a node and puts data in it,
 * 					in the correct place in the tree
 * Arguments : pointer to tree, pointer to data
 * Return : nothing
 */
void *BSTInsert(bst_t *bst, const void *data)
{
	node_t *new_node = NULL, *found = NULL;
	if (NULL == bst->root) /* first insert */
	{
		bst->root = CreateNode(bst->root, (void *)data);
		return bst->root->data;
	}
	else
	{
		found = RecursiveFind(bst->root, bst->cmp, (void *)data);
		assert(!found);
		new_node = RecursiveInsert(bst->root, bst->cmp, (void *)data, new_node);
		return new_node->data;
	}
}

/* helper to BSTSize -
	traverses pre order and add 1 to size before
	returning from each node
*/
int ActionCounter(void *data, void *param)
{
	*(size_t *)param += 1;
	return 0;
}
/* Status : Approved
 * Reviewer : Adi
 * Description : counts number of nodes in the tree
 * Arguments : pointer to tree
 * Return : nothing
 */
size_t BSTSize(const bst_t *bst)
{
	size_t size = 0;
	BSTForEach((bst_t *)bst, PRE_ORDER, ActionCounter, &size);
	return size;
}


/* prints whole tree */
static void Print(node_t *node, int space, int count)
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
	Print((node_t *)bst->root, space, count);
}

static void RecursiveHeight(node_t *node, size_t *max, size_t temp)
{
	if (NULL == node->children[0] && NULL == node->children[1])
	{
		*max = (*max < temp) ? temp : *max;
	}
	if (NULL != node->children[0])
	{
		RecursiveHeight(node->children[0], max, (temp + 1));
	}
	if (NULL != node->children[1])
	{
		RecursiveHeight(node->children[1], max, (temp + 1));
	}
	return;
}
/* Status : Approved
 * Reviewer : Adi
 * Description : finds deepest node and count as you go back to root
 * Arguments : pointer to tree
 * Return :
 */
size_t BSTHeight(const bst_t *bst)
{
	size_t high = 0, temp = 0;
	RecursiveHeight(((bst_t *)bst)->root, &high, temp);
	return high;
}

/* pre order >> root > left > right */
static int PreOrder(node_t *root, action_t act, void *param)
{
	int result = 0;
	if (NULL == root)
	{
		return 0;
	}
	result = act(root->data, param);
	PreOrder(root->children[LEFT], act, param);
	PreOrder(root->children[RIGHT], act, param);
	return result;
}
/* post order >> left > right > root */
static int PostOrder(node_t *root, action_t act, void *param)
{
	int result = 0;
	if (NULL == root)
	{
		return 0;
	}
	PostOrder(root->children[LEFT], act, param);
	PostOrder(root->children[RIGHT], act, param);
	result = act(root->data, param);
	return result;
}
/* in order >> left > root > right */
static int InOrder(node_t *root, action_t act, void *param)
{
	int result = 0;
	if (NULL == root)
	{
		return 0;
	}
	PostOrder(root->children[LEFT], act, param);
	result = act(root->data, param);
	PostOrder(root->children[RIGHT], act, param);
	return result;
}
/* Status : Approved
 * Reviewer : Adi
 * Description : traverses over tree in user-chosen order, using a LUT
 * 					of travers functions. aplying a user action func 
 * 					as it goues
 * Arguments : pointer to tree, chosen order type, action function pointer,
 * 				parameter.
 * Return : will return what ever action function returns.
 */
int BSTForEach(bst_t *bst, traverse order_type, action_t act, void *param)
{
	return tree_traverse[order_type](bst->root, act, param);
}

