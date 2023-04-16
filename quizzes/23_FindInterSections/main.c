
#include <stdio.h>/* printf */
#include <stdlib.h>/* malloc */
#include "/home/elad/elad.shem-tov/ds/include/slist.h"

int FindIntersections(slist_t *list1, slist_t *list2)
{
   node_t *node1 = list1->head;
   node_t *node2 = list2->head;
   if(NULL == list1 || NULL == list2)
   {
      return 0;
   }   

   while(NULL != node1 && NULL != node1->next )
   {
      while(NULL != node2->next)
      {
         if( node1->next == node2->next || node1 == node2->next )
         {
            node2->next = NULL;
            return 1;
         }
      }
   }
   return 0;
}

int main()
{
   

   return 0;
}
