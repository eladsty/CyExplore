#include <security/pam_appl.h>/* for pam */
#include <security/pam_misc.h>/* for pam */
#include <stdio.h> /* printf */

#define MAX_USERNAME 32


static struct pam_conv conv = 
{
    misc_conv,
    NULL
};

int main(void)
{
    pam_handle_t *pamh = NULL;
    int retval;
    char user[MAX_USERNAME];
    
    printf("Enter username \n");
    fgets(user, MAX_USERNAME ,stdin);
    user[strlen(user)-1] = '\0';
    retval = pam_start("elad_auth", user, &conv, &pamh);

    if (retval == PAM_SUCCESS)
    {
      retval = pam_authenticate(pamh, 0);    /* is user really user? */
    }    
    /* This is where we have been authorized or not. */
    if (retval == PAM_SUCCESS)
     {
        fprintf(stdout, "Authenticated\n");
     }
     else 
     {
        fprintf(stdout, "Not Authenticated\n");
     }

     if (pam_end(pamh, retval) != PAM_SUCCESS) {     /* close Linux-PAM */
         pamh = NULL;
         fprintf(stderr, "elad_auth: failed to release authenticator\n");
         exit(1);
     }

    return 0;
}
