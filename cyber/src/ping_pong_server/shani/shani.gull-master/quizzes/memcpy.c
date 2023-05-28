#define WORDSIZE sizeof(size_t)
#include <stdio.h> /* size_t */
void *Memcpy(void *dest, void *src, size_t n);
int main()
{
	char str[] = {"shani"}, copy[6] = {'\0'};
	
	Memcpy(copy, str, 6);
	return 0;
}

void *Memcpy(void *dest, void *src, size_t n)
{
	char *dest_tmp = dest, *src_tmp = src;
	char word[WORDSIZE] = {0};
	int i = 0;
	
	while (n)
	{
		if (WORDSIZE > n || !((size_t)dest_tmp % WORDSIZE))
		{
			*dest_tmp = *src_tmp;
			++dest_tmp, ++src_tmp, --n;
		}
		else
		{
			for (i = 0; WORDSIZE > (size_t)i; ++i, ++src_tmp)
			{
				word[i] = *src_tmp;
				--n;
			}
			*(void **)dest_tmp = *(void **)word;
			dest_tmp += WORDSIZE;
		}
	}
	return dest;
}
