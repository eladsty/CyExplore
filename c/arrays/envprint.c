 #include<ctype.h>
 #include<stdio.h>
 #include<stdlib.h>
 #include<string.h>

char ToLower(char c)
{
	if ((c >= 'A') && (c <= 'Z'))
	{
		return (c+32);
	} 
	else
	{
		return c;
	}
} 
 
 
int main(int argc, char *argv[], char *envp[])
{
 	int i = 0;
 	int j = 0;
	char *cpy = 0; 
	
 	while(envp[i])
	{
		j+= strlen(envp[i]);
		++i;

	}
	cpy = malloc(j);
 	*cpy = 
    return 0;
}


/*









printf("%c\n", *(*envp));	
realloc(myBuffer,strlen(*envp));
 		while(*)
		printf("%d\n", strlen(*envp));
	 check each string 
		
		



	char *myBuffer[];
	int i = 0;
	
	
  while(NULL != envp[i])
  {
    char *thisEnv = *env;
    printf("%s\n", thisEnv);    
  }
  	








  char myBuffer[300][300];
	int i = 0;
	int j = 0;
  	
while ('\0' != envp[i][j])
		{
			myBuffer[i][j] = ToLower(envp[i][j]);
			++j;
		}
		
		printf("%s\n", myBuffer[i]);
		j = 0;
    	++i;


*/
