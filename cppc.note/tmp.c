
#include<stdio.h>

// avoid the use of tmpnam and tmpname function due to the race condition
// Instead use the tmpfile and mkstemp function to create temporary files

int main()
{

	char message[1024];

	FILE *file = tmpfile(); // automatically unlink the file

	fputs( "Hello world!", file );

	rewind( file );
	fgets( message, sizeof( message ) , file );

	printf("%s\n", message );
	


	// the mkstemp function return the file descriptor
	// the template name must be a pathname whose last six characters
	// are set to XXXXXX

	char name[1024] = "./testXXXXXX";
	int fd = mkstemp ( name ); 
	
	printf( "%s\n", name );

	
	return 0;
}
