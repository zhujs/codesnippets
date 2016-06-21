#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int glob = 6;

int main(void)
{
	int var;
	pid_t pid;
	var = 88;
	printf("before vfork"); /* don't flush the output */

	if((pid = vfork() ) < 0 )
	{
		printf("Error\n");
	}
	else if ( 0 == pid ) 
	{
		/* share the same output if using vfork to create new child */
		glob++;
		var++;
		printf("vfork\n"); 

        /*execlp("echo", "echo", "hello, vfork", 0);*/

        // Should never return in vfork child! 会破坏栈数据，父进程报错
        /*return 0;*/ 
		exit(0);
	}

	fflush(NULL);
	printf ( "pid = %d, glob=%d, var = %d\n", getpid(), glob, var);
	exit(0);
}
