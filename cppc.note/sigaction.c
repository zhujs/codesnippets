#include "apue.h"
#include <errno.h>


void sigchld(int signo)
{
	printf("sigchld caught!\n");
}

int
main(void)
{
	pid_t	pid;


	// registers the SIGCHLD handler and specifies the SA_NOCLDWAIT
	// and SA_RESTART option flags
	struct sigaction sa, osa;
	sa.sa_handler = sigchld;
	sa.sa_flags = SA_NOCLDWAIT | SA_RESTART;

	sigaction( SIGCHLD, &sa, &osa );

	// the first child
	if ((pid = fork()) < 0) {
		exit(1);
	} else if (pid == 0) {	/* child */
		sleep(1);
		exit(0);	
	}

	if ((pid = fork()) < 0) {
		exit(1);
	} else if (pid == 0) {	/* second child*/
		sleep(5);
		exit(0);	
	}
	
	// the wait function call restarts when the first child terminates
	// blocks until the second child terminates
	wait(NULL ); 
	perror("wait");
}
