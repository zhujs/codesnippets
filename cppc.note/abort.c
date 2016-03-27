#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<signal.h>
#include<setjmp.h>

jmp_buf buf;
void sigabrt(int a)
{
	printf("SIGABRT was caught\n");
	lognjmp( buf, 1 );
}


int main()
{
	signal( SIGABRT, SIG_IGN); 
	//signal( SIGABRT, sigabrt );

	if( setjmp( buf ) !=0)
		printf("setjmp\n");
	
	//override the ignore and exit; never return to caller( POSIX )
	abort();

	// never go here
	printf("After the call of abort function\n");
}



