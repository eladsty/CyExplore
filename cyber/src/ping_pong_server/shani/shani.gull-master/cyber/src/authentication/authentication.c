#include <stdio.h> /* FILE */
#include <string.h> /* strcpy */
#include <crypt.h> /* crypt & crypt_salt */
#include <stdlib.h> /* malloc */
#include "../../include/authentication/authentication.h"

#define TEMP_PATH (PATH "temp")
#define HASH_ALGO "$y$"
#define HASHED_SIZE_IN_BYTES 74
#define USER_CHAR_LIMIT 35
#define SALT 22
#define ERROR -1
#define NOT_FOUNT -2


/* encryptes using yescrypt */
char *encrypt(char *password)
{
	return crypt(password, crypt_gensalt(HASH_ALGO, 0, NULL, 0));
}
/* in order to erase garbage values containing a user data from the stack or heap */
void CoverTracks(char *used)
{
	while ('\0' != *used)
	{
		*used = '\0';
		++used;
	}
	return;
}

/* returns the index of the line where a username was found, -2 if not found */
long IsUserExist(char *username)
{
	/* strstr each line until EOF */
	FILE *shadow = fopen(PATH, "r");
	char line[USER_CHAR_LIMIT + HASHED_SIZE_IN_BYTES + 10];
	size_t i = 0;
	
	while (EOF != fscanf(shadow, "%s\n", line))
	{
		if (!strncmp(line, username, strlen(username)))
		{
			fclose(shadow);
			CoverTracks(line);
			return i;
		}
		++i;
	}
	if (ferror(shadow))
	{
		fclose(shadow);
		CoverTracks(line);
		return ERROR;
	}
	fclose(shadow);
	CoverTracks(line);
	return NOT_FOUNT;
}
/* checks for username length and forbiden characters */
size_t IsUserValid(char *username)
{
	size_t i = 0;
	char forbiden[] = {'\\','!', ':', ';', '*', '$', '%'};
	if (USER_CHAR_LIMIT < strlen(username))
	{
		return 0;
	}
	for (i = 0; i < sizeof(forbiden) ; ++i)
	{
		if (NULL != strchr(username, forbiden[i]))
		{
			return 0;
		}
	}
	return (i = 5) ? 1 : 0;
}

/* Status : approved
 * Reviewer : Michael E
 * Description : opens/reads into shadow file, checks for similar user names, 
 * 				and for validity of user name. if all good, adds to shadow file 
 * 				as 'username:hashedpassword'.	
 * Arguments : username, password	
 * Return : success or error
 */
status AuthAddUser(char *user, char *password)
{
	FILE *shadow;
	char *user_temp = (char *)malloc((USER_CHAR_LIMIT + HASHED_SIZE_IN_BYTES + 1) * sizeof(char)); 
	char *hashed_pass = NULL;
	if (NULL == user_temp)
	{
		return SYSTEM_ERROR;
	}
	strcpy(user_temp, user);
	strcat(user_temp, ":");
	if (NOT_FOUNT != IsUserExist(user_temp))
	{
		free(user_temp);
		user_temp = NULL;
		return SYSTEM_ERROR;
	}
	shadow = fopen(PATH, "a+");

	if (NULL == shadow)
	{
		free(user_temp);
		user_temp = NULL;
		return SYSTEM_ERROR;
	}
	/* check for username validity */
	if (!IsUserValid(user))
	{
		fclose(shadow);
		free(user_temp);
		user_temp = NULL;
		return SYSTEM_ERROR;
	}
	/* check if username already exists */

	hashed_pass = encrypt(password);
	user_temp = strcat(user_temp, hashed_pass);
	CoverTracks(hashed_pass);

	if (0 > fprintf(shadow, "%s\n", user_temp))
	{
		fclose(shadow);
		free(user_temp);
		user_temp = NULL;
		return SYSTEM_ERROR;
	}

	free(user_temp);
	user_temp = NULL;
	fclose(shadow);
	return 0;
}


char *Standardize(char *user)
{
	char *user_temp = (char *)malloc((USER_CHAR_LIMIT + HASHED_SIZE_IN_BYTES + 1) * sizeof(char));
	if (NULL == user_temp)
	{
		return NULL;
	}
	strcpy(user_temp, user);
	strcat(user_temp, ":");
	return user_temp;
}
/* Status : approved
 * Reviewer : Michael E
 * Description : gets a string, validate it's configuration against standard, 
 * 				find it in the database, remove it by coping all other instances 
 * 				to a different file and removing the original file.	
 * Arguments : user name	
 * Return : 0 upon success, nonzero indicating an error
 */
