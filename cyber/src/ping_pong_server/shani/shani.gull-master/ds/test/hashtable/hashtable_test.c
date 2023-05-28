#include "../../include/hashtable/hashtable.h"
#include <string.h> /* strcmp */
#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */
#include <math.h> /* pow */
#include <stdlib.h> /*malloc */

/* computes hash value by picking a very big prime number, 
	and a prime number closest to the sum of possible letters 
	in a string comprised of lower and upper case letters.
	setting the value of a to 1, b to 2, and so forth.
	itterate over string, up until null terminator (not including),
	adding the sum of all characters values (a = 1, b = 2, ..),
	times the power variable mod the big primer.
	then updating the power factor by the prime closest mod big prime.
*/
size_t HashFunc(char *str)
{
	size_t i = 0;
	size_t size = 0;
	const int p = 53; /* closest prime to */
	const size_t m = (pow(10, 9) + 9); /* very big prime */
	long hash_value = 0;
	long power = 1;
	size = strlen(str);
	for (i = 0; i < size; ++i)
	{
		hash_value = (hash_value + (str[i] - 'a' + 1) * power) % m;
		power = (power * p) % m;
	}
	return hash_value;
}
int PrintHashTable(void *data, void *param)
{
	printf("%s\n", (char *)data);
	printf("of index: %ld\n", (HashFunc(data) % 3));
	(void)param;
	return 0;
}
hash_table_t *CreateTest(void)
{
	hash_table_t *hash_table = HASHCreate(3, (hashfunc_t)HashFunc, (compfunc_t)strcmp);
	printf(" - Create Hash Table -\n");
	return hash_table;
}
int InsertTest(hash_table_t *table)
{
	int i = 0;
	int indicator = 0;
	char *data_test[] = {"Shani", "Nave", "Adi", "Ran", "Elad", "Shlomi", "shani", "shaked", "tavor", "liat", "mor", "shahar"};
	for (i = 0; i < 12; ++i)
	{
		indicator += HASHInsert(table, data_test[i]);
	}
	printf(" - Insert to Hash Table -\n");
	return indicator;

}
int PrintTest(hash_table_t *table)
{
	printf(" - My Awesome Hash Table -\n");
	HASHForEach(table, PrintHashTable, NULL);
	return 0;
}
void FindTest(hash_table_t *table)
{
	char *word = (char *)HASHFind(table, "Shlomi");
	char *null = HASHFind(table, "Tzion");
	printf("Shlomi is in list: %s, Tzion is not: %s\n", word, null);
}

void SizeTest(hash_table_t *table)
{
	size_t size = HASHSize(table);
	printf("hash table holds: %ld elements.\n", size);
	printf("hash table %s empty\n", (HASHIsEmpty(table) ? "is not" : "is"));
	return;
}
void RemoveTest(hash_table_t *table)
{
	char *data = {"Shani"};
	HASHRemove(table, data);
}



void IsInDict(hash_table_t *table)
{
	char input[64] = {"good luck"};
	while('0' != *input)
	{
		fscanf(stdin, "%s", input);
		if ('0' == *input)
		{
			break;
		}
		if (!HASHFind(table, input))
		{
			printf("Your spelling sucks! XD\n");
		}
	}
}
/* Status : Aproved
 * Reviewer : Michael A
 * Description : recieve string of a word from stdin, checks if word is in dictionary,
 * 					if encounters an unknown word, prints notification, continues 
 * 					until '0' is pressed by user.	
 * Arguments : void	
 * Return : void
 */
void SpellCheck()
{
	char *buffer = (char *)malloc(1000000);
	char *keep = buffer;
	FILE *dict = fopen("/usr/share/dict/words", "r");
	int indicator = 0;
	hash_table_t *table = HASHCreate(1600, (hashfunc_t)HashFunc, (compfunc_t)strcmp);
	while (EOF != fscanf(dict, "%s", buffer))
	{
		indicator += HASHInsert(table, buffer);
		buffer += (strlen(buffer) + 1);
	}
	if (indicator)
	{
		printf("Insert Failed\n");
	}
	/* test for SD */
	printf("before refactor SD = %f\n", HashSD(table));
	printf("before refactor LOAD = %f\n", HASHLoad(table));
	IsInDict(table);
	/* test for chaching */
	HASHFind(table, "cargo");
	/* test for refactoring */
	table = HASHReFactor(table, UP);
	printf("after refactor SD = %f\n", HashSD(table));
	printf("before refactor LOAD = %f\n", HASHLoad(table));
	HASHDestroy(table);
	fclose(dict);
	free(keep);
	keep = NULL;
	return;
}


int main(void)
{
	hash_table_t *table = NULL;
	table = CreateTest();
	InsertTest(table);
	PrintTest(table);
	SizeTest(table);
	RemoveTest(table);
	SizeTest(table);
	FindTest(table);
	HASHDestroy(table);
	SpellCheck();
	return (0);
}


