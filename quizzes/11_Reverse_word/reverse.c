#include <stdio.h>
#include <string.h>


void ReverseString(char *src_str, char *copy_reversed )
{
	
	 
    size_t len, i = 0, index = 0, word_start = 0, word_end = 0;
    len   = strlen(src_str);
    index = 0;

    /* Start checking of words from the end of string*/ 
    word_start = len - 1;
    word_end   = len - 1;

    while(word_start > 0)
    {
        /* If a word is found */ 
        if(' ' == str[word_start])
        {
            // Add the word to the reverse string
            i = word_start + 1;
            while(i <= word_end)
            {
                reverse[index] = src_str[i];

                i++;
                index++;
            }
            reverse[index++] = ' ';

            word_end = word_start - 1;
        }

        --word_start;
    }

    // Finally add the last word
    for(i=0; i<=word_end; i++)
    {
        copy_reversed[index] = str[i];
        index++;
    }

    // Add NULL character at the end of reverse string
    reverse[index] = '\0'; 
    
    
    return copy_reversed;
}
 
int main()
{
    char string[] = " ";
	printf("%s\n",string);
    ReverseString(string);
	printf("after reverseing: %s\n",string);
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
