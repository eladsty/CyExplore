
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
#define FREE 0
#define LOCKED 1


size_t arr[MAX_THREADS] = {0};

int global_var = 44;

void *Mem_Map_thread(void *i)
{
    size_t shared_sum = 0;
    size_t j = 0;
    size_t thread_stack = 20+i;
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
        sleep(1);
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
Approved by: Mr Evanov.M

------------------------------------------ */
int info_array[1] = {0};
int lock = 0;

void *Consumer()
{
    int i = 0;

    while (1) 
    {
         if(1 == lock)
        {
            printf("%d \n",info_array[0]);
            --lock;
        }
        printf("lock is %d\n",lock);

    }    
    return NULL;
 }

void *Producer()
{
    int i = 0;
    int rand_n = 0;
 
     while (1) 
    {
        if(0 == lock)
        {
            rand_n = (rand() % 10) + 1;
            info_array[0] = rand_n;

            ++lock;
        }
        printf("lock is %d\n",lock);
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
     unsigned i = 0;
     
    /*
      Create100K(arr); 
      simple_loop();   
      
      */
/*   Mem_Mapping(); */    

    ProdConsMain();

    return 0;
}
