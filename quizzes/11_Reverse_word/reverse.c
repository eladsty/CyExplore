#include <stdio.h>
#include <string.h>


char *ReverseString(char *src_str, char *copy_reversed )
{
    size_t len, i = 0, index = 0, word_start = 0, word_end = 0;
    len   = strlen(src_str);

    /* Start checking of words from the end of string*/ 
    word_start = len - 1;
    word_end   = len - 1;

    while(word_start > 0)
    {
        /* If a word is found */ 
        if(' ' == src_str[word_start])
        {
 
            i = word_start + 1;
            while(i <= word_end)
            {
                copy_reversed[index] = src_str[i];

                i++;
                index++;
            }
            copy_reversed[index++] = ' ';

            word_end = word_start - 1;
        }

        --word_start;
    }

 
    for(i=0; i<=word_end; i++)
    {
        copy_reversed[index] = src_str[i];
        index++;
    }

 
    copy_reversed[index] = '\0'; 
    
    
    return copy_reversed;
}
 
int main()
{
    char string[] = "hello my name is luka";
    char copy_rev[30];
    
	printf("%s\n",string);
	printf("after reverseing: %s\n", ReverseString(string,copy_rev));
    return 0;
}

/*
	map each word, each word end when encountering a space.
	copy each 50-100 character from the string to avoid overriding existing words in 						the original string.
	now, starting from end of string, find the starting_point of the last word.
	and copy it until encountering " " or ".", 
 "This" "string" "is" "not" "reversed"."
 "is not reversed This string  ."

*/
