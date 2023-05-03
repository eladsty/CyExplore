
#include <pthread.h>/* threads */
#include <threads.h>/* threads */

#include <stdio.h>  /* printf */
#include <stdlib.h>
#include <omp.h>  /* OpenMP */
#include <assert.h> /* assert */
#include "slist.h"
#include "slist.c" /* if time permits, I should create a shared library */

#define MAX_ROUNDS 10000


slist_t *new_list = NULL;
pthread_mutex_t mutex_lock;

int j = 0;

void *Consumer()
{
    int i = 0;
    int *answer = NULL;    

    while (j < MAX_ROUNDS) 
    {
        pthread_mutex_lock(&mutex_lock);
        if(SListSize(new_list) > 0)
        {
            answer = (int *)SListGetData( SListStart(new_list) );
            printf(" %d \n",*answer); 
            SListDelete(SListStart(new_list));
        }
        pthread_mutex_unlock(&mutex_lock);
        ++j;
     }    



    return NULL;
 }

void *Producer()
{
    int i = 0;
    int rand_n = 0;
    
    while(j < MAX_ROUNDS)
    {
        pthread_mutex_lock(&mutex_lock);
        rand_n = rand() % 20;
        SListInsertBefore( SListStart(new_list) , &rand_n);
        pthread_mutex_unlock(&mutex_lock);
        ++j;
    }

    return NULL;
}


void ProdConsMain()
{
    pthread_t cons_thr[3] = {0};
    pthread_t prod_thr[3] = {0};
    int i = 0;

    new_list = SListCreate();    
    for(i = 0; i < 3; ++i)
    {
        pthread_create(&prod_thr[i], NULL, Producer, NULL );
        pthread_create(&cons_thr[i], NULL, Consumer, NULL );
    }
    
    for(i = 0; i < 3; ++i)
    {
        pthread_join(cons_thr[i], NULL);
        pthread_join(prod_thr[i], NULL);
    }    
 }


int main()
{
 
    ProdConsMain();

    SListDestroy(new_list);
  return 0;
}
