#include <stddef.h> /* NULL */
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	void *data;
	struct node *right; 
	struct node *left;	
}node_t;

typedef struct bst
{
	node_t *root;
}bst_t;
bst_t *Create()
{
	static node_t root, node1, node2, node3, node5;
	bst_t *tree = (bst_t *)malloc(sizeof(bst_t));
	tree->root = &root;
	root.data = (void *)4;
	root.right = &node5;
	root.left = &node2;

	node2.data = (void *)2;
	node2.right = &node3;
	node2.left = &node1;

	node5.data = (void *)5;
	node5.right = NULL;
	node5.left = NULL;

	node1.data = (void *)1;
	node1.right = NULL;
	node1.left = NULL;

	node3.data = (void *)3;
	node3.right = NULL;
	node3.left = NULL;
	return tree;
}


void SwapChild(node_t *node)
{
	node_t *temp;
	temp = node->right;
	node->right = node->left;
	node->left = temp;
}
static int PostOrder(node_t *root)
{
	if (NULL == root)
	{
		return 0;
	}
	PostOrder(root->left);
	PostOrder(root->right);
	SwapChild(root);
	return 0;
}
int BSTMirror(bst_t *tree)
{
	PostOrder(tree->root);
	free(tree);
	tree = NULL;
	return 0;
}

int main()
{
	BSTMirror(Create());
	
	return 0;
}