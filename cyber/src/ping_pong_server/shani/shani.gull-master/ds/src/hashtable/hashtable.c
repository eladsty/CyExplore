#include <math.h> /* pow & sqrt */
#include "../../include/hashtable/hashtable.h"
#include "../../include/linked_list/linked_list.h"

#define EPSILON 0.5
#define RESIZEUP 1.65
#define RESIZEDOWN 0.45

typedef struct bucket bucket_t;
static void Chaching(hash_table_t *table, void *data);
static double direction[2] = {RESIZEUP, RESIZEDOWN};

struct hash
{
	hashfunc_t HashFunction;
	size_t number_of_buckets;
	compfunc_t cmp;
	slist_t **hash_table;
};
struct bucket
{
	void *value;
};


static size_t HashedKey(hash_table_t *table, void *data)
{
	return (table->HashFunction((void *)data) % table->number_of_buckets); 
}
static void Eliminate(size_t index, slist_t **slist_arr)
{
	size_t i = 0;
	for (; i < index; ++i)
	{
		SListDestroy(slist_arr[i]);
	}
}
/* Status : Aproved
 * Reviewer : Michael A
 * Description : creates a hash table, allocating storage for the table 
 * 					managing unit, and to any number of indexes requested by
 * 					user. initializing all linked lists in each bucket. if a 
 * 					list init fails, needs to free the allocated lists and hash.
 * Arguments : table size is number of indexes user requests, a hashfunction and
 * 				a compare function to nest in the managing unit for future use.	
 * Return : NULL if malloc did not succeed, else a pointer to tha tbale.
 */
hash_table_t *HASHCreate(size_t table_size, hashfunc_t HashFunction, 
							compfunc_t cmp)
{
	hash_table_t *hash = (hash_table_t *)malloc(sizeof(hash_table_t) + (table_size * sizeof(slist_t *)));
	size_t i = 0;
	if (NULL == hash)
	{
		return NULL;
	}
	hash->cmp = cmp;
	hash->HashFunction = HashFunction;
	hash->number_of_buckets = table_size;
	hash->hash_table = (slist_t **)((char *)hash + sizeof(hash_table_t));
	for (i = 0; i < table_size; ++i)
	{
		hash->hash_table[i] = SListCreate();
		if (NULL == hash->hash_table[i])
		{
			Eliminate(i, hash->hash_table);
			HASHDestroy(hash);
			return NULL;
		}
	}
	return hash;
}



/* Status : Aproved
 * Reviewer : Michael A
 * Description : destroys a hash table
 * Arguments : pointer to hash table	
 * Return : nothing
 */
void HASHDestroy(hash_table_t *table)
{
	Eliminate(table->number_of_buckets, table->hash_table);
	free(table);
	table = NULL;
	return;
}


/* Status : Aproved
 * Reviewer : Michael A
 * Description : finds each linked list's first and last iterators and
 * 					activates a linked list foreach function on every
 * 					linked list in the hash table	
 * Arguments : pointer to table, action function, and a parameter.	
 * Return : 1 if fails, 0 if succeeds.
 */
int HASHForEach(hash_table_t *table, int (*ActionFunc)(void *data ,void *param), void *param)
{
	slist_iter_t start = NULL, end = NULL;
	int success_indicator = 0;
	size_t i = 0;

	while (!success_indicator && i < table->number_of_buckets)
	{
		start = SListStart(table->hash_table[i]);
		end = SListEnd(table->hash_table[i]);
		success_indicator = SListForEach(start, end, ActionFunc, param);
		++i;
	}
	return success_indicator;
}


/* Status : Aproved
 * Reviewer : Michael A
 * Description : inserts new data to hash table
 * Arguments : pointer to table, pointer to data	
 * Return : 0 success, 1 fail.
 */
int HASHInsert(hash_table_t *table, const void *data)
{
	size_t key = 0;
	slist_iter_t insert_before = NULL;
	key = table->HashFunction((void *)data) % table->number_of_buckets;
	insert_before = SListStart(table->hash_table[key]);
	insert_before = SListInsertBefore(insert_before, data);
	if (NULL == insert_before)
	{
		return 1;
	}
	return 0;
}

static int SizeCounter(void *data, void *param)
{
	*(size_t *)param += 1;
	(void)data;
	return 0;
}
/* Status : Aproved
 * Reviewer : Michael A
 * Description : uses foreach to count elements in hash table	
 * Arguments : pointer to table	
 * Return : number of elements in hash table
 */
size_t HASHSize(const hash_table_t *table)
{
	size_t size = 0;
	HASHForEach((hash_table_t *)table, SizeCounter, &size);
	return size;
}

/* Status : Aproved
 * Reviewer : Michael A 
 * Description : removes an element from hash table	
 * Arguments : pointer to table, pointer to data to find and remove	
 * Return : 0 success, 1 fail.
 */
