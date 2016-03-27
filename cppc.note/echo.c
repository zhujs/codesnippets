
#include<stdio.h>
#include<unistd.h>
#include<termios.h>

// test the effect of several terminal option flag 
// It clears the input by typing the corresponding key but does not errases
// the output from the display

int main()
{

	struct termios ts, ots;

	tcgetattr( STDIN_FILENO, &ts );

	ots = ts;

	// reset these flags
	ts.c_lflag &= ~ ( ECHOK | ECHONL | ECHOE);
	
	// reset the ICRNL input option, type ^J to enter '\n'
	ts.c_iflag &= ~ ( ICRNL );

	//ts.c_oflag &= ~ ( TABDLY );
	//ts.c_oflag |= TAB3;


	tcsetattr( STDIN_FILENO, TCSAFLUSH, &ts );


	printf( "Enter to test:" );
	scanf("%*s"); //ignore the input

	// restore the status of terminal
	tcsetattr( STDIN_FILENO, TCSAFLUSH, &ots );

}
