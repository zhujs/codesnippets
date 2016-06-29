#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	buf[500000];

// an interface to lock a file
// to save ourselves from having to allocate an flock structure
int lockfile( int fd, int cmd, int type, off_t  offset, int whence, off_t len)
{
	struct flock lock;

	lock.l_type = type;	// F_RDLCK, F_WRLCK, F_UNLCK
	lock.l_start = offset;	// byte offset,
	lock.l_whence = whence;
	lock.l_len = len;

	return ( fcntl( fd, cmd,  &lock ) );
}

int main( int argc, char** argv)
{
	
	if(argc != 2 )
		exit(1);

	int fd;
	if( ( fd = open( argv[1], O_RDWR ) ) < 0 )
	{
		perror("open function");
		exit(1);
	}

	// try to lock the whole file, we can't use the F_GETLK command to
	// test whether the file has been locked in the same file
	if( lockfile( fd, F_SETLK, F_WRLCK, 0, SEEK_SET, 0 ) < 0 )
	{
		perror("lockfile");
		exit(1);
	}

	int newfd = dup( fd );
	close( newfd );

	// the chile process should acquire the write lock of the file
	// due to the locks are associated with a process
	pid_t pid = fork();
	if( pid == 0 )
	{
		if( lockfile( fd, F_SETLK, F_WRLCK, 0, SEEK_SET, 0 ) < 0 )
		{
			perror("lockfile");
			exit(1);
		}
		else
		{
			printf("In chile, wirte lock succeed.\n");
		}
		exit(0);
	}

	exit(0);
}
