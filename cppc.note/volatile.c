
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

// 如果没有volatile关键字，并以gcc -O3 volatile来编译该程序
// 该程序会一直死循环
sig_atomic_t flag = 0;
// volatile sig_atomic_t flag = 0;


static void sigint( int signo )
{

	flag = 1;
	printf("SIGINT signal received.\n");

}

int main()
{
	if( signal( SIGINT, sigint ) == SIG_ERR )
		exit(1);

	// if compiler optimizes the code, it will not fetch the value of 
	// flag stored in memory
	while( flag == 0 );

	printf("Ending main.\n");
}