status AuthDeleteUser(char *user)
{
	char *user_temp = Standardize(user);
	char buffer[USER_CHAR_LIMIT + HASHED_SIZE_IN_BYTES + 10];
	long line_i = 0, i = 0;
	FILE *shadow, *temp;
	if (NULL == user_temp)
	{
		free(user_temp);
		user_temp = NULL;
		return SYSTEM_ERROR;
	}
	/* is user name valid */
	if (!IsUserValid(user))
	{
		free(user_temp);
		user_temp = NULL;
		return SYSTEM_ERROR;
	}

	/* find index of line in file where instance is */
	line_i = IsUserExist(user_temp);
	free(user_temp);
	user_temp = NULL;
	if (0 > line_i)
	{
		return SYSTEM_ERROR;
	}

	shadow = fopen(PATH, "r");
	temp = fopen(TEMP_PATH, "a+");
	if (NULL == shadow || NULL == temp)
	{
		remove(TEMP_PATH);
		return SYSTEM_ERROR;
	}

	for (i = 0; EOF != fscanf(shadow, "%s\n", buffer); ++i)
	{
		if (i != line_i)
		{
			if (0 > fprintf(temp, "%s\n", buffer))
			{
				fclose(shadow);
				fclose(temp);
				remove(TEMP_PATH);
				CoverTracks(buffer);
				return SYSTEM_ERROR;
			}
		}
	}
	if (ferror(shadow))
	{
		fclose(shadow);
		fclose(temp);
		remove(TEMP_PATH);
		CoverTracks(buffer);
		return ERROR;
	}
	fclose(shadow);
	fclose(temp);
	remove(PATH);
	rename(TEMP_PATH, PATH);
	CoverTracks(buffer);
	return 0;
}
char *GetSalt(char *user_data)
{
	char *salt_end = strrchr(user_data, '$');
	size_t i = 0;
	while ((user_data + i) != salt_end)
	{
		++i;
	}
	while ('\n' != *(user_data + i))
	{
		*(user_data + i) = '\0';
		++i;
	}
	return user_data;
}
char *GetUserData(size_t line_i, char *username, char **temp)
{
	FILE *shadow = fopen(PATH, "r");
	size_t i = 0;
	char data[USER_CHAR_LIMIT + HASHED_SIZE_IN_BYTES + 10], *salt_end;
	
	while (i != line_i)
	{
		if (EOF == fscanf(shadow, "%s\n", data))
		{
			fclose(shadow);
			free(username);
			username = NULL;
			
			return NULL;
		}
		++i;
	}
	CoverTracks(data);
	fseek(shadow, strlen(username), SEEK_CUR);
	if (EOF == fscanf(shadow, "%s\n", *temp))
	{
		fclose(shadow);
		free(username);
		username = NULL;
		free(*temp);
		*temp = NULL;
		return NULL;
	}


	fclose(shadow);
	free(username);
	username = NULL;
	return *temp;
} 
/* Status : approved
 * Reviewer : Michael E
 * Description : check if a user exists and if the password used is correct for 
 * 				said user	
 * Arguments : username and password.	
 * Return : 0 if authenticated, non-zero for fail
 */
status AuthAuthenticate(char *user, char *password)
{
	long line_i = 0, i = 0;
	char *user_temp = Standardize(user), *salt_end, *data, temp[USER_CHAR_LIMIT + HASHED_SIZE_IN_BYTES + 10];
	if (!IsUserValid(user))
	{
		free(user_temp);
		user_temp = NULL;
		return SYSTEM_ERROR;
	}

	line_i = IsUserExist(user_temp);
	if (0 > line_i)
	{
		free(user_temp);
		user_temp = NULL;
		return SYSTEM_ERROR;
	}
	data = (char*)malloc(USER_CHAR_LIMIT + HASHED_SIZE_IN_BYTES + 10);
	data = GetUserData(line_i, user_temp, &data);
	if (NULL == data)
	{
		free(user_temp);
		user_temp = NULL;
		return SYSTEM_ERROR;
	}
	

	salt_end = strrchr(data, '$');
	i = 0;
	while ((data + i) != salt_end)
	{
		temp[i] = *(data + i);
		++i;
	}
	temp[i] = '\0';
	
	if (strcmp(crypt(password, temp), data))
	{
		free(data);
		data = NULL;
		return SYSTEM_ERROR;
	}
	free(data);
	data = NULL;
	return AUTHENTICATED;
}
