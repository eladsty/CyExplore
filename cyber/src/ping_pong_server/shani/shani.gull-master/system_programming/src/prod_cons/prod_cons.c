#define _POSIX_C_SOURCE 200112L /* mutex / spinlock */

#include <pthread.h>   /* threads */
#include <semaphore.h> /* semaphore */
#include <unistd.h>	   /* write */

#include "../../include/prod_cons/prod_cons.h"
#include "../../../ds/include/linked_list/linked_list.h"
#include "../../../../Downloads/cbuff_read_write_index.h"

#define MAX_THREADS 150
#define MAX_MESSAGE_LEN 255
#define LINE ((__LINE__) - 1)


static void CheckRet(size_t ret, char *str, int line);
static void CheckRet(size_t ret, char *str, int line)
{
	if (ret)
	{
		printf("error %ld in function:%s() -- in line:%d\n", ret, str, line);
		exit(1);
	}
}





/* -------- Ex 1 --------*/
/* Status : Approved
 * Reviewer : Michael A.
 * Description : single producer write read into a buffer
 * Arguments : ncycles - num of cycles, produce - buffer with raw data, 
 * 				buffer - buffer to read to, buffer_size - size of both buffers.
 * Return : void
 * Time Complexity :
 * Space Complexity :
 */
typedef struct Ex1
{
	pthread_spinlock_t lock;
	size_t ncycles;
	size_t counter;
	void *produce;
	actionfunc_t *consumer;
	actionfunc_t *producer;
}Ex1_data_t;
static void *Ex1Produce(void *arg)
{
	size_t i = 0, ret = 0;
	Ex1_data_t *data = (Ex1_data_t *)arg;
	while (i < data->ncycles)
	{
		ret = pthread_spin_lock(&data->lock);
		CheckRet(ret, "pthread_spin_lock", LINE);
		data->producer(((size_t *)data->produce) + i);
		data->counter += 1;
		++i;
		ret = pthread_spin_unlock(&data->lock);
		CheckRet(ret, "pthread_spin_unlock", LINE);
	}
	return NULL;
}
static void *Ex1Consume(void *arg)
{
	Ex1_data_t *data = (Ex1_data_t *)arg;
	size_t i = 0, ret = 0;
	while (i < data->ncycles)
	{
		ret = pthread_spin_lock(&data->lock);
		CheckRet(ret, "pthread_spin_lock", LINE);
		if (data->counter)
		{
			data->consumer(((size_t *)data->produce) + i);
			++i;
			data->counter -= 1;
		}
		ret = pthread_spin_unlock(&data->lock);
		CheckRet(ret, "pthread_spin_unlock", LINE);
			
	}
	return NULL;
}
void Ex1SingleProdCons(size_t ncycles, void *produce, actionfunc_t Actprod, actionfunc_t Actcons)
{
	pthread_t prod, cons;
	size_t ret = 0;
	
	Ex1_data_t user_data;
	ret = pthread_spin_init(&user_data.lock, PTHREAD_PROCESS_PRIVATE);
	CheckRet(ret, "pthread_spin_init", LINE);

	user_data.produce = produce;
	user_data.ncycles = ncycles;
	user_data.counter = 0;
	user_data.producer = Actprod;
	user_data.consumer = Actcons;

	ret = pthread_create(&prod, NULL, Ex1Produce, &user_data);
	CheckRet(ret, "pthread_create", LINE);
	ret = pthread_create(&cons, NULL, Ex1Consume, &user_data);
	CheckRet(ret, "pthread_create", LINE);
	
	ret = pthread_join(prod, NULL);
	CheckRet(ret, "pthread_join", LINE);
	ret = pthread_join(cons, NULL);
	CheckRet(ret, "pthread_join", LINE);
	ret = pthread_spin_destroy(&user_data.lock);
	CheckRet(ret, "pthread_spin_destroy", LINE);
}

/* -------- Ex 2 --------*/
/* Status : Approved
 * Reviewer : Michael A.
 * Description : multi producer and consumer, critical zone locked with a mutex
 * Arguments : 	void
 * Return : void
 * Time Complexity :
 * Space Complexity :
 */
