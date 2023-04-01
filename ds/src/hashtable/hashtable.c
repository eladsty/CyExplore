#include <stdlib.h>/* malloc */
#include <assert.h>/* assert */
#include <stdio.h> /* printf */
#include <string.h>/* strcmp */

#include "hashtable.h"
#include "slist.h"
#define LONGESTWORDSIZE 30

struct hash_table
{
    size_t index_capacity;
    hash_func_t hash_func;
    cmp_func_t hashcmp;
    slist_t **bucket_list;
};

size_t HashFunc(char *str)
{
    size_t i = 0;
    size_t size = 0;
    const int p = 53;                  /* closest prime to */
    const size_t m = (pow(10, 9) + 9); /* very big prime */
    long hash_value = 0;
    long power = 1;
    size = strlen(str);
    for (i = 0; i < (size); ++i)
    {
        hash_value = (hash_value + (str[i] - 'a' + 1) * power) % m;
        power = (power * p) % m;
    }
    return hash_value;
}



 

/* ******************LISTLISTLIST**************************LISTLISTLIST***************LISTLISTLIST******************************** */

struct slist
{
    node_t *tail;
    node_t *head;
};

struct node
{
    void *data;
    node_t *next;
};

slist_iter_t SListInsertBefore(slist_iter_t to_insert, const void *data)
{
    slist_iter_t new_node = malloc(sizeof(struct node));
    assert(NULL != to_insert && NULL != new_node);
    new_node->data = to_insert->data;
    new_node->next = to_insert->next;
    if (NULL == to_insert->next)
    {
        ((slist_t *)(to_insert->data))->tail = new_node;
    }

    to_insert->data = (void *)data;
    to_insert->next = new_node;

    return to_insert;
}

size_t SListSize(const slist_t *list)
{
    size_t cnt = 0;
    slist_iter_t iter = SListStart(list);

    while (iter->next != NULL)
    {
        ++cnt;
        iter = SListNext(iter);
    }
    return cnt;
}

slist_iter_t SListFind(slist_const_iter_t from, slist_const_iter_t to, is_match_t CompareFunc, void *param)
{
    while (NULL != from->next && (size_t)from != (size_t)to && CompareFunc(from->data, param))
    {
        from = SListNext(from);
    }
    return CompareFunc(from->data, param) ? NULL : (slist_iter_t)from;
}

slist_iter_t SListDelete(slist_iter_t to_remove)
{
    slist_iter_t temp = NULL;

    if (NULL == to_remove->next)
    {
        return ((slist_t *)to_remove->data)->tail;
    }

    temp = to_remove->next;
    to_remove->data = (to_remove->next)->data;
    to_remove->next = (to_remove->next)->next;
    free(temp);
    temp = NULL;

    return to_remove;
}

void SListDestroy(slist_t *list)
{
    assert(list);
    while (NULL != list->head->next)
    {
        SListDelete(list->head);
    }

    free(list->head);
    list->head = NULL;
    free(list);
    list = NULL;
}

void *SListGetData(slist_const_iter_t element)
{
    return (element->data);
}

void SListSetData(slist_iter_t elem, const void *data)
{
    elem->data = (void *)data;
}
slist_iter_t SListNext(slist_const_iter_t element)
{
    if (NULL == element->next)
    {
        return ((slist_t *)(element->data))->tail;
    }
    return (slist_iter_t)element->next;
}

slist_iter_t SListStart(const slist_t *list)
{
    return list->head;
}

slist_iter_t SListEnd(const slist_t *list)
{
    return list->tail;
}

int SListForEach(slist_iter_t from, slist_const_iter_t to, action_t ActionFunc, void *param)
{
    slist_iter_t iter = SListNext(from);
    int error = 0;
    while (iter != to && (0 == error))
    {
        error = ActionFunc((SListGetData(iter)), param);
        iter = SListNext(iter);
    }

    return error;
}

slist_t *SListCreate(void)
{
    struct slist *new_list = malloc(sizeof(struct slist));
    struct node *dummy_node = malloc(sizeof(struct node));

    if (NULL == new_list && NULL == dummy_node)
    {
        return NULL;
    }

    dummy_node->data = (slist_t *)new_list;
    dummy_node->next = NULL;

    new_list->head = dummy_node;
    new_list->tail = dummy_node;

    return new_list;
}

/* struct slist
{
    node_t *tail;
    node_t *head;
};
 */

/* ******************LISTLISTLIST**************************LISTLISTLIST***************LISTLISTLIST******************************** */

