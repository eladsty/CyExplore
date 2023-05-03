
#include <pthread.h>/* threads */
#include <threads.h>/* threads */
#include <semaphore.h> /* semaphroes */
#include <stdio.h>  /* printf */
#include <stdlib.h>
#include <omp.h>  /* OpenMP */
#include <assert.h> /* assert */
#include "slist.h"
#include "slist.c" /* if time permits, I should create a shared library */

#define MAX_ROUNDS 10


slist_t *new_list = NULL;
pthread_mutex_t mutex_lock;
sem_t sema;


void *Consumer()
{
    size_t j = 0;
    int i = 0;
    size_t answer = 0;    
    slist_iter_t head_node = NULL;
    
     while (j < MAX_ROUNDS) 
    {
        pthread_mutex_lock(&mutex_lock);
        if(SListSize(new_list) > 0)
        {
            head_node =  SListStart(new_list);
            answer = (size_t)SListGetData( head_node );
            printf(" %ld \n",answer); 
            SListDelete(head_node);
            ++j;
        }
        pthread_mutex_unlock(&mutex_lock);
     }    


    return NULL;
 }

void *Producer()
{
    size_t j = 0;
    int i = 0;
    int *rand_n = NULL;
    slist_iter_t head_node = NULL;

    while(j < MAX_ROUNDS)
    {
        pthread_mutex_lock(&mutex_lock);

        head_node = SListStart(new_list);

        SListInsertBefore(head_node , (void*)j);
        ++j;

        pthread_mutex_unlock(&mutex_lock);
    }

    return NULL;
}


void ProdConsMain()
{
    pthread_t cons_thr[3] = {0};
    pthread_t prod_thr[3] = {0};
    int i = 0;

        
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
    new_list = SListCreate();
    ProdConsMain();
     SListDestroy(new_list);
  return 0;
}
