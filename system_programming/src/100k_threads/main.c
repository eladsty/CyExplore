
#include <pthread.h>/* threads */
#include <stdio.h>/* printf */
#include <time.h>/* time */
#include <stdlib.h>

int arr[100000] = {0};

void handler(void *i)
{
    arr[(int)i] = (int)i;
}

void Create100K()
{
    unsigned i = 0;
    int pthread_status = 0;
    pthread_t thr;
 
    for(i = 0; i < 100000; ++i)
    {
        
        pthread_status = pthread_create(&thr, NULL, &handler, (void *)i );
        pthread_detach(thr);
    
    }
}

int main()
{
    unsigned i = 0;
    time_t time1;
    time_t time2;
    
    time1 = clock();
    Create100K(arr); 
    time2 = clock();
    
 
    printf("threads were created in:%f\n",(double)(time2 - time1)/CLOCKS_PER_SEC);
    
    for(i = 0; i < 100000; ++i)
    {
        printf("%d ", arr[i]);
    } 
 
        
    return 0;
}