typedef struct Ex2
{
	pthread_mutex_t mutex;
	slist_t *shared_list;
	size_t ncycles;
	char *produce;
	actionfunc_t *consumer;
}Ex2_data_t;
void *Ex2Produce(void *arg)
{
	Ex2_data_t *data = (Ex2_data_t *)arg;
	size_t i = 0, ret = 0;
	
	while (i < data->ncycles)
	{
		ret = pthread_mutex_lock(&data->mutex);
		CheckRet(ret, "pthread_mutex_lock", LINE);
		SListInsertBefore(SListStart(data->shared_list), (char *)data->produce);
		ret = pthread_mutex_unlock(&data->mutex);
		CheckRet(ret, "pthread_mutex_unlock", LINE);
		++i;
	}
	return NULL;
}
void *Ex2Consume(void *arg)
{
	Ex2_data_t *data = (Ex2_data_t *)arg;
	size_t i = 0, ret = 0;
	slist_iter_t node;

	while (i < data->ncycles)
	{
		ret = pthread_mutex_lock(&data->mutex);
		CheckRet(ret, "pthread_mutex_lock", LINE);
		if (SListSize(data->shared_list))
		{
			node = SListStart(data->shared_list);
			if (NULL == node)
			{
				exit(1);
			}
			data->consumer(SListGetData(node));
			SListDelete(node);
			++i;
		}
		ret = pthread_mutex_unlock(&data->mutex);
		CheckRet(ret, "pthread_mutex_unlock", LINE);
	}
	return NULL;
}
void Ex2MultiProdCons(size_t nconsumer, size_t nproducer, size_t ncycles, char *produce, actionfunc_t ActConsumer)
{
	pthread_t prod[MAX_THREADS], cons[MAX_THREADS];
	Ex2_data_t user_data;
	size_t i = 0, ret = 0;

	ret = pthread_mutex_init(&user_data.mutex, NULL);
	CheckRet(ret, "pthread_mutex_init", LINE);
	user_data.shared_list = SListCreate();
	if (NULL == user_data.shared_list)
	{
		exit(1);
	}
	user_data.ncycles = ncycles;
	user_data.produce = produce;
	user_data.consumer = ActConsumer;
	
	for (i = 0; i < nproducer; ++i)
	{
		ret = pthread_create(&prod[i], NULL, Ex2Produce, &user_data);
		CheckRet(ret, "pthread_create", LINE);
	}
	for (i = 0; i < nconsumer; ++i)
	{
		ret = pthread_create(&cons[i], NULL, Ex2Consume, &user_data);
		CheckRet(ret, "pthread_create", LINE);
	}
	for (i = 0; i < nproducer; ++i)
	{
		ret = pthread_join(prod[i], NULL);
		CheckRet(ret, "pthread_join", LINE);
	}
	for (i = 0; i < nconsumer; ++i)
	{
		ret = pthread_join(cons[i], NULL);
		CheckRet(ret, "pthread_join", LINE);
	}

	ret = pthread_mutex_destroy(&user_data.mutex);
	CheckRet(ret, "pthread_mutex_destroy", LINE);
	SListDestroy(user_data.shared_list);
}

/* -------- Ex 3 --------*/
/* Status : Approved
 * Reviewer : Michael A.
 * Description : multi producer and consumer, critical zone locked with a mutex
 * 					semaphore synchronizes consumer access.
 * Arguments : 	void
 * Return : void
 * Time Complexity :
 * Space Complexity :
 */
