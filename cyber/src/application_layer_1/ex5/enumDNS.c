#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>


#define DIC_PATH "/home/elad/elad.shem-tov/cyber/src/application_layer_1/ex5/3Kwords.txt"
 
void EnumDNS(const char *url)
{
    struct hostent *remote_host;
    char line_buff[150] = {0};
    char current_word[50] = {0};
    char *end_of_line = NULL;
    int i = 0;
    FILE *fd = fopen(DIC_PATH, "r");;
    if(!fd)
    {
        printf("fd is NULL");
        return;
    }
     
    while (fgets(line_buff, 100, fd) != NULL)
    {
        end_of_line = strchr(line_buff,'\n');
        strncpy(current_word, line_buff, (end_of_line - line_buff));
        *end_of_line = '.';
        ++end_of_line;
        *end_of_line = '\0';
        strcat(line_buff, url);
        remote_host = gethostbyname(line_buff);
        if(NULL != remote_host)
        {
            while(remote_host->h_addr_list)
            {
               printf("%s \n",line_buff);
               break;
            }
         }
     }
 
    fclose(fd);

    return;
}

int main()
{
    char *url = "ynet.co.il";

    EnumDNS(url);
 
    return 0;    
}
