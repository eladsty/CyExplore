#define _POSIX_C_SOURCE 200112L /* for locks */
 
#include <pthread.h>
#include <stddef.h>
#include <stdio.h>

#define MAX_NUM (6)



int info_array[MAX_NUM] = {0};

pthread_spinlock_t  lock_status = 0;

size_t g_buff = 0;
int g_stat = 0;

void *Producer(void *args)
{
	size_t i = 0;

	while (MAX_NUM > i)
	{
		pthread_spin_lock(&g_lock_stat);
		if (0 == g_stat)
		{
/* 			pthread_spin_lock(&g_lock_message); */
			g_buff = i;
/* 			pthread_spin_unlock(&g_lock_message); */
			g_stat = 1;
			++i;
		}
		pthread_spin_unlock(&g_lock_stat);
	}
	(void)args;
	return 0;
}
void *Consumer(void *args)
{
	size_t i = 0;

	while (MAX_NUM > i)
	{
		pthread_spin_lock(&g_lock_stat);
		if (1 == g_stat)
		{
/* 			pthread_spin_lock(&g_lock_message); */
			printf(" %lu ", g_buff);
/* 			pthread_spin_unlock(&g_lock_message); */
			g_stat = 0;
			++i;
		}
		pthread_spin_unlock(&g_lock_stat);
	}
	(void)args;
	return 0;
}

int main()
{
	pthread_t producer_tr = 0;
	pthread_t consumer_tr = 0;
	pthread_attr_t attr = { 0 };

	/* if (pthread_spin_init(&g_lock_message, PTHREAD_PROCESS_PRIVATE))
	{
		perror("spin init failed");
	} */
	if (pthread_spin_init(&g_lock_stat, PTHREAD_PROCESS_PRIVATE))
	{
		perror("spin init failed");
	}

	pthread_attr_init(&attr);
	pthread_create(&producer_tr, &attr, Producer, NULL);
	pthread_create(&consumer_tr, &attr, Consumer, NULL);
	pthread_attr_destroy(&attr);
	
	pthread_join(producer_tr, NULL);
	pthread_join(consumer_tr, NULL);

	pthread_spin_destroy(&g_lock_stat);
/* 	pthread_spin_destroy(&g_lock_message); */

	return 0;
}


int main()
{


    return 0;
}