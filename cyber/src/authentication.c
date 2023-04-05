#define  _POSIX_C_SOURCE 200809L


#include <stdlib.h>/* free */
#include <stdio.h>/* FILE */
#include <string.h> /* strcat */
#include "authentication.h"

 
static status AuthInput( char *str)
{
    unsigned len = 0;
    if(NULL == str)
    {
        return AUTHFAILED;
    }
    while('\0' != *str )
    {
        if(len > 100 || ':' == *str || '$' == *str || ',' == *str || '\n' == *str) 
        {
            return AUTHFAILED;
        }
        ++len;
        ++str;
    }
    return AUTHENTICATED;
}

status AuthAddUser(char *user, char *password)
{
	 
    FILE *auth_fp;
    size_t len = 40;
    char *line = NULL;
    char user_buff[100] = {0};
    char *salt = NULL;
 	char *new_crypt = NULL;


    if( AuthInput(user) || AuthInput(password) )
    {
        return AUTHFAILED;
    }
    
    auth_fp = fopen(PATH ,"r");
    
    if(NULL == auth_fp)
    {
        return SYSERR;
    }

    strcat(user_buff, user);
    strcat(user_buff, ":");

/* check if user already exist */
    while(getline(&line, &len, auth_fp) != -1)
    {
    	if(strncmp(user_buff, line , strlen(user_buff)) == 0)
        {
            free(line);
            fclose(auth_fp);
            return AUTHFAILED;
        }
    }
    /* username: salt (concatted with) password */

    salt = crypt_gensalt("$5$", 8 ,NULL, 0);
    new_crypt = crypt(password, salt); 
    strcat(user_buff, new_crypt);




/* 
        enduser = strchr(line, (int)':');
    	
    	if (0 == strncmp(user,line,enduser-line) && strlen(user)==(size_t)(enduser-line))
    	{
    		fclose(file);
    		return AUTH_FAILURE;
    	}
    while( EOF != fscanf(auth_fp, "\n") )
    {
        if(0 == strncmp(user_buff, line_buffer , user_len)  );
    }


    salt =  crypt_gensalt();

    fscanf(auth_fp, const char *format, ...);
 */
    free(line);
    fclose(auth_fp);


 
}