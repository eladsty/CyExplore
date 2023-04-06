#include <stdio.h>/* printf */

#include "authentication.h"
#define LEN 11

int Test_AuthAddUser(char *username[LEN], char *password[LEN])
{
    unsigned i = 0;
    for(i = 0; i < LEN; ++i)
    {
       AuthAddUser(username[i], password[i]);
    }
}
 

int main()
{
    char *user_arr[] = {"$asd","$asd","eelad","elad", "shlomi","ran", "shani",":", " " ,"oneofthelongestusernamesever", ""};
    char *pass_arr[] = {"","123","1:23","123","=-907897","12oUJ(&3","Ll#^e23","123","123","123thisisthelongestpassword","9"};
    
    Test_AuthAddUser(user_arr, pass_arr);

    Authenticator("oneofthelongestusernamesever", "123thisisthelongestpassword"); 

    AuthDeleteUser("oneofthelongestusernamesever");
    
    Authenticator("oneofthelongestusernamesever", "123thisisthelongestpassword"); 

   

    return 0;
}