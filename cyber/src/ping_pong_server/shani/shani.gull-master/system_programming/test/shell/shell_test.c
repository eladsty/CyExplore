#include "../../include/shell/shell.h"
#include <unistd.h> /* access || fork || exec */

int main(int argc, char *argv[], char *envp[])
{
	MAS(argv[1]);
	return (0);
}

