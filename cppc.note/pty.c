
#define _XOPEN_SOURCE 600

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>


// the psudo terminal interface on Linux
// ignore all error checking
int main(int argc, char** argv)
{

	int fdmaster, fdslave;

	// open the first unused PTY master device;
	fdmaster = posix_openpt( O_RDWR );
	
	printf( "The pt master name: %s\n", ttyname( fdmaster ) );
	printf( "The pt slave name: %s\n", ptsname( fdmaster ) );

	grantpt( fdmaster ); // change the pt slave's permissions

	unlockpt( fdmaster ); // clear slave's lock flag

	// open the salve device
	fdslave = open( ptsname(fdmaster) , O_RDWR );


	pid_t pid = fork();

	if( pid == 0 ) // in child
	{

		int fd = open( ptsname(fdmaster) , O_RDWR );
		char message[] = "Message sent from slave in the child\n";
		write( fd, message, sizeof(message) );

		_exit(1); // prevent from closing standard I/O
	}

	wait(NULL );

	char message[1024] ;
	read( fdmaster ,  message,  1024);

	write( STDOUT_FILENO, message, strlen(message) ); // write to standard output

	close( fdmaster );
	close( fdslave );
	return 0;
}








