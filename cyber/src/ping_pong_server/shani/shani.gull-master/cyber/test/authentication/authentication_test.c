#include <stdio.h>
#include <string.h>
#include <crypt.h> /* crypt & crypt_salt */
#include <unistd.h> /* sleep */
/* PAM mudule */
#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include <pwd.h>
#define MY_CONFIG "shani-auth"

static struct pam_conv conv = {misc_conv, NULL};

#include "../../include/authentication/authentication.h"

/*int user_interface(int num_msg, const struct pam_message **msg, struct pam_response **resp, void *data_p)
{
	;
}*/


void AddTest(void)
{
	char user_password[8][2][50] = {{"MichaelEvanovIsTheGdbKingAndWeAllSuck", "Michael1234"},
									 {"ShaniGal", "Shani1234"}, 
									 {"&MichaelAfonin", "Michael1234"},
									 {"Lola$Pushtakit", "\\bestdogever!@#$^&*()"},
									 {"LolaInAnyCase", "ImALittlePiggy"},
									 {"KennyMcCormick", "I'mDead"},
									 {"BibiNetanyahu", "EddieSaidNoPolitics"},
									 {"ShakedGull", "QAZwsx123$^&"}};
	int i = 0, j = 0;
	for (i = 0; i < 8; ++i)
	{
		printf("%s\n", (AuthAddUser(user_password[i][j], user_password[i][j + 1])) ? "Add Failed\n" : "Add Successful\n");
	}
}

void DeleteTest(void)
{
	char target[4][50] = {"KennyMcCormick", "Imposter", "ShaniGal:", "MichaelAfonin"};
	int i = 0;
	int indicator = 0;
	for (i = 0; i < 4; ++i)
	{
		indicator = AuthDeleteUser(target[i]);
		if (!indicator)
		{
			printf("Target eliminated successfully\n");
		}
	}
}

void AuthenticateTest(void)
{
	int i = 0, j = 0;
	char cred[3][2][50] = {{"LolaInAnyCase", "ImALittlePiggy"},
							{"BibiNetanyahu", "EddieSaidNoPolitics!"}, 
							{"ShakedGull", "QAZwsx123$^&"}};
	for (i = 0; i < 3; ++i)
	{
		printf("%s\n", (AuthAuthenticate(cred[i][j], cred[i][j + 1]) ? "Imposter" : "Welcome Back brah"));
	}
}

void Authenticator(void)
{
	char username[64], password[128];
	printf("Enter UserName\n");
	scanf("%s", username);
	printf("Enter Password\n");
	scanf("%s", password);

	if (!AuthAddUser(username, password))
	{
		printf("Registered succesfully\n");
		return;
	}
	if (!AuthAuthenticate(username, password))
	{
		printf("Welcome Back brah\n");
		return;
	}
	printf("Imposter\n");
	return;
}

void PAMAuthenticator(void)
{
	char username[64], password[128];
	pam_handle_t *pamh;
	int status;
	printf("Enter UserName\n");
	scanf("%s", username);

	status = pam_start(MY_CONFIG, (const char *)username, &conv, &pamh);
	/*if (PAM_SUCCESS == pam_setcred(pamh, PAM_ESTABLISH_CRED))
	{
		printf("Registered succesfully\n");
		pam_end(pamh, 0);
		return;
	}
	else if (PAM_SUCCESS != pam_setcred(pamh, PAM_ESTABLISH_CRED))
	{
		printf("Register Failed\n");
		pam_end(pamh, 1);
		return;
	}*/
	status = pam_authenticate(pamh, 0);
	if (PAM_SUCCESS == status)
	{
		printf("Welcome Back brah\n");
		return;
	}
	else if (PAM_SUCCESS != status)
	{
		printf("Imposter\n");
	}
	return;
}
int main(void)
{
	char username[64], password[128];
	pam_handle_t *pamh;
	int status;
	printf("Enter UserName\n");
	scanf("%s", username);

	status = pam_start(MY_CONFIG, (char *)username, &conv, &pamh);
	
	status = pam_authenticate(pamh, 0);
	if (PAM_SUCCESS == status)
	{
		printf("Welcome Back brah\n");
	}
	else if (PAM_SUCCESS != status)
	{
		printf("Imposter\n");
		
	}
	printf("%d\n", pam_end(pamh, status));
	return (0);
}

