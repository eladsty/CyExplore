
#include <pthread.h>/* threads */
#include <threads.h>/* threads */
#include <stdio.h>  /* printf */
#include <stdlib.h>
#include <omp.h>    /* OpenMP */
#include <assert.h> /* assert */
#include "slist.h"
#include "slist.c" /* if time permits, I should create a shared library */

#define MAX_ROUNDS 10

/* 
description: function pointer to: function that returns void pointer (data to insert)
 */
typedef void *(*produce_action_t(void* data)) ;


struct thread_struct
{
    slist_t *new_list;
    pthread_mutex_t mutex_lock;
    produce_action_t *action_func;
 };

 

void *Consumer(struct thread_struct *thr_struct)
{
    size_t j = 0;
    int i = 0;
    size_t answer = 0;
    slist_iter_t head_node = NULL;

    while (j < MAX_ROUNDS)
    {
        pthread_mutex_lock(&thr_struct->mutex_lock);
        if (SListSize(thr_struct->new_list) > 0)
        {
            head_node = SListStart(thr_struct->new_list);
            answer = (size_t)SListGetData(head_node);
            printf(" %ld \n", answer);
            SListDelete(head_node);
            ++j;
        }
        pthread_mutex_unlock(&thr_struct->mutex_lock);
    }

    return NULL;
}

 void *ProduceData()
{        
    return (rand() % 10);   
}

void *Producer(struct thread_struct *thr_struct)
{
    int i = 0;
    slist_iter_t head_node = NULL;
    void *data = thr_struct->action_func(NULL);
    while (i < MAX_ROUNDS)
    {
        pthread_mutex_lock(&thr_struct->mutex_lock);

        head_node = SListStart(thr_struct->new_list);
        SListInsertBefore(head_node, data );
        ++i;

        pthread_mutex_unlock(&thr_struct->mutex_lock);
    }

    return NULL;
}

void ProdConsMain()
{
    pthread_t cons_thr[3] = {0};
    pthread_t prod_thr[3] = {0};
    int i = 0;
    struct thread_struct thr_strct;
    pthread_mutex_t mutex_lock;

    thr_strct.mutex_lock = mutex_lock;
    thr_strct.new_list = SListCreate();
    thr_strct.action_func = ProduceData;
    for (i = 0; i < 3; ++i)
    {
        pthread_create(&prod_thr[i], NULL, Producer, &thr_strct);
        pthread_create(&cons_thr[i], NULL, Consumer, &thr_strct);
    }

    for (i = 0; i < 3; ++i)
    {
        pthread_join(cons_thr[i], NULL);
        pthread_join(prod_thr[i], NULL);
    }
}

int main()
{
    ProdConsMain();
    /*      SListDestroy(new_list);
     */
    return 0;
}
