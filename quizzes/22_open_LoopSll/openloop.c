#include <stdio.h>/* printf */
#include <assert.h> /* asserts */
typedef struct node node_t;
 
 struct node 
 {
    int data;
    node_t *next;
 };

void OpenLoopSLL(node_t *node)
{
    node_t *slow = node, *fast = node, *p1 = node, *p2 = node;
    unsigned cyc_len  = 0;
    if (node == NULL || node->next == NULL)
    {
        return;
    }
     while(fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
        if(fast == slow)
        {
           break;        
        }
        ++cyc_len;
    }

    while(cyc_len)
    {
        p2 = p2->next;
        --cyc_len;
    }
    while(p2)
    {
        if(p1 == p2->next)
        {
            printf("im the last node: %d", p2->data);
            p2->next = NULL;
            return;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
}

int main()
{ 
    node_t node1, node2, node3, node4, node5, node6;
 
    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node4.next = &node5;
    node5.next = &node6;
    node6.next = &node3;
 
    node1.data = 100; 
    node2.data = 200; 
    node3.data = 300; 
    node4.data = 400; 
    node5.data = 500; 
    node6.data = 600; 
 
    OpenLoopSLL(&node1);
/*     assert(node6.next != &node3);
 */    return 0;
}
 