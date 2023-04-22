
#include <stdio.h>/* printf */
typedef struct node node_t;

 struct node 
 {
    int data;
    node_t *next;
 };

node_t *FindNthElem(node_t *node, int *n);
node_t *Find(node_t *node, int *n);

node_t *Find(node_t *node, int *n)
{
    
    if(0 == *n)
    {
        return node;
    }
    *n -= 1;
    return  Find(node->next, n);
}

node_t *FindNthElem(node_t *node, int *n)
{
    int n_copy = *n;
     return  Find(node, &n_copy);
}


int main()
{ 
    node_t node1, node2, node3, node4, node5, node6, tail;
     int nth_elem = 2;
    node_t *res = NULL;
 
    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node4.next = &node5;
    node5.next = &node6;
    node6.next = &tail;
    tail.next = NULL;

    node1.data = 100; 
    node2.data = 200; 
    node3.data = 300; 
    node4.data = 400; 
    node5.data = 500; 
    node6.data = 600; 

  
    res = FindNthElem(&node1, &nth_elem );
    printf("the %d num is: %d", nth_elem,  res->data );

 
    return 0;
}

