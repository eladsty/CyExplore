
#include <pthread.h>/* threads */
#include <stdio.h>  /* printf */
#include <time.h>   /* time */
#include <stdlib.h>
#include <omp.h>  /* OpenMP */



#define MAX_THREADS2 32000 /* actual: 32752, ulimit -u : 62398 */
#define MAX_THREADS 10 /* actual: 32752, ulimit -u : 62398 */

#define NUMBER 1232000000
#define RANGE (NUMBER / MAX_THREADS) /*  + (NUMBER % MAX_THREADS)) */

size_t arr[MAX_THREADS] = {0};
void *handler(void *i)
{
    size_t shared_sum = 0;
    size_t j = 0;
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
    unsigned i = 0;
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

int main()
{
     unsigned i = 0;
     
     Create100K(arr); 
      simple_loop();  
  
    
    return 0;
}