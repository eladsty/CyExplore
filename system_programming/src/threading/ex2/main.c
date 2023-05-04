#include <pthread.h>/* threads */
#include <semaphore.h> /* semaphroes */
#include <stdio.h>  /* printf */
#include <assert.h> /* assert */

#include "slist.h"
#include "slist.c" /* if time permits, I should create a shared library */

#define MAX_ROUNDS 1000
#define N_THREADS 16

/* 
description: function pointer to: function that returns void pointer (data to insert)
 */
typedef void *(*producer_action_t)(void* data);
typedef void *(*consumer_action_t)(void* data);
void *ConsumeData(void *data);
void *ProduceData(void *data);

struct thread_struct
{
    pthread_mutex_t mutex_lock;
    slist_t *new_list;
    producer_action_t prod_action_func;
    consumer_action_t cons_action_func;
    void* data;
};

 
void *Consumer(void *data)
{
    size_t i = 0;
    size_t sum = 0;
    size_t answer = 0;
    slist_iter_t head_node = NULL;
    
    while (i < MAX_ROUNDS)
    {
        pthread_mutex_lock(&((struct thread_struct*)data)->mutex_lock);
        /* printf("thread id = %ld", pthread_self()); */

        if (SListSize(((struct thread_struct*)data)->new_list) > 0)
        {
            head_node = SListStart(((struct thread_struct*)data)->new_list);
            answer = (size_t)SListGetData(head_node);
            /* printf(" %ld \n", answer); */
            SListDelete(head_node);
            ++i;
            sum += answer;
        }
        pthread_mutex_unlock(&((struct thread_struct*)data)->mutex_lock);
    }

    return (void*)sum;
}
 
 void *ProduceData(void *data)
{        
    (void)data;
    return (void *)(size_t)(rand() % 10);   
}

void *ConsumeData(void *data)
{        
    printf(" %ld \n", (size_t)data); 
    return NULL;   
}

void *Producer(void *data)
{
    int i = 0;
    size_t sum = 0;
    slist_iter_t head_node = NULL;
    void *data_to_send = ((struct thread_struct*)data)->prod_action_func(NULL);
    
    while (i < MAX_ROUNDS)
    {
        pthread_mutex_lock(&((struct thread_struct*)data)->mutex_lock);
        /* printf("thread id = %ld", pthread_self()); */

        head_node = SListStart(((struct thread_struct*)data)->new_list);
        SListInsertBefore(head_node, data_to_send);
        ++i;
        sum += (size_t)data_to_send;

        pthread_mutex_unlock(&((struct thread_struct*)data)->mutex_lock);
        
    }

    return (void*)sum;
}

void ProdConsMain()
{
    int i = 0;
    size_t tot_prod = 0;
    size_t tot_cons = 0;
    pthread_t cons_thr[3] = {0};
    pthread_t prod_thr[3] = {0};
    pthread_mutex_t mutex_lock;
    slist_t *thr_slist = NULL;
    struct thread_struct thr_struct;
    thr_slist = SListCreate();

    pthread_mutex_init(&mutex_lock, 0);

    thr_struct.mutex_lock = mutex_lock;
    thr_struct.new_list = thr_slist;
    thr_struct.prod_action_func = ProduceData;
    thr_struct.cons_action_func = ConsumeData;
    thr_struct.data = NULL;
    
 
    for (i = 0; i < 3; ++i)
    {
        pthread_create(&prod_thr[i], NULL, Producer, &thr_struct);
        pthread_create(&cons_thr[i], NULL, Consumer, &thr_struct);
    }

    for (i = 0; i < 3; ++i)
    {
        size_t cons_ret = 0;
        size_t prod_ret = 0;
        pthread_join(cons_thr[i], (void*)&cons_ret);
        pthread_join(prod_thr[i], (void*)&prod_ret);
        tot_cons += cons_ret;
        tot_prod += prod_ret;
    }
    assert(tot_cons == tot_prod);
}

int main()
{
    ProdConsMain();
    /*      SListDestroy(new_list);
     */
    return 0;
}
