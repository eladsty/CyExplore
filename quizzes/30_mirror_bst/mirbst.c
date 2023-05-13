#include <assert.h>
#include <stdio.h>/* printf */
#include <stddef.h>/* NULL */
#define COUNT 10

typedef struct node node_t;
 struct node 
 {
    int data;
    node_t *left;
    node_t *right;
 };

 

void PrintBST(node_t *root, int space)
{
    int i = 0;
     if (root == NULL)
        return;
 
     space += COUNT;
 
    PrintBST(root->right, space);
 
    printf("\n");
    for (i = COUNT; i < space; i++)
    {
        printf(" ");
    }  
    printf("%d\n", root->data);
  
    PrintBST(root->left, space);
}

void printBST_2D(node_t *root)
{
    PrintBST(root, 0);
}

void MirrorBST(node_t *root)
{
    node_t *temp = NULL;
    if (NULL == root)
    {
        return;
    }
    temp = root->left;
    root->left = root->right;
    root->right = temp;

    MirrorBST(root->left);
    MirrorBST(root->right);
}

int main()
{
    node_t node1, node2, node3, node4, node5;
    node1.data = 1;
    node2.data = 2; 
    node3.data = 3;
    node4.data = 4;
    node5.data = 5; 
    
    node4.right = &node5;
    node4.left = &node2;
    node4.right->right = NULL;
    node4.right->left = NULL;
    node4.left->left = &node1;
    node4.left->left->left = NULL;
    node4.left->left->right = NULL;

    node4.left->right = &node3;
    node4.left->right->right = NULL;
    node4.left->right->left = NULL;

     printBST_2D(&node4);
        MirrorBST(&node4);
     printBST_2D(&node4);

    return 0;
}