typedef struct Ex3
{
	pthread_mutex_t mutex;
	sem_t sem;
	slist_t *shared_list;
	size_t ncycles;
	char *produce;
	actionfunc_t *consumer;
}Ex3_data_t;
void *Ex3Produce(void *arg)
{
	Ex3_data_t *data = (Ex3_data_t *)arg;
	size_t ret = 0, i = 0;
	while (i < data->ncycles)
	{
		ret = pthread_mutex_lock(&data->mutex);
		CheckRet(ret, "pthread_mutex_lock", LINE);
		SListInsertBefore(SListStart(data->shared_list), (char *)data->produce);
		ret = sem_post(&data->sem);
		CheckRet(ret, "sem_post", LINE);
		ret = pthread_mutex_unlock(&data->mutex);
		CheckRet(ret, "pthread_mutex_unlock", LINE);
		++i;
	}
	return NULL;
}
void *Ex3Consume(void *arg)
{
	Ex3_data_t *data = (Ex3_data_t *)arg;
	size_t ret = 0, i = 0;
	slist_iter_t node;

	while (i < data->ncycles)
	{
		ret = sem_wait(&data->sem);
		CheckRet(ret, "sem_wait", LINE);
		ret = pthread_mutex_lock(&data->mutex);
		CheckRet(ret, "pthread_mutex_lock", LINE);
		node = SListStart(data->shared_list);
		if (NULL == node)
		{
			exit(1);
		}
		data->consumer(SListGetData(node));
		SListDelete(node);
		ret = pthread_mutex_unlock(&data->mutex);
		CheckRet(ret, "pthread_mutex_unlock", LINE);
		++i;
	}
	return NULL;
}
void Ex3MultiProdCons(size_t nconsumer, size_t nproducer, size_t ncycles, char *produce, actionfunc_t ActConsumer)
{
	Ex3_data_t user_data;
	pthread_t prod[MAX_THREADS], cons[MAX_THREADS];
	size_t i = 0, ret = 0;

	user_data.consumer = ActConsumer;
	user_data.ncycles = ncycles;
	user_data.produce = produce;
	user_data.shared_list = SListCreate();
	if (NULL == user_data.shared_list)
	{
		exit(1);
	}
	ret = pthread_mutex_init(&user_data.mutex, NULL);
	CheckRet(ret, "pthread_mutex_init", LINE);
	ret = sem_init(&user_data.sem, 0, 0);
	CheckRet(ret, "sem_init", LINE);

	for (i = 0; i < nproducer; ++i)
	{
		ret = pthread_create(&prod[i], NULL, Ex3Produce, &user_data);
		CheckRet(ret, "pthread_create", LINE);
	}
	for (i = 0; i < nconsumer; ++i)
	{
		ret = pthread_create(&cons[i], NULL, Ex3Consume, &user_data);
		CheckRet(ret, "pthread_create", LINE);
	}
	for (i = 0; i < nproducer; ++i)
	{
		ret = pthread_join(prod[i], NULL);
		CheckRet(ret, "pthread_join", LINE);
	}
	for (i = 0; i < nconsumer; ++i)
	{
		ret = pthread_join(cons[i], NULL);
		CheckRet(ret, "pthread_join", LINE);
	}
	
	ret = pthread_mutex_destroy(&user_data.mutex);
	CheckRet(ret, "pthread_mutex_destroy", LINE);
	ret = sem_destroy(&user_data.sem);
	CheckRet(ret, "sem_destroy", LINE);
	SListDestroy(user_data.shared_list);
}

/* Status : approved
 * Reviewer : michael a
 * Description : writes and reads from log using 2 semaphores and a mutex.
 * Arguments : 	void
 * Return : void
 * Time Complexity :
 * Space Complexity :
 */

