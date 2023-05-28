#define _POSIX_C_SOURCE 200112L

#include <string.h> /* strlen */
#include <unistd.h>	   /* write */
#include <stdio.h>

#include "../../include/prod_cons/prod_cons.h"
#include "../../../ds/include/linked_list/linked_list.h"

#define MAX_LEN 255

void *ActProducePrimes(void *datum)
{
	*(size_t*)datum = rand() % 100 + 1;
	return (size_t *)datum;
}
void *ActPrintParam(void *param)
{
	char temp[MAX_LEN];
	sprintf(temp, "%ld", *(long *)param);
	write(STDOUT_FILENO, temp, strlen(temp));
	return NULL;
}

void *ActPrintSLL(void *param)
{
	write(STDOUT_FILENO, param, 15);
	write(STDOUT_FILENO, "\n", 1);
	return NULL;
}

void Ex1Test()
{
	size_t ncycles = 3;
	size_t produce[15] = {0};
	Ex1SingleProdCons(ncycles, produce, &ActProducePrimes, &ActPrintParam);
}
void Ex2Test()
{
	size_t ncycles = 3;
	size_t consumers = 2, producers = 2;
	char produce[15] = {"first message."};
	Ex2MultiProdCons(consumers, producers, ncycles, (char *)produce, ActPrintSLL);
}
void Ex3Test()
{
	size_t ncycles = 3;
	size_t consumers = 2, producers = 2;
	char produce[15] = {"first message."};
	Ex3MultiProdCons(consumers, producers, ncycles, (char *)produce, ActPrintSLL);
}
void Ex4Test()
{
	size_t ncycles = 3;
	size_t consumers = 2, producers = 2;
	char produce[3][15] = {{"first message."}, {"second message"}, {"third message."}};
	Ex4FSQ(consumers, producers, ncycles, 15, (char **)produce, ActPrintSLL);
}
void Ex5Test()
{
	size_t ncycles = 3;
	size_t consumers = 5, producers = 5;
	char produce[3][15] = {{"first message."}, {"second message"}, {"third message."}};
	Ex5FSQ(consumers, producers, ncycles, 15, (char **)produce, ActPrintSLL);
}
void Ex6Test()
{
	size_t ncycles = 3;
	size_t consumers = 5;
	char produce[3][15] = {{"First message6"}, {"second message"}, {"third message."}};
	Ex6Barrier(consumers , 15 , (char **)produce, ncycles, ActPrintSLL);
}

int main(void)
{
	/*Ex1Test();
	Ex2Test();
	Ex3Test();
	Ex4Test();
	Ex5Test();*/
	Ex6Test();
	return (0);
}
