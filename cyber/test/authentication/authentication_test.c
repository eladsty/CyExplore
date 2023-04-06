#include "authentication.h"



int main()
{
       AuthAddUser("elad", "123");
        AuthAddUser("eladad", "123");
        AuthAddUser("shlomi", "123");
       AuthAddUser("elad", "123");
        AuthAddUser("eelad", "123");
        AuthAddUser("", "123");        
        AuthAddUser(":", "123");
        AuthAddUser(" ", "123");
         AuthDeleteUser("eelad");
        AuthDeleteUser("eelad");
        AuthDeleteUser("not_a_user");

    printf(" real user real password %d\n", AuthAuthenticate("elad", "123"));
    printf(" real user wrong password %d\n", AuthAuthenticate("eladad", "1234"));
    printf(" real password wrong user %d\n", AuthAuthenticate("eladude", "123"));
    printf("wrong password and username%d\n", AuthAuthenticate("e43lad", "12e2e23"));
    printf("real user%d\n", AuthAuthenticate("shlomi", "123"));


    return 0;
}