typedef struct Ex4
{
	c_buff_t *log;
	pthread_mutex_t mutex;
	sem_t read_sem;
	sem_t write_sem;
	char **produce;
	ssize_t nbytes;
	actionfunc_t *consumer;
}Ex4_data_t;
void *Ex4Produce(void *arg)
{
	Ex4_data_t *data = (Ex4_data_t *)arg;
	size_t ret = 0;
	
	ret = pthread_mutex_lock(&data->mutex);
	CheckRet(ret, "pthread_mutex_lock", LINE);
	ret = sem_wait(&data->write_sem);
	CheckRet(ret, "sem_wait", LINE);
	if (data->nbytes != CBuffWrite(data->log, data->produce, data->nbytes))
	{
		exit(1);
	}
	ret = sem_post(&data->read_sem);
	CheckRet(ret, "sem_post", LINE);
	ret = pthread_mutex_unlock(&data->mutex);
	CheckRet(ret, "pthread_mutex_unlock", LINE);
	return NULL;
}
void *Ex4Consume(void *arg)
{
	Ex4_data_t *data = (Ex4_data_t *)arg;
	size_t ret = 0;
	char buffer[MAX_MESSAGE_LEN];

	ret = pthread_mutex_lock(&data->mutex);
	CheckRet(ret, "pthread_mutex_lock", LINE);
	ret = sem_wait(&data->read_sem);
	CheckRet(ret, "sem_wait", LINE);
	CBuffRead(data->log, buffer, data->nbytes);
	ret = sem_post(&data->write_sem);
	CheckRet(ret, "sem_post", LINE);
	ret = pthread_mutex_unlock(&data->mutex);
	CheckRet(ret, "pthread_mutex_unlock", LINE);
	data->consumer(buffer);
	return NULL;
}
void Ex4FSQ(size_t nconsumer, size_t nproducer, size_t ncycles, size_t nbytes, char **produce, actionfunc_t ActConsumer)
{
	pthread_t prod[MAX_THREADS], cons[MAX_THREADS];
	size_t i = 0, ret = 0;
	Ex4_data_t user_data;

	user_data.log = CBuffCreate(ncycles * nbytes);
	if (NULL == user_data.log)
	{
		exit(1);
	}
	ret = pthread_mutex_init(&user_data.mutex, NULL);
	CheckRet(ret, "pthread_mutex_init", LINE);
	ret = sem_init(&user_data.read_sem, 0, 0);
	CheckRet(ret, "sem_init", LINE);
	ret = sem_init(&user_data.write_sem, 0, ncycles);
	CheckRet(ret, "sem_init", LINE);
	user_data.nbytes = nbytes;
	user_data.consumer = ActConsumer;
	user_data.produce = produce;
	
	for (i = 0; i < nproducer; ++i)
	{
		ret = pthread_create(&prod[i], NULL, Ex4Produce, &user_data);
		CheckRet(ret, "pthread_create", LINE);
	}
	for (i = 0; i < nconsumer; ++i)
	{
		ret = pthread_create(&cons[i], NULL, Ex4Consume, &user_data);
		CheckRet(ret, "pthread_create", LINE);
	}
	for (i = 0; i < nproducer; ++i)
	{
		ret = pthread_join(prod[i], NULL);
		CheckRet(ret, "pthread_join", LINE);
	}
	for (i = 0; i < nconsumer; ++i)
	{
		ret = pthread_join(cons[i], NULL);
		CheckRet(ret, "pthread_join", LINE);
	}

	ret = pthread_mutex_destroy(&user_data.mutex);
	CheckRet(ret, "pthread_mutex_destroy", LINE);
	ret = sem_destroy(&user_data.read_sem);
	CheckRet(ret, "sem_destroy", LINE);
	ret = sem_destroy(&user_data.write_sem);
	CheckRet(ret, "sem_destroy", LINE);
	CBuffDestroy(user_data.log);
}
/* Status : approved
 * Reviewer : michael a
 * Description : writes and reads from log using 2 semaphores and 2 mutexes.
 * Arguments : 	void
 * Return : void
 * Time Complexity :
 * Space Complexity :
 */
