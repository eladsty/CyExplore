
#include <string.h>

#include "/home/elad/elad.shem-tov/ds/include/stack.h"

static int IsOpenPar(char *c);
static int IsClosePar(char *c);

/* enum ISPAR {NOT, ROUND, SQUAR, CURLY};
 */
static int IsOpenPar(char *c)
{
  if('(' == *c || '[' == *c || '{' == *c )
  {
    return 1;
  }
  return 0;
}

static int IsClosePar(char *c)
{
  if(')' == *c)  
  {
    return 1;
  }
  if(']' == *c)  
  {
    return 2;
  }
  if('}' == *c)  
  {
    return 3;
  }
  
  return 0;
}

/* 
if the parentheses are opened and closed properly, print success, else print error
 */
void CheckParentheses( char *str )
{
  stack_t *stack = StackCreate(1000,1);
  size_t len = strlen(str), i = 0;
  int close_par = 0;
  for(i = 0; i < len; ++i)
  {
    if(IsOpenPar(&str[i]))
    {
      StackPush(stack, &str[i]);
      continue;
    }
    
    if(str[i] == ')' )
    {
      if( '(' != *(char *)StackPeek(stack) )
      {
        printf("Failed.\n");
        return;
      }
      StackPop(stack);
      continue;
    }
     if(str[i] == ']' )
    {
      if( '[' != *(char *)StackPeek(stack) )
      {
        printf("Failed.\n");
        return;

      }
      StackPop(stack);
      continue;
    }
     if(str[i] == '}' )
    {
      if( '{' != *(char *)StackPeek(stack) )
      {
        printf("Failed.\n");
        return;
      }
      StackPop(stack);
      continue;
    }
  }

  if(StackIsEmpty(stack))
  {
    printf("Success.\n");
    return;
  }
  printf("Failed.");

}
 
int main()
{
  char *test[] = { "", "f2182f", "{}([dqd12]1r1r1r)f9(ff8w)", "fqnhw0{,2,2,2}[2()]"    ,   "ooooo}[o()", "{[oooo[oooo()]ooo}", "[]{}(( )))", "}}))]]"};
  unsigned i = 0;
  for(i = 0; i < 8; ++i)
  {
    CheckParentheses(test[i]);
  }

  return 0;
}
