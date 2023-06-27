    #include <signal.h>           /* Definition of SIG* constants */
       #include <sys/syscall.h>      /* Definition of SYS_* constants */
       #include <unistd.h>



       #include <signal.h>

 /*       int syscall(SYS_tkill, pid_t tid, int sig);*/

int main()
{
	while(1)
	{
		syscall(SYS_tkill, 35332, 15);
	}
	
	return 0;
}
