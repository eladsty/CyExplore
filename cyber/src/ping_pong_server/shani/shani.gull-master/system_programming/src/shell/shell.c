#include <sys/types.h> /* fork || wait */
#include <unistd.h> /* access || fork || exec */
#include <stdlib.h> /* system */
#include <stdio.h> /* gets */

#include "../../include/shell/shell.h"
#define MAX_COMMAND 4096

static int CountWords(char *command_line);
static void ArgSpliter(char **arg_list, char *args);

/* checks if a file "str" exists and if the process has execute permissions */

static int CountWords(char *command_line)
{
	int counter = 1;
	while ('\0' != *command_line)
	{
		if (' ' == *command_line)
		{
			++counter;
		}
		++command_line;
	}
	return counter;
}

static void ArgSpliter(char **arg_list, char *args)
{
	int i = 0;
	int words = CountWords(args);
	while (1 < words)
	{
		arg_list[i] = strtok(args, " ");
		args += strlen(arg_list[i]) + 1;
		++i;
		--words;
	}
	arg_list[i] = strtok(args, "\n");
	++i;
	arg_list[i] = NULL;
}
/* Status : approved
 * Reviewer : adi
 * Description : implement process spawning using fork and exec function
 * Arguments : string as a command line argument
 * Return : void
 * Time Complexity : O(1)
 * Space Complexity : O(1)
 */
void ForkExecShell(char *command)
{
	pid_t child;
	int child_status;
	char *command_line_args[256] = {NULL};
	child = fork();
	if (0 == child)
	{
		/* this is child process. */
		if (CountWords(command))
		{
			ArgSpliter(command_line_args, command);
		}
		child_status = execvp(command_line_args[0], command_line_args);
		perror("an error occured: ");
		exit(-1);
	}
	else
	{
		/* this is parent */
		wait(&child_status);
		if (WIFEXITED(child_status))
		{
			return;
		}
		else if (WIFSIGNALED(child_status))
		{
			WTERMSIG(child_status);
		}
	}
	return;
}


/* Status : approved
 * Reviewer : adi
 * Description : implement process spawning using system function
 * Arguments : string of arguments from user
 * Return : void
 * Time Complexity : O(1)
 * Space Complexity : O(1)
 */
void SystemShell(char *argument_vector)
{
	int ret = system(argument_vector);
	if (127 == ret || -1 == ret)
	{
		perror("error occured: ");
	}
}

/* Status : approved
 * Reviewer : adi
 * Description : configures which type af spawning the user chose and directs it
 * 				correctly to the coresponding function
 * Arguments : flag stating either system or fork
 * Return : void
 * Time Complexity : O(1)
 * Space Complexity : O(1)
 */
void MAS(char *configurations)
{
	char command[4096] = {'\0'};
	config configure;
	if (!strncmp("-system", configurations, 7))
	{
		configure = SYSTEM;
	}
	else if (!strncmp("-fork", configurations, 5))
	{
		configure = FORK_EXEC;
	}
	else
	{
		return;
	}
	printf("$ ");
	fgets(command, MAX_COMMAND, stdin);
	while(strncmp("exit", command, 4))
	{
		switch (configure)
		{
		case FORK_EXEC:
			ForkExecShell(command);
			break;
		case SYSTEM:
			SystemShell(command);
		default:
			break;
		}
		printf("$ ");
		fgets(command, MAX_COMMAND, stdin);
	}
}


