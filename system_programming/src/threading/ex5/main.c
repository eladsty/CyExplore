
/* 
APPROVED: MICHAEL EVANOV
 */
#include <pthread.h>/* threads */
#include <semaphore.h> /* semaphroes */
#include <stdio.h>  /* printf */
#include <stdlib.h> /* rand */
#include <assert.h> /* assert */

#include "cbuff_read_write_index.h"/* buffer */
 
 
#define MAX_ROUNDS 12
#define BUFFER_SIZE 80


typedef struct thread_struct thr_struct_t;
typedef void *(*producer_action_t)(void* data);
typedef void *(*consumer_action_t)(void* data);
void *ConsumeData(void *data);
void *ProduceData(void *data);

struct thread_struct
{
    pthread_mutex_t *mutex_lock_prod;
    pthread_mutex_t *mutex_lock_cons;
    sem_t *sem_cons;
    sem_t *sem_prod;
    c_buff_t *thr_buffer;
    producer_action_t prod_action_func;
    consumer_action_t cons_action_func;
    void* data;
    size_t data_read_size;
};

void *ProduceData(void *data)
{     
    size_t num = (rand() % 10);
    (void)data;
    return (void *)num;   
}
void *ConsumeData(void *data)
{        
    printf(" %ld \n", (size_t)data); 
    return NULL;   
}

void *Consumer(void *data)
{
    size_t i = 0;
    size_t sum = 0;
    size_t answer = 0;

    while (i < MAX_ROUNDS)
    {
        sem_wait( ((thr_struct_t *)data)->sem_cons );
        pthread_mutex_lock(((thr_struct_t *)data)->mutex_lock_cons);   
        CBuffRead(((thr_struct_t *)data)->thr_buffer, &answer, ((thr_struct_t *)data)->data_read_size );
        pthread_mutex_unlock(((thr_struct_t *)data)->mutex_lock_cons);
        sem_post( ((thr_struct_t *)data)->sem_prod );
      
        ++i;
        sum += answer;   
    }

    return (void*)sum;
}
 
 
void *Producer(void *data)
{
    int i = 0;
    size_t sum = 0;
    size_t test_data = 0;
    while (i < MAX_ROUNDS)
    {
        sem_wait(((thr_struct_t *)data)->sem_prod);
        pthread_mutex_lock(((thr_struct_t *)data)->mutex_lock_prod);
       
        test_data = (size_t)((thr_struct_t *)data)->prod_action_func(NULL);
        CBuffWrite(((thr_struct_t *)data)->thr_buffer, &test_data, 8);   

        pthread_mutex_unlock(((thr_struct_t *)data)->mutex_lock_prod);
        sem_post(((thr_struct_t *)data)->sem_cons);
        
        ++i;
        sum += test_data;
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
    pthread_mutex_t mutex_lock_prod;
    pthread_mutex_t mutex_lock_cons;

    sem_t sem_cons;
    sem_t sem_prod;
    c_buff_t *thr_buffer = NULL;
    
    thr_struct_t thr_struct;
    
    thr_buffer = CBuffCreate(BUFFER_SIZE);

    pthread_mutex_init(&mutex_lock_prod, 0);
    pthread_mutex_init(&mutex_lock_cons, 0);
   

    thr_struct.mutex_lock_prod = &mutex_lock_prod;
    thr_struct.mutex_lock_cons = &mutex_lock_cons;
    thr_struct.sem_cons = &sem_cons;
    thr_struct.sem_prod = &sem_prod;
    thr_struct.thr_buffer = thr_buffer;
    thr_struct.prod_action_func = ProduceData;
    thr_struct.cons_action_func = ConsumeData;
    thr_struct.data = NULL;
    thr_struct.data_read_size = sizeof(size_t);
 
    sem_init(&sem_cons, 0, 0);
    sem_init(&sem_prod, 0, (BUFFER_SIZE / thr_struct.data_read_size) );

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

    pthread_mutex_destroy(&mutex_lock_prod);
    pthread_mutex_destroy(&mutex_lock_cons);
    sem_destroy(&sem_cons);
    sem_destroy(&sem_prod);
    CBuffDestroy(thr_buffer);
}


int main()
{
    ProdConsMain();
    return 0;
}
