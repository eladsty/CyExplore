#include <pthread.h>/* threads */
#include <threads.h>/* threads */

#include <stdio.h>  /* printf */
#include <time.h>   /* time */
#include <stdlib.h>
#include <omp.h>  /* OpenMP */
#include <assert.h> /* assert */


#define MAX_THREADS2 32000 /* actual: 32752, ulimit -u : 62398 */
#define MAX_THREADS 10 /* actual: 32752, ulimit -u : 62398 */

#define NUMBER 1232000000
#define RANGE (NUMBER / MAX_THREADS) /*  + (NUMBER % MAX_THREADS)) */
#define UNLOCK 0
#define LOCKED 1
#define INFO_ARR_SIZE 5
#define EMPTY 0
#define MAX_ROUNDS 100000

size_t arr[MAX_THREADS] = {0};

int global_var = 44;

void *Mem_Map_thread(void *i)
{
    size_t shared_sum = 0;
    size_t j = 0;
    size_t thread_stack = 20 + (size_t)i;
    int *heap_var = malloc(4);
    static thread_local int thr_local = 88;
 
    *heap_var = 33;
 
}

void Mem_Mapping()
{
    unsigned i = 0;
    int pthread_status = 0;
    pthread_t thread_arr[5] = {0};
 
    for (i = 0; i < 5; ++i)
    {
        pthread_status = pthread_create(&thread_arr[i], NULL, Mem_Map_thread, (void *)i);
        if (0 != pthread_status)
        {
            printf("error creating threads");
        }
    }

    for (i = 0; i < 5; ++i)
    {
        pthread_join( thread_arr[i], (void *)&i );
    }  
 }


void *handler(void *i)
{
    size_t shared_sum = 0;
    size_t j = 0;
    size_t thread_stack = 20;
  
    arr[(size_t)i] = (size_t)i;
    for (j = 1; j <= RANGE; ++j)
    {
        if (0 == ((size_t)NUMBER % (j + (RANGE * (size_t)i))))
        {
            shared_sum += (j + (RANGE * (size_t)i));
        }
    }
    
     return (void *)shared_sum;
}

void Create100K()
{
    size_t i = 0;
    long sum = 0;
    int pthread_status = 0;
    pthread_t thread_arr[MAX_THREADS] = {0};
    long temp = 0;

    for (i = 0; i <= MAX_THREADS; ++i)
    {
        pthread_status = pthread_create(&thread_arr[i], NULL, handler, (void *)i);
        if (0 != pthread_status)
        {
            printf("error creating threads");
        }
    }

    for (i = 0; i <= MAX_THREADS; ++i)
    {
        pthread_join(thread_arr[i], (void *)&temp);
        sum += temp;
    }  
    printf("our %ld\n",sum);
}

void simple_loop()
{
    int i = 0;
    size_t shared_sum2 = 0;
 
    #pragma omp parallel for
    for (i = 1; i <= NUMBER; ++i)
    {
        if (0 == ((size_t)NUMBER % i))
        {
            shared_sum2 += i;
        }
    }
    printf("using a simple loop, result i %ld", shared_sum2);
}

/* -------------------------------
Approved by: Evanov.M EX1

------------------------------------------ */
  void *Consumer(void *info_array)
{
    int i = 1;
    unsigned consumer_rounds = 0;
    unsigned j = 0;
     while (j < MAX_ROUNDS) 
    {
        if(UNLOCK == *(int *)info_array)
        {
            *(int *)info_array = LOCKED;
            ++consumer_rounds;
            if(EMPTY != *( ((int *)(info_array) + 2)) ) 
            {
                while(i <=  INFO_ARR_SIZE)
                {

                     printf("%d \n", *( ((int *)(info_array) + i)) );
                   *( ((int *)(info_array) + i)) = EMPTY;
                    ++i;
                }
            }
            *(int *)info_array = UNLOCK;
             i = 1;
        }

        ++j;
    }    
    printf("total cons rounds: %d \n ", consumer_rounds);
    return NULL;
 }

void *Producer(void *info_array)
{
    int i = 1;
    int new_info = 0;  
    unsigned producer_rounds = 0;
    unsigned j = 0;
    while (j < MAX_ROUNDS) 
    {
        if(UNLOCK == *(int *)info_array)
        {
            *(int *)info_array = LOCKED;
            ++producer_rounds;
            if(EMPTY == *((int *)(info_array) + 2))
            {
                while(i <= INFO_ARR_SIZE)
                {
                    new_info = (int)(rand() % 10);
                    *((int *)(info_array) + i) = (new_info + 1);
                    ++i;
                }
            }

            *(int *)info_array = UNLOCK;
            i = 1;
        }
        ++j;
    }  
    printf("total rounds: %d \n ", producer_rounds);
    return NULL;
}


void ProdConsMain()
{
    pthread_t cons_thr ;
    pthread_t prod_thr;
    int arr[1] = {0};
    int pshared = 0;
    int info_array[INFO_ARR_SIZE + 1] = {0};

    pthread_create(&prod_thr, NULL, Producer, &info_array );
    pthread_create(&cons_thr, NULL, Consumer, &info_array );


    pthread_join(prod_thr, NULL);
    pthread_join(cons_thr, NULL);
 

  }


int main()
{     
    /*
      Create100K(arr); 
      simple_loop();   
      
      */
/*   Mem_Mapping(); */    

    ProdConsMain();

    return 0;
}

