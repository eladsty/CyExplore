#include <string.h>

void Swap(char *a, char *b)
{
  if(*a != *b)
  {
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
  }
}


void StringPermutation(char *str, int l, int r)
{
 
  int i;
  if (l == r)
  {
      printf("%s\n", str);
  }
  else 
  {
      for (i = l; i <= r; i++) 
      {
          Swap((str + l), (str + i));
          StringPermutation(str, l + 1, r);
          Swap((str + l), (str + i));  
      }
  }

}

int main()
{
  char str[] = "abc";
  int n = strlen(str);
  StringPermutation(str, 0, n-1);
  return 0;
}
