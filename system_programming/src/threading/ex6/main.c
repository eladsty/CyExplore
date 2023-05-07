
 
#include <pthread.h>/* threads */
#include <semaphore.h> /* semaphroes */
#include <stdio.h>  /* printf */
#include <stdlib.h> /* rand */
#include <assert.h> /* assert */

  /* 
APPROVED: MICHAEL EVANOV
 */
 
#define CONS_NUM 5
#define STRING_LEN 12
#define MAX_ROUNDS 102

typedef struct thread_struct thr_struct_t;
typedef void *(*producer_action_t)(void* data);
typedef void *(*consumer_action_t)(void* data);
  
 

struct thread_struct
{
    pthread_mutex_t *mutex_lock;
    sem_t *sem_p;
    pthread_cond_t *cond;
    char *str;
    void* data;
};
 
void *Rand_String(char str[STRING_LEN+1])
{     
    const char char_set[] = "abcdefghijklmnopqrstuvwxyz";
    size_t i = 0;
    size_t str_len = STRING_LEN;
    if (str_len) 
    {
        for (i = 0; i < str_len; i++) {
            int key = rand() % (int)(sizeof(char_set) - 1);
            str[i] = char_set[key];
        }
        str[STRING_LEN] = '\0';
    }
    return str;
}


void *Consumer(void *data)
{
    size_t i = 0;
    while (i < MAX_ROUNDS)
    {
        pthread_mutex_lock(((thr_struct_t *)data)->mutex_lock);  
        sem_post(((thr_struct_t *)data)->sem_p);
        pthread_cond_wait(((thr_struct_t *)data)->cond, ((thr_struct_t *)data)->mutex_lock);
        printf("%s\n",((thr_struct_t *)data)->str );
        pthread_mutex_unlock(((thr_struct_t *)data)->mutex_lock);
        ++i;
     }

    return (void*)i;
}
 

/*    for (j = 0; j < CONS_NUM; ++j)
		{
			sem_wait( ((thr_struct_t *)data)->sem_p );
		}
 */

void *Producer(void *data)
{
    int i = 0, j = 0;
    int curr_sem_val = 0;
    while (i < MAX_ROUNDS)
    {
        for(j = 0; j < CONS_NUM; ++j)
        {
            sem_wait(((thr_struct_t *)data)->sem_p );
        }
        pthread_mutex_lock(  ((thr_struct_t *)data)->mutex_lock );  
        Rand_String(((thr_struct_t *)data)->str );                    
        pthread_mutex_unlock(((thr_struct_t *)data)->mutex_lock);
        pthread_cond_broadcast(((thr_struct_t *)data)->cond);
        ++i;
    }
    return (void*)i;
}
 

void ProdConsMain()
{
    size_t i = 0;
    pthread_t cons_thr[CONS_NUM] = {0};
    pthread_t prod_thr;
    pthread_mutex_t mutex_lock;
    sem_t sem;    
    char string[STRING_LEN + 1];
    thr_struct_t thr_struct;
    pthread_cond_t cond;

    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&mutex_lock, 0);
    sem_init(&sem, 0, 0);

    thr_struct.mutex_lock = &mutex_lock;
    thr_struct.cond = &cond;
    thr_struct.sem_p = &sem;
    thr_struct.str = string;
    thr_struct.data = NULL;
 
 
    pthread_create(&prod_thr, NULL, Producer, &thr_struct);

    for (i = 0; i < CONS_NUM; ++i)
    {
        pthread_create(&cons_thr[i], NULL, Consumer, &thr_struct);
    }

    pthread_join(prod_thr, NULL);

    for (i = 0; i < CONS_NUM; ++i)
    {
        pthread_join(cons_thr[i], NULL);
    }
 
    pthread_mutex_destroy(&mutex_lock);
    sem_destroy(&sem);
    pthread_cond_destroy(&cond);
 }


int main()
{
    ProdConsMain();
    return 0;
}
