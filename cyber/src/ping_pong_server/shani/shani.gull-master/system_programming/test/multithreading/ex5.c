#include <pthread.h> /* thread */
#include <time.h> /* time */
#include <omp.h> /* openMP */
#include "../../include/multithreading/multithreading.h"
#define HK 100000
#define NUMBER (1000000000)
#include "../../include/multithreading/multithreading.h"
void EXfive()
{
	time_t start, end;
	int i = 0;
	size_t sum = 0;
	time(&start);
	#pragma omp parallel for
	for (i = 1; i <= NUMBER; ++i)
	{
		if (0 == NUMBER % i)
		{
			sum += i;
		}
	}
	time(&end);
	printf("thread time: %ld\n", end - start);
	printf("%ld\n", sum);
}
int main(void)
{
	EXfive();
	return (0);
}
