
#include <stdio.h>/* printf */
#include <assert.h> /* asserts */
typedef struct node node_t;

 struct node 
 {
    int data;
    node_t *next;
 };

void Seperator( node_t *node1,  node_t *node2)
{
     node_t *temp = node2;
    while(NULL != node1)
   {     
     while(NULL != temp->next)
      {
        if(temp->next == node1)
        {
           temp->next = NULL;
           return;
        }
        temp = temp->next;
      }
      temp = node2;
      node1 = node1->next;
   }
}

int FindIntersections( node_t *node1,  node_t *node2)
{
   node_t *temp = node2;
    while(NULL != node1)
   {     
     while(NULL != temp->next)
      {
        if(temp->next == node1)
        {
           return 1;
        }
        temp = temp->next;
      }
      temp = node2;
      node1 = node1->next;
   }
   return 0;
}

 
int main()
{ 
   int res = 0;
    node_t node1, node2, node3, node4, node5, node6, tail, node1_2list, node2_2list, node3_2list;
    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node4.next = &node5;
    node5.next = &node6;
    node6.next = &tail;
    tail.next = NULL;
    
    node1_2list.next = &node2_2list;
    node2_2list.next = &node3_2list;
    node3_2list.next = &node3;
   
   assert(1 == FindIntersections(&node1, &node1_2list) );
   Seperator(&node1, &node1_2list) ;
   assert(NULL ==  node3_2list.next);

  
    return 0;
}