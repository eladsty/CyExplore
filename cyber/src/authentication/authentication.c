

#include <stdlib.h>/* free */
#include <stdio.h>/* FILE */
#include <string.h> /* strcat */
#include <crypt.h> /* crypt_salt and crypt */
 
#include "authentication.h"

#define USERNAME_LEN 32
#define PASS_LENGTH 32
#define LINE_LENGTH 100

static status AuthInput( char *str)
{
    unsigned len = 0;
    if(NULL == str)
    {
        return AUTHFAILED;
    }
    while('\0' != *str )
    {
        if(len > USERNAME_LEN || ':' == *str || '$' == *str || ',' == *str || '\n' == *str ||  ' ' == *str ) 
        {
            return AUTHFAILED;
        }
        ++len;
        ++str;
    }
    return  (len < 1 ? AUTHFAILED : AUTHENTICATED);
}

status AuthAddUser(char *user, char *password)
{       

    FILE *auth_fp;
    size_t user_len = 0;
    char *line = NULL;
    char user_buff[LINE_LENGTH] = {0};      
    char *salt = NULL;
 	char *new_crypt = NULL;

    if( AuthInput(user) || AuthInput(password) )
    {
        return AUTHFAILED;
    }
    
    auth_fp = fopen(PATH ,"a+");
    
    if(NULL == auth_fp)
    {
        return SYSERR;
    }

    strcat(user_buff, user);
    strcat(user_buff, ":");
    user_len = strlen(user_buff);

/* check if user already exist */
    while(getline(&line, &user_len, auth_fp) != -1)
    {
    	if(strncmp(user_buff, line , strlen(user_buff)) == 0)
        {
            free(line);
            fclose(auth_fp);
            return AUTHFAILED;
        }
    }
 
    salt = crypt_gensalt("$5$", 8 ,NULL, 0);
    new_crypt = crypt(password, salt); 
    strcat(user_buff, new_crypt);
    fputs(user_buff, auth_fp);
    fputs("\n", auth_fp);

    free(line);
    line = NULL;
    fclose(auth_fp);


    return AUTHENTICATED;
}

/* 




 */
int AuthDeleteUser(char *user)
{
    FILE *src_fp;
    FILE *temp_fp;
 
    size_t user_len = 0;
    size_t line_len = LINE_LENGTH;
    char user_name[USERNAME_LEN+1] = {0}; 
    char *line = NULL;

    if(AuthInput(user) || NULL == user)
    {
        return AUTHFAILED;
    }

    src_fp = fopen(PATH ,"r");
    temp_fp = fopen("__temp__CR4" ,"a");

    if(NULL == src_fp || NULL == temp_fp)
    {
        return SYSERR;
    }
    strcat(user_name, user);
    strcat(user_name, ":");

    user_len = strlen(user_name);

    while( getline(&line, &line_len, src_fp) != -1 )
    {
    	if( strncmp(user_name, line , user_len) == 0)
        {
            continue;
        }
        fputs(line, temp_fp);
     }

        fclose(src_fp);
        fclose(temp_fp);
        free(line);
        line = NULL;
   if(0 != rename( PATH, "old_src_path" ))
   {
        remove("__temp__CR4");
        fclose(src_fp);
        fclose(temp_fp);
        return SYSERR;
   }

   if(0 != rename( "__temp__CR4", PATH))
   {
        remove("__temp__CR4");
        fclose(src_fp);
        fclose(temp_fp);
        return SYSERR;
   }

   remove("old_src_path");

   return AUTHENTICATED;
}
 


status AuthAuthenticate(char *user, char *password)
{
    FILE *src_fp;
    size_t user_len = 0;
     char user_name[LINE_LENGTH] = {0}; 
    size_t line_len = LINE_LENGTH;
    size_t hash_len = 0;
    char *line = NULL;
    char *hash_cpy = NULL;
    char *hash = NULL;
    if(AuthInput(user) || AuthInput(password)|| NULL == user || NULL == password)
    {
        return AUTHFAILED;
    }

    src_fp = fopen(PATH ,"r");
 
    if(NULL == src_fp)
    {
        return SYSERR;
    }

    strcat(user_name, user);
    strcat(user_name, ":");

    user_len = strlen(user_name);

    while( getline(&line, &line_len, src_fp) != -1 )
    {
    	if( strncmp(user_name, line , user_len) == 0)
        {
            hash_cpy = line + user_len ;
            strcpy(hash_cpy, crypt(password, line + user_len)) ;
            
            if( strcmp(hash_cpy, line + user_len) )
            {
                return AUTHENTICATED;
            }
            return AUTHFAILED;
        }
      }

    return AUTHFAILED;
}   

void Authenticator( char *user, char *password)
{
    if(AUTHENTICATED == AuthAuthenticate(user, password))
    {
        printf("Restricted message, how awsome.\n");
    }

}