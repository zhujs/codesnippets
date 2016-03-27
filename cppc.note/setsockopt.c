/* Use standard echo server; baseline measurements for nonblocking version */
#include	"unp.h"

int
main(int argc, char **argv)
{
	int					sockfd;
	struct sockaddr_in	servaddr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	int sndSize = 1023;
	int sndLowMark = 1024;


	if ( -1 == setsockopt( sockfd, SOL_SOCKET, SO_SNDBUF, &sndSize, sizeof( sndSize ) ) )
		perror( "setsockopt for SO_SNDBUF");

	if ( -1 == setsockopt( sockfd, SOL_SOCKET, SO_SNDLOWAT, &sndLowMark, sizeof(sndLowMark)) ) // this option is not changeable on Linux, set socket(7)
		perror( "setsockopt for SO_SNDLOWAT");

	fd_set writeSet;

	FD_ZERO( &writeSet );
	FD_SET( sockfd, &writeSet );

	if ( -1 == select( sockfd + 1, NULL, &writeSet, NULL, NULL ) )
		perror( "select ");

	exit(0);
}
