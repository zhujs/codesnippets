#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<signal.h>


void sigint(int a)
{
	printf("SIGINT was caught\n");
}


int main()
{

	
	char c;
	signal( SIGINT, sigint );

again:
	// linux restart the read function if we type ctrl-c
	if( read( STDIN_FILENO, &c, 1) < 0)  
	{
		if( errno == EINTR )
		{
			printf("Interrupted by signal.\n");
			goto again;
		}
	}
	write ( STDIN_FILENO, &c, 1);
}