typedef struct Ex5
{
	c_buff_t *log;
	pthread_mutex_t read_mutex;
	pthread_mutex_t write_mutex;
	sem_t read_sem;
	sem_t write_sem;
	char **produce;
	ssize_t nbytes;
	actionfunc_t *consumer;
}Ex5_data_t;
void *Ex5Produce(void *arg)
{
	Ex5_data_t *data = (Ex5_data_t *)arg;
	size_t ret = 0;
	ret = pthread_mutex_lock(&data->write_mutex);
	CheckRet(ret, "pthread_mutex_lock", LINE);
	ret = sem_wait(&data->write_sem);
	CheckRet(ret, "sem_wait", LINE);
	if (data->nbytes != CBuffWrite(data->log, data->produce, data->nbytes))
	{
		exit(1);
	}
	ret = sem_post(&data->read_sem);
	CheckRet(ret, "sem_post", LINE);
	ret = pthread_mutex_unlock(&data->write_mutex);
	CheckRet(ret, "pthread_mutex_unlock", LINE);
	return NULL;
}
void *Ex5Consume(void *arg)
{
	Ex5_data_t *data = (Ex5_data_t *)arg;
	size_t ret = 0;
	char buffer[MAX_MESSAGE_LEN];

	ret = pthread_mutex_lock(&data->read_mutex);
	CheckRet(ret, "pthread_mutex_lock", LINE);
	ret = sem_wait(&data->read_sem);
	CheckRet(ret, "sem_wait", LINE);
	CBuffRead(data->log, buffer, data->nbytes);
	ret = sem_post(&data->write_sem);
	CheckRet(ret, "sem_post", LINE);
	ret = pthread_mutex_unlock(&data->read_mutex);
	CheckRet(ret, "pthread_mutex_unlock", LINE);
	data->consumer(buffer);
	return NULL;
}
void Ex5FSQ(size_t nconsumer, size_t nproducer, size_t ncycles, size_t nbytes, char **produce, actionfunc_t ActConsumer)
{
	Ex5_data_t user_data;
	pthread_t prod[MAX_THREADS], cons[MAX_THREADS];
	
	size_t i = 0, ret = 0;
	user_data.log = CBuffCreate(ncycles * nbytes);
	if (NULL == user_data.log)
	{
		exit(1);
	}

	ret = pthread_mutex_init(&user_data.write_mutex, NULL);
	CheckRet(ret, "pthread_mutex_init", LINE);
	ret = pthread_mutex_init(&user_data.read_mutex, NULL);
	CheckRet(ret, "pthread_mutex_init", LINE);
	ret = sem_init(&user_data.read_sem, 0, 0);
	CheckRet(ret, "sem_init", LINE);
	ret = sem_init(&user_data.write_sem, 0, ncycles);
	CheckRet(ret, "sem_init", LINE);

	user_data.nbytes = nbytes;
	user_data.consumer = ActConsumer;
	user_data.produce = produce;
	
	for (i = 0; i < nproducer; ++i)
	{
		ret = pthread_create(&prod[i], NULL, Ex5Produce, &user_data);
		CheckRet(ret, "pthread_create", LINE);
	}
	for (i = 0; i < nconsumer; ++i)
	{
		ret = pthread_create(&cons[i], NULL, Ex5Consume, &user_data);
		CheckRet(ret, "pthread_create", LINE);
	}
	for (i = 0; i < nproducer; ++i)
	{
		ret = pthread_join(prod[i], NULL);
		CheckRet(ret, "pthread_join", LINE);
	}
	for (i = 0; i < nconsumer; ++i)
	{
		ret = pthread_join(cons[i], NULL);
		CheckRet(ret, "pthread_join", LINE);
	}

	ret = pthread_mutex_destroy(&user_data.write_mutex);
	CheckRet(ret, "pthread_mutex_destroy", LINE);
	ret = pthread_mutex_destroy(&user_data.read_mutex);
	CheckRet(ret, "pthread_mutex_destroy", LINE);
	ret = sem_destroy(&user_data.read_sem);
	CheckRet(ret, "sem_destroy", LINE);
	ret = sem_destroy(&user_data.write_sem);
	CheckRet(ret, "sem_destroy", LINE);
	CBuffDestroy(user_data.log);
}

/* Status : approved
 * Reviewer : michael a
 * Description : one producer, multi consumers, broadcasting messages.
 * Arguments : 	void
 * Return : void
 * Time Complexity :
 * Space Complexity :

 */
