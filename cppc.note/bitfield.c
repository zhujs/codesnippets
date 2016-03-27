#include <stdlib.h>

#include <stdio.h>
#include <string.h>

struct
{
	unsigned int age :3;
	unsigned int :0; // start an new int
	unsigned int :2; // the 2 bits are not used
	unsigned int height :20;
} Age;

int main( )
{
	Age.age = 4;
	printf( "Sizeof( Age ) : %ld\n", sizeof(Age) );
	printf( "Age.age : %d\n", Age.age );

	Age.age = 7;
	printf( "Age.age : %d\n", Age.age );

	// the value will be truncated
	Age.age = 8;
	printf( "Age.age : %d\n", Age.age );

	return 0;
}
