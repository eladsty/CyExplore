#include "hashtable.h"
#include <string.h> /* strcmp */
#include <stdio.h>  /* printf */
#include <stddef.h> /* size_t */
 
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






int PrintData(void *data, void *param)
{
    UNUSED(param);
    printf(" %s  \n", (char *)data);
    return 0;
}






/*
Start of Shani's test ----------------------
*/


void IsInDict(hash_table_t *table)
{
	char input[64] = {"good luck"};
	while('0' != *input)
	{
		fscanf(stdin, "%s", input);
		if (!HashFind(table, input))
		{
			printf("word is missing\n");
		}
	}
}
/* Status : 
 * Reviewer : 
 * Description : recieve string of a word from stdin, checks if word is in dictionary,
 * 					if encounters an unknown word, prints notification, continues 
 * 					until '0' is pressed by user.	
 * Arguments : void	
 * Return : void
 */
void Spellcheck()
{
	char *buffer = (char *)malloc(1000000);
	char *keep = buffer;
	FILE *dict = fopen("/usr/share/dict/words", "r");
	int indicator = 0;
	hash_table_t *table = HashCreate(10000, (hash_func_t)HashFunc, (cmp_func_t)strcmp);
	while (EOF != fscanf(dict, "%s", buffer))
	{
		indicator += HashInsert(table, buffer);
		buffer += (strlen(buffer) + 1);
	}
	if (!indicator)
	{
		printf("Insert Failed\n");
	}
	IsInDict(table);
    HashForEach(table, PrintData, 0);
	HashDestroy(table);
	fclose(dict);
	free(keep);
	keep = NULL;
	return;
}

/*
 End of Shani's test ----------------------
*/




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
    printf("before removing: %ld \n",HashSize(table) ) ;
    HashRemove(table, &str[2]);
    printf("after removing: %ld \n", HashSize(table)) ; 


    printf("\n\n\n");

    printf("%s\n", (char *)HashFind(table, (void *)str[6]));

    HashForEach(table, PrintData, 0);

    printf("\n\nList Empty? --> %d\n", HashIsEmpty(table));

    HashDestroy(table);
    /* ************************end of adi's tests ****************** */

    /* ***************************spell checker********************************** */

 
    table_dictionary = HashCreate(10, (hash_func_t)HashFunc, (cmp_func_t)strcmp);

/*     HashLoader(table_dictionary);
 */     HashForEach(table_dictionary, PrintData, 0);

    printf("Size Of Hash %ld \n", HashSize(table_dictionary));
 
/*     SpellCheck( table_dictionary );
 */  if(NULL == HashFind(table_dictionary, "AF") )
    {
        printf("Didn't find the requested string.\n");
    }
 

    HashDestroy(table_dictionary);

    /* ***************************end of spell checker********************************** */
	Spellcheck();


    return (0);
}