typedef struct Ex6 
{
	pthread_mutex_t mutex; /* pointer to array of mutex pointers */
	sem_t sem; /* pointer to array of sem pointers */
	size_t ncycle; /* number of thread cycles */
	size_t buffer_size; /* size of buffer to read/write */
	size_t nconsumer;
	pthread_cond_t cond_var; /* pointer to condition variable */
	actionfunc_t *ActConsumer; /* action function pointer */
	char **produce; /* data from user to produce */
	size_t counter; /* self explenatory */
	char *buffer;
}Ex6_data_t;
void *Ex6BarrierProduce(void *arg)
{
	size_t i = 0, ret = 0;
	Ex6_data_t *data = (Ex6_data_t *)arg;
	while(i < data->ncycle)
	{
		/* wait for all consumer to reach barrier */
		ret = sem_wait(&data->sem);
		CheckRet(ret, "sem_wait", LINE);
		/*get produce from user and do whateve on it*/
		ret = pthread_mutex_lock(&data->mutex);
		CheckRet(ret, "pthread_mutex_lock", LINE);
		/* write to buffer */
		memcpy(data->buffer, data->produce + (i * 15), 15);
		++i;	
		/* broadcast */
		ret = pthread_cond_broadcast(&data->cond_var);
		CheckRet(ret, "pthread_cond_broadcast", LINE);
		ret = pthread_mutex_unlock(&data->mutex);
		CheckRet(ret, "pthread_mutex_unlock", LINE);
	}
	return NULL;
}
void *Ex6BarrierConsume(void *arg)
{
	size_t i = 0, ret = 0;
	Ex6_data_t *data = (Ex6_data_t *)arg;
	while(i < data->ncycle)
	{
		/* immediate wait for broadcast */
		ret = pthread_mutex_lock(&data->mutex);
		CheckRet(ret, "pthread_mutex_lock", LINE);
		/* counter */
		++data->counter;
		/* when steps in, checks if all consumers went in, inform prodecer via semaphore and reset counter */
		if (data->nconsumer == data->counter)
		{
			ret = sem_post(&data->sem);
			CheckRet(ret, "sem_post", LINE);
			data->counter = 0;
		}
		ret = pthread_cond_wait(&data->cond_var, &data->mutex);
		CheckRet(ret, "thread_cond_wait", LINE);
		data->ActConsumer(&data->buffer);
		ret = pthread_mutex_unlock(&data->mutex);
		CheckRet(ret, "pthread_mutex_unlock", LINE);
		++i;
	}
	return NULL;
}
void Ex6Barrier(const size_t consumers, const size_t data_len, char **produce, const size_t ncycles, actionfunc_t *ActConsumer)
{
	Ex6_data_t user_data;
	size_t ret;

	pthread_t prod, cons[MAX_THREADS];
	size_t i = 0;

	char buffer[15];

	ret = sem_init(&user_data.sem, 0, 0);
	CheckRet(ret, "sem_init", LINE);
	ret = pthread_mutex_init(&user_data.mutex, NULL);
	CheckRet(ret, "pthread_mutex_init", LINE);
	ret = pthread_cond_init(&user_data.cond_var, NULL);
	CheckRet(ret, "pthread_cond_init", LINE);

	user_data.nconsumer = consumers;
	user_data.ncycle = ncycles;
	user_data.buffer_size = data_len;
	user_data.produce = produce;
	user_data.ActConsumer = ActConsumer;
	user_data.counter = 0;
	user_data.buffer = buffer;
	
	for (i = 0; i < consumers; ++i)
	{
		ret = pthread_create(&cons[i], NULL, Ex6BarrierConsume, &user_data);
		CheckRet(ret, "pthread_create", LINE);
	}
	ret = pthread_create(&prod, NULL, Ex6BarrierProduce, &user_data);
	CheckRet(ret, "pthread_create", LINE);
	for (i = 0; i < consumers; ++i)
	{
		ret = pthread_join(cons[i], NULL);
		CheckRet(ret, "pthread_join", LINE);
	}
	ret = pthread_join(prod, NULL);
	CheckRet(ret, "pthread_join", LINE);
	ret = sem_destroy(&user_data.sem);
	CheckRet(ret, "sem_destroy", LINE);
	ret = pthread_cond_destroy(&user_data.cond_var);
	CheckRet(ret, "pthread_cond_destroy", LINE);
	ret = pthread_mutex_destroy(&user_data.mutex);
	CheckRet(ret, "pthread_mutex_destroy", LINE);
}
