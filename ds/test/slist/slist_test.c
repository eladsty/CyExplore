#include <stdio.h>
#include <string.h>
#include "slist.h"


int CompareStrings(const void* data, void* param)
{
    char *str = (char *) data;
    char *target = (char *) param;
    return strcmp(str, target);
}

int CatString(void *data ,void *param)
{
	char *dest = (char *) data;
    char *src = (char *) param;
    return ((NULL != strcat(dest, src)) ? 0 : 1);
   	
}


int main()
{
	slist_t *list = SListCreate();
	
	char s[][40] = {"1111111", "22222", "33333333",
				 "", "long long ling long string", 
				"just one string"};
	char *find = "22222";
	char *action = "success";
	slist_iter_t func = NULL;
	int arr[500][1];
	size_t j = 0;
	
	slist_iter_t i = SListStart(list);
	for (j = 0; j < 100; j++)
	{
		arr[j][0] = j * 2;
		i = SListInsertBefore(i, arr[j]); 
	}
	
	i = SListStart(list);
	for (j = 0; j < 100; j++)
	{
		printf("%d\n", *(int *)SListGetData(i));
	}
	
	printf("\nsize of elements in list: %ld\n\n", SListSize(list));	
	
	printf("Deleting using functions in loop\n\n");
	i = SListStart(list);
	while ( i != SListEnd(list))
	{
		i = SListDelete(i);
		printf("\nsize of elements in list: %ld\n", SListSize(list));	
	}
	
	printf("\n*********************Create, insert, Size, Delete******************* \n\n");
	
	i = SListStart(list);
	for (j = 0; j < 7; ++j)
	{
		i = SListInsertBefore(i, s[j]); 
		printf("%s\n", (char *)SListGetData(i));
	}
	
	SListSetData(i, s[j]);
	printf("\nUse SetData in last node\n%s\n", (char *)SListGetData(i));
	
	printf("\nsize of elements in list: %ld\n\n", SListSize(list));	
	
	printf("Deleting using functions in loop\n\n");
	i = SListStart(list);
	while ( i != SListEnd(list))
	{
		i = SListDelete(i);
	}
	
	printf("\nsize of elements in list after delete loop: %ld\n\n", SListSize(list));	
	
	i = SListStart(list);
	for (j = 0; j < 7; ++j)
	{
		i = SListInsertBefore(i, s[j]); 
	}
	
	printf("***************************Checking SListFind:**************************\n\n");
	func = SListFind(SListStart(list), SListEnd(list), CompareStrings, find);
	if (func != SListEnd(list))
	{
		printf("Found! --> %s\n", (char *)SListGetData(func));
	}
	else
	{
		printf("SListFind - failed\n");
	}	
	printf("\n\n");
	printf("************************Checking SListForEach:****************************\n");
	SListForEach(SListStart(list), SListEnd(list), CatString, action);
	i = SListStart(list);
	for (j = 0; j < 7; ++j)
	{
		printf("%s\n", (char *)SListGetData(i));
		i = SListNext(i);
		
	}
	printf("\n\n");
	SListDestroy(list);
	return 0;
}

