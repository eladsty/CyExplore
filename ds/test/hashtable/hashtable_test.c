#include "hashtable.h"
#include <string.h> /* strcmp */
#include <stdio.h>  /* printf */
#include <stddef.h> /* size_t */
#include <math.h>   /* pow */
#include <stdlib.h> /* free and malloc*/

#define HASHSIZE 3
#define UNUSED(var) (void)(var)
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

int PrintData(void *data, void *param)
{
    UNUSED(param);
    printf(" %s  \n", (char *)data);
    return 0;
}

int main(void)
{

    hash_table_t *table_dictionary;
/* ************************adi's tests ****************** */
    char str[][150] = {"adi amilany", "yarden wuntch", "yuval mevulbal",
                       "I love varible size allocation lists :)", "adi",
                       "I should go have fun!!", "One day we will make plenty of money :)))",
                       "Approved?  you Wish!", "If you copy my tests and failed them, you only got yourself to blame - NOT MY TESTS!!"};
    size_t i = 0, size = sizeof(str) / sizeof(str[0]);
    hash_table_t *table = HashCreate(HASHSIZE, (hash_func_t)HashFunc, (cmp_func_t)&strcmp);
    printf("\n\nList Empty? --> %d\n", HashIsEmpty(table));

    printf("\n\n\n");

    for (i = 0; i < size; ++i)
    {
        HashInsert(table, (void *)str[i]);
        printf("Size Of Hash %ld \n", HashSize(table));
    }
    printf("\n\n\n");

    printf("%s\n", (char *)HashFind(table, (void *)str[6]));

    HashForEach(table, PrintData, 0);

    printf("\n\nList Empty? --> %d\n", HashIsEmpty(table));

    HashDestroy(table);
    /* ************************end of adi's tests ****************** */

    /* ***************************spell checker********************************** */

   

    table_dictionary = HashCreate(25000, (hash_func_t)HashFunc, (cmp_func_t)strcmp);

    HashLoader(table_dictionary);
    printf("Size Of Hash %ld \n", HashSize(table_dictionary));
 
/*     SpellCheck( table_dictionary );
 */    if(NULL != HashFind(table_dictionary, "AA"))
        {
            printf("Found the word!");
        } 

    HashDestroy(table_dictionary);

    /* ***************************end of spell checker********************************** */

    return (0);
}
