
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

// test the relational topoc of pipe
int main()
{

	int pipefd[2];

	pipe(pipefd);

	// whether the write end of the pipe will be blocked ?
	// How to guarantee the actomicity of pipe writing?
	
	int val = fcntl( pipefd[1], F_GETFL, 0 );
	val |= O_NONBLOCK;
	fcntl( pipefd[1], F_SETFL, val );


	struct stat pipeStat;

	fstat( pipefd[0], &pipeStat );

	if( S_ISFIFO( pipeStat.st_mode ) )
	{
		printf( "fstat function to test the file type of the pipe!");
	}
	return 0;
}
