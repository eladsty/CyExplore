#include <stdlib.h>/* exit */
#include <string.h>/* strbcmp */
#include <stdio.h>/* printf */
#include <sys/types.h>/* fork */
#include<sys/wait.h>/* wait */
#include <unistd.h>/* exec */

 #define CMD_BUFF_SIZE 255
 


/* Status : Approved
 * Reviewer : Hen
 * arguments: pointer to string.
 * Description : fork and execv the command in the string it receives as an argument
 * return: 0
*/

int Fork_Way(char *input)
{
    char *command_args[CMD_BUFF_SIZE] = {0};
    int i = 0; 
    pid_t pid = 0;
    char *new_line = NULL;
    new_line = strchr(input, '\n');
     if(NULL != new_line)
    {
      *new_line = '\0';
    }
    command_args[0] = strtok(input, " ");

    while( NULL !=  command_args[i]) 
    {
        ++i;
        command_args[i] = strtok(NULL, " ");
     }
    pid = fork();
    switch (pid) {
 		case -1:			/* fork failed */
 			perror ("fork");
 			exit (1);
 		case 0:			/* in new child process */
            if(-1 == execvp(command_args[0],  command_args))
            {
                printf("command not found. \n");
            }		
 		    exit (0);
 		default:	 /* in parent  */
            wait(0);
  			break;
 	}
 
	return 0;	
}



/* Status : Approved
 * Reviewer : Hen
 * arguments: none.
 * Description : creates a simple shell and let the user run commands through system and fork + exec.
 * return: void
*/
void SimpleShell()
{
    char *p_input = NULL;
    char cmd_buffer[CMD_BUFF_SIZE] = {0}; 
    int status = 0;
    while(1) 
    {
        printf("Type a command using system or fork: \n");
          
        if (NULL != fgets(cmd_buffer, CMD_BUFF_SIZE, stdin))
        {            
            p_input = strchr(cmd_buffer, ' ');

            if ( NULL != p_input )
            {
                *p_input = '\0';
            }
            if(0 == strcmp(cmd_buffer, "exit\n"))
            {
                printf("exit.\n");
                exit(0);
            }
            if(0 == strcmp(cmd_buffer, "system"))
            {
                status = system((p_input+1));
                if(0 != status)
                {
                    printf("command not found. \n");

                }
            }

            if(0 == strcmp(cmd_buffer, "fork"))
            {
                 Fork_Way( (p_input+1) );
            }
        }
    }
}



int main()
{
    SimpleShell();
     
    return 0;
}


 