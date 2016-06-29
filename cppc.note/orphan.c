#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void
sig_hup(int signo)
{
	printf("SIGHUP received, pid = %d\n", getpid());
}

static void
pr_ids(char *name)
{
	printf("%s: pid = %d, ppid = %d, pgrp = %d, tpgrp = %d\n",
	    name, getpid(), getppid(), getpgrp(), tcgetpgrp(STDIN_FILENO));
	fflush(stdout);
}

int
main(void)
{
	char	c;
	pid_t	pid;

	pr_ids("parent");
	if ((pid = fork()) < 0) {
		exit(1);
	} else if (pid > 0) {	/* parent */
		sleep(5);		/* sleep to let child stop itself */
		exit(0);		/* then parent exits */
	} else {			/* child */
		pr_ids("child");

		setsid();

		printf("Message from a new session\n");

		if (read(STDIN_FILENO, &c, 1) != 1)
			printf("read error from controlling TTY, errno = %d\n", errno);
		kill( getpid(), SIGTSTP ); // kernel ignores this signal due to its a orphaned process group

		printf("Read a character: %c\n", c ); // still can use the previous controlling terminal

		exit(0);
	}
}
