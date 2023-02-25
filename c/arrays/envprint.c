 #include<ctype.h>
 #include<stdio.h>
 #include<stdlib.h>
 #include<string.h>
 #include <assert.h>
 
/* Status: READY;
 * Reviewer: Nimrod
 * Description: Function that print enviroment variables.
 * Return :  return pointer.
 */




size_t StrLen(char *str)
{
	char *p_end = str;

	assert(NULL != str);
	
	while('\0' != *p_end)
	{
		++p_end;
	}
 
	return (p_end - str);
}

char ToLower(char c)
{
	return ((c >= 'A' && c <= 'Z')? c+32 : c);
} 

char *CpyToLower(char *cpy, char *str )
{	
	char *p_strt = cpy;
	assert(NULL != str && NULL != cpy);
	
	while('\0' != *str)
	{
		*p_strt = ToLower(*str);
		++p_strt;
		++str;
	}
	
	return cpy;
} 
 
char **PrintEnvpLow(char *envp[])
{
  size_t i = 0, j = 0;
  char **myBuffer;  
  
  for(;envp[i] != NULL; ++i);
  
  myBuffer = malloc(i*sizeof(char*)+1);

  i = 0;
  
  while(envp[i])
	{	
 	    myBuffer[i] = malloc(strlen(envp[i]) + 1);
 	    
		while ('\0' != envp[i][j])
		{
			myBuffer[i][j] = ToLower(envp[i][j]);
			++j;	
		}
		printf("%s\n",myBuffer[i]);
		j=0;
		++i;
	}
 
 	return myBuffer;
}


void freeBuffer(char** buffer)
{
 int i = 0;
 
  while(buffer[i])
	{	
	
 	  free(buffer[i]);
 	++i;    
	}
	 free(buffer);
}


int main(int argc, char *argv[], char *envp[])
{
  
 	freeBuffer(PrintEnvpLow(envp));
    return 0;
}

 
