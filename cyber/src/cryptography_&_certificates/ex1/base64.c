#include <stdlib.h> /* for malloc */
#include <stdio.h> /* for print */
#include <string.h> /* printf */

static char *encoding_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


char *B64Enc(const char *str)
{
    char *copy_str = (char *)str;
    size_t len = strlen(str);
    int padding = len % 3;
    int i = 0 ;
    char *encoded_str;
    char *cpy;
    int temp = 0;
    encoded_str = malloc(  ( len * 4) / 3 + 3);
    cpy = encoded_str;
    if (NULL == encoded_str)
    {
        return NULL;
    }

    while(len > 2)
    {
        memcpy(&temp, copy_str, 3);
        i = 3;
        temp &= 16777215;
        while(i >= 0)
        {
            *(encoded_str + i) =  encoding_table[ temp & 63];
            temp >>= 6;
            --i;
        }

        copy_str += 3;
        encoded_str += 4;
        temp = 0;
        len -= 3;
    }

    memcpy(&temp, copy_str, 3 - padding);
    i = 3 - padding;
    while(padding)
    {
        *(encoded_str + (3 - padding))  = '=';
        ++encoded_str;
        --padding;
    }

    temp = 0;
   
    while (i)
    {
        *(encoded_str + i) = encoding_table[temp & 63]; 
        temp >>= 6;
        ++encoded_str;
        --i;
    }
כן
    return cpy;
}


/* 
void B64Dec(char *str, char *res)
{
    
} */

/* 
maybe I should zero the memory
 */

int main()
{
    char *str = "0";
    char *str2 = "abcdef";
    char *str3 = "abcdefg";
    char *encoded;

    encoded = B64Enc(str);
    printf("%s \n",encoded);

    encoded = B64Enc(str2);
    printf("%s \n",encoded);

    encoded = B64Enc(str3);
    printf("%s \n", encoded);



    free(encoded);
    return 0;
}