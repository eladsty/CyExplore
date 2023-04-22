
#include <stdio.h>/* printf */
typedef struct node node_t;

 struct node 
 {
    int data;
    node_t *next;
 };
 

int main()
{ 
    node_t node1, node2, node3, node4, node5, node6, tail, node1_2list, node2_2list, node3_2list;
    int nth_elem = 2;
    node_t *res = NULL;
  
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
   
    printf("before releaseing ");
 
    return 0;
}

int FindIntersections( node_t *node1,  node_t *node2)
{
   while(NULL != node1->next)
   {
      if(node1->next = node2)
      {
        return 1;
      }
     
     while(NULL != node2->next)
      {
        if(node1->next = node2)
        {
          return 1;
        }
        node2 = node2->next      
      }
      node1 = node1->next;
   }
   
   return 0;
}

int main()
{
   

   return 0;
}
