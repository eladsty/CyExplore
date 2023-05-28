#include <pthread.h> /* thread */
#include <threads.h>
#include "../../include/multithreading/multithreading.h"
#define HK 100000
#define MAX_THREAD (10)
#define NUMBER (1000000000)
#define RANGE (NUMBER / MAX_THREAD)
long *var = 0;
pthread_key_t key;
static thread_local long v = 5;
long s[HK];
/* Status : 
 * Reviewer : 
 * Description : 
	
 * Arguments : 
	
 * Return : 
 * Time Complexity :
 * Space Complexity :
 */
static int OK()
{
	int i = 0;
	for (; i < MAX_THREAD; ++i)
	{
		if (s[i] != i)
		{
			return i;
		}
	}
	return 0;
}

void *Increment(void *arg)
{
	size_t i = 1, sum_of_deviders = 0;
	
	void *key_test;
	void *shani = malloc(1);
	free(shani);
	key_test = pthread_getspecific(key);

	for (i = (size_t)arg + 1; i <= (size_t)arg + RANGE; ++i)
	{
		if (0 == NUMBER % i)
		{
			sum_of_deviders += i;
		}
	}
	if ((0 != pthread_setspecific(key, &v)))
	{
		v += 10;
	}

	printf("before: %ld\n", v);
	/*s[(long)arg] = (long)arg;*/
	return (void *)sum_of_deviders;
}
void HundredK()
{
	pthread_t comp[MAX_THREAD] = {0};
	pthread_attr_t attr;
	size_t i = 1;
	int ok = -1;
	size_t sum = 0, num = 0;
	pthread_key_create(&key, NULL);
	pthread_attr_init(&attr);
	/*pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);*/

	for (i = 0; i < MAX_THREAD; ++i)
	{
		ok = pthread_create(&comp[i], &attr, Increment, (void *)(i * RANGE));
		/*if (ok)
		{
			perror("failed successfully");
		}*/
	}
	for (i = 0; i < MAX_THREAD; ++i)
	{
		pthread_join(comp[i], (void **)&sum);
		num += sum;
	}
	printf("%ld\n", num);
	/*pthread_exit(NULL);*/
}