int HASHRemove(hash_table_t *table, const void *data)
{
	slist_iter_t to_remove = NULL, start = NULL, end = NULL;
	size_t key = (table->HashFunction((void *)data) % table->number_of_buckets);
	start = SListStart(table->hash_table[key]);
	end = SListEnd(table->hash_table[key]);
	to_remove = SListFind(start, end, (is_match_t)table->cmp, (void *)data);
	if (to_remove == end)
	{
		return 1;
	}
	SListDelete(to_remove);
	return 0;
}

/* once foreach encounters an element, a fail status is returned by
	this function and stops the foreach action. */
static int EmptyOrNot(void *data, void *param)
{
	(void)param;
	(void)data;
	return 1;
}
/* Status : Aproved
 * Reviewer : Michael A
 * Description : checks if hashtable is empty
 * Arguments : 	pointer to hash table.
 * Return : 0 of fail, 1 if succeed.
 */
int HASHIsEmpty(const hash_table_t *table)
{
	int indicator = 0;
	indicator = HASHForEach((hash_table_t *)table, EmptyOrNot, NULL);
	return indicator;
}

/* Status : Aproved
 * Reviewer : Michael A
 * Description : finds element in table	
 * Arguments : pointer to table, pointer to data to find	
 * Return : the pointer to the data if found, NULL if not
 */
void *HASHFind(const hash_table_t *table, const void *data)
{
	void *result = NULL;
	slist_iter_t find = NULL;
	slist_iter_t start = NULL, end = NULL;
	size_t key = HashedKey((hash_table_t *)table, (void *)data);
	start = SListStart(table->hash_table[key]);
	end = SListEnd(table->hash_table[key]);
	find = SListFind(start, end, (is_match_t)table->cmp, (void *)data);
	result = SListGetData(find);
	if (find == end)
	{
		return NULL;
	}
	Chaching((hash_table_t *)table, (void *)data);
	return result;
}



/* load factor is optimal between 0.6 and 0.75 */
static size_t BestSize(hash_table_t *table, resize updown)
{
	double temp = (table->number_of_buckets * direction[updown]) + EPSILON;
	return (size_t)temp;
}
int CopyValue(void *old, void *new)
{
	if (HASHInsert(new, old))
	{
		return 1;
	}
	return 0;
}
void SwapTables(hash_table_t **table1, hash_table_t **table2)
{
	hash_table_t *temp = NULL;
	temp = *table1;
	*table1 = *table2;
	*table2 = temp;
}
static hash_table_t *ResizenRehash(hash_table_t* old, resize updown)
{
	hash_table_t *new = NULL;
	size_t new_size = 0;
	int indicator = 0;
	new_size = BestSize(old, direction[updown]);
	new = HASHCreate(new_size, old->HashFunction, old->cmp);
	if (!new)
	{
		return old;
	}
	indicator += HASHForEach(old, CopyValue, new);
	if (indicator)
	{
		HASHDestroy(new);
		return old;
	}
	SwapTables(&old, &new);
	HASHDestroy(new);
	return old;
}

double LoadFactor(hash_table_t *table)
{
	if (0.75 < (HASHSize(table)/table->number_of_buckets))
	{
		return RESIZEUP;
	}
	else if (0.6 > (HASHSize(table)/table->number_of_buckets))
	{
		return RESIZEDOWN;
	}
	return 1;
}
/* Status : Approved
 * Reviewer : Michael E
 * Description : removes an element from table then returns it and by doing so
 * 					causes it to be first in line.
 */
static void Chaching(hash_table_t *table, void *data)
{
	HASHRemove(table, data);
	HASHInsert(table, data);
	return;
}
/* Status : Approved
 * Reviewer : Michael E
 * Description : resize rehash to optimize load factor by user request or when optimization requires.
 * Arguments : pointer to table
 * Return : pointer to resized rehashed table
 */
hash_table_t *HASHReFactor(hash_table_t *table, resize updown)
{
	hash_table_t *new = NULL;
	if (direction[updown] == LoadFactor(table))
	{
		new = ResizenRehash(table, direction[updown]);
	}
	return new;
}



/* Status : Approved
 * Reviewer : Michael E
 * Description : Calculate standart deviation. 
 * Arguments : pointer to table.	
 * Return : SD
 */
double HashSD(const hash_table_t *table)
{
	double sum_values = 0, mean = 0;
	double variance = 0;
	size_t i = 0;
	for (i = 0; i < table->number_of_buckets; ++i)
	{
		sum_values += (double)SListSize(table->hash_table[i]);
	}
	mean = sum_values / (double)table->number_of_buckets;
	sum_values = 0;
	for (i = 0; i < table->number_of_buckets; ++i)
	{
		sum_values = ((double)SListSize(table->hash_table[i]) - mean);
		variance += pow(sum_values, 2);
	}
	variance = sqrt(variance / table->number_of_buckets);
	return variance;
}
double HASHLoad(const hash_table_t *table)
{
	double load = (double)HASHSize(table)/(double)table->number_of_buckets;
	return load;
}