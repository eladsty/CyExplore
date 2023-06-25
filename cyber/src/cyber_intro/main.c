#include <stdio.h>
#include <string.h>


int IsAllowedUser(char *username)
{
  return 0;
}

void PrivilegedAction()
{
  printf("you are priviledged!");
}

int main () {
     char username[8];
     int allow = 0;
    printf("aloow:%p \n usrname: %p ",  &allow,  &username);
    
    printf("Enter your username, please: ");
    gets(username);

    if (IsAllowedUser(username)) {
        allow = 1;
    }

    if (allow) {
        PrivilegedAction();
    }
    else
    {
      printf("you are not priviledged");
    }
    

    return 0;
}
