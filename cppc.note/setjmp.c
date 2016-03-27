#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>

jmp_buf env;

void callSetjmp() {
    int r = setjmp(env);
    if (r == 0) {
        printf("initialize setjmp\n");
    } else if(r==1) {
        printf("return from setjmp because of longjmp\n");
    }
}

void wrap() {
    callSetjmp();
}

void callLongjmp() {
    longjmp(env, 1);
}

int main( )
{
    //wrap();
    //callLongjmp();
    int r = setjmp(env);
    if (r == 0) {
        printf("initialize setjmp\n");
    } else if(r==1) {
        printf("return from setjmp because of longjmp\n");
    }

    longjmp(env, 1);
    printf("Can it get to here?\n");
	return 0;
}