hash_table_t *HashCreate(const size_t index_amount, const hash_func_t HashFunc, const cmp_func_t hashcmp)
{
    size_t i = 0, j = 0;
    hash_table_t *table = (hash_table_t *)malloc(sizeof(hash_table_t) + index_amount * sizeof(slist_t *));
    if (NULL == table)
    {
        return NULL;
    }
    table->hash_func = HashFunc;
    table->hashcmp = hashcmp;
    table->index_capacity = index_amount;
    table->bucket_list = (slist_t **)((char *)table + sizeof(hash_table_t));

    for (i = 0; i < index_amount; ++i)
    {
        table->bucket_list[i] = SListCreate();
        if (NULL == (table->bucket_list[i]))
        {
            j = 0;
            while (j < i)
            {
                SListDestroy(table->bucket_list[j]);
                ++j;
            }
            free(table);
            return NULL;
        }
    }

    return table;
}

int HashForEach(hash_table_t *table, int (*ActionFunc)(void *list, void *param2), void *param)
{
    size_t i = 0;

    for (i = 0; i < (table->index_capacity); ++i)
    {
        SListForEach(SListStart(table->bucket_list[i]), SListEnd(table->bucket_list[i]), ActionFunc, param);
    }

    return 0;
}

void HashDestroy(hash_table_t *table)
{
    size_t i = 0;

    for (i = 0; i < (table->index_capacity); ++i)
    {
        SListDestroy(table->bucket_list[i]);
    }

    free(table);
    table = NULL;
}

void *HashFind(const hash_table_t *table, const void *data)
{
    size_t hash = table->hash_func(data);
    size_t i = hash % (table->index_capacity); 
    slist_t *curr_list = table->bucket_list[i];

    slist_iter_t node_p = SListFind(SListStart(curr_list), SListEnd(curr_list), table->hashcmp, (void *)data);
    if (NULL == node_p)
    {
        return NULL;
    }
    return node_p->data;
}

int HashInsert(hash_table_t *table, const void *data)
{
    size_t hash = table->hash_func(data);
    size_t i = hash % table->index_capacity;
    slist_t *curr_list = table->bucket_list[i];
    if (NULL != SListInsertBefore(curr_list->head, data))
    {
        return 1;
    }

    return 0;
}

int HashRemove(hash_table_t *table, const void *data)
{
    size_t hash = table->hash_func(data);
    size_t i = hash % table->index_capacity;
    slist_t *curr_list = table->bucket_list[i];
    slist_iter_t iter_to_remove = SListFind(curr_list->head, curr_list->tail, table->hashcmp, (void *)data);

    /*deletes the node pointed by next in the give iterator*/
    SListDelete(iter_to_remove);
    return 0;
}

size_t HashSize(const hash_table_t *table)
{
    size_t count = 0;
    size_t i = 0;

    for (i = 0; i < table->index_capacity; ++i)
    {
        count += SListSize(table->bucket_list[i]);
    }
    return count;
}

int HashIsEmpty(const hash_table_t *table)
{
    size_t i = 0;
    for (i = 0; i < table->index_capacity; ++i)
    {
        if (NULL != (table->bucket_list[i])->head->next)
        {
            return 0;
        }
        return 1;
    }
}

void HashLoader(hash_table_t *table)
{
    FILE *dict = fopen("/usr/share/dict/words", "r");
    int j = 0;
    int num_of_inserts = 0;
    char word_in_dic[30];
    if (NULL == dict)
    {
        return;
    }

    /* NULL != fgets(word_in_dic, 30, dict)  insert it inside the while */
    while (j < 20)
    {
        ++j;
        fgets(word_in_dic, 30, dict);
        num_of_inserts += HashInsert(table, word_in_dic);
        printf("%s\n", word_in_dic);
        printf("insert: %d\n", num_of_inserts);
    }
    fclose(dict);
}
/* void SpellCheck(hash_table_t *table)
{
   char word[30] = {0};
   slist_t *curr_list = NULL;
   while (27 != getc(stdin))
   {
       printf("type word to look for in dictionary or press Esc to exit.\n"  );
       fgets(word, LONGESTWORDSIZE, stdin);
       curr_list = table->bucket_list[ (HashFunc(word) % table->index_capacity) ];

       if(NULL != SListFind(SListStart(curr_list), SListEnd(curr_list),(is_match_t)strcmp, word))
       {
           printf("Found the word!");
           return;
       }

       printf("Word is missing or misspelled.\n");

   }

} */

/* void SpellCheck(hash_table_t *table)
{
    slist_t *curr_list = NULL;

    char *line = NULL;
    size_t len = 0;
 
    while (1)
    {
        printf("type word to look for in dictionary or press Esc to exit.\n");
        puts("enter a line");
       getline(&line, &len, stdin);
        curr_list = table->bucket_list[(HashFunc(line) % table->index_capacity)];
         if(NULL != HashFind(table, line))
        {
            printf("Found the word!");
            break;
        }  
 
    }

    free(line);
}
 */