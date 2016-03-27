
#include <stdio.h>
#include <wchar.h>

const int LINE_NUM = 1024;

// test the effect of standard I/O on the Chinese file
int main()
{

	char content[LINE_NUM];

	FILE * file = fopen( "chinese", "r");

	//fget( file, content, LINE_NUM ); 
	
	scanf("%s", content);

	printf( "%s", content );

	return 0;
}
