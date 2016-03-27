
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <pthread.h>

#define PATHNAME_MAX 1024


// represents a file object in a directory
struct fileObject {
	char name[NAME_MAX + 1]; 	// file name
	time_t modTime;			// modification time of the file
	struct fileObject *next;		// next file object
};

struct fileObject* allFile = NULL;	// head pointer to the file objects link list


struct fileObject* head= NULL;
struct fileObject* tail= NULL;

pthread_mutex_t listLock  = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t listReady  = PTHREAD_COND_INITIALIZER;


// free the file objects link list
void freeFileObjects( struct fileObject *head )
{
	struct fileObject *temp;

	while( NULL != head)
	{
		temp = head->next;
		free( head );
		head = temp;
	}
}

void addFileObject( struct fileObject *head, char *fileName )
{
	struct fileObject * tempObject;
	if( NULL == ( tempObject = (struct fileObject *) malloc( sizeof( struct fileObject ) ) ) )
	{
		perror("malloc");
		exit(1);
	}

	strncpy( tempObject-> name, fileName , NAME_MAX+1 );
	tempObject-> modTime = 0;
	tempObject->next = allFile;
	
	allFile= tempObject;
}


void initDirStatus( char* dirName)
{
	DIR *dir = NULL;
	struct dirent *dirEntry = NULL;
	struct fileObject *tempObject;

	allFile = NULL;

	// open the directory 
	if( NULL == ( dir = opendir( dirName ) )  )
	{
		perror("opendir");
		exit(1);
	}

	// build a link list of all files in the directory
	while ( NULL != ( dirEntry = readdir( dir ) ) )
	{
		if( strcmp( dirEntry->d_name , "." ) == 0 ||
				0 == strcmp( dirEntry->d_name, ".." ) )
			continue;

		addFileObject( allFile, dirEntry->d_name);
	}

	closedir( dir );
}


int fileNotChanged(struct fileObject * fileHead, char * fileName )
{
	struct fileObject *temp, *tempHead = fileHead;

	while( NULL != tempHead)
	{
		temp = tempHead->next;

		if( 0 == strcmp( tempHead -> name , fileName) ) 
			return 1;
		tempHead = temp;
	}
	return 0;
}


// the thread detect the files change in the directory
void *thread_sync( void * para )
{
	char * dirName = (char *) para;
	int i = 0;
	
	for( ; ; )
	{
		DIR *dir = NULL;
		struct dirent *dirEntry = NULL;
		struct fileObject * tempObject = NULL ;

		// open the directory 
		if( NULL == ( dir = opendir( dirName ) )  )
		{
			perror("opendir");
			exit(1);
		}

		// build a link list of all files in the directory
		while ( NULL != ( dirEntry = readdir( dir ) ) )
		{
			if( strcmp( dirEntry->d_name , "." ) == 0 ||
					0 == strcmp( dirEntry->d_name, ".." ) )
				continue;

                        if ( 1 == fileNotChanged( allFile,  dirEntry->d_name ) )
				continue;

			addFileObject( allFile, dirEntry->d_name);


			// add a changed file to the updated list
			if( NULL == ( tempObject = (struct fileObject *) malloc( sizeof( struct fileObject ) ) ) )
			{
				perror("malloc");
				exit(1);
			}

			strncpy( tempObject-> name, dirEntry->d_name, NAME_MAX+1 );
			tempObject-> modTime = 0;
			tempObject->next = NULL;
			
			pthread_mutex_lock( &listLock );

			if ( NULL == tail )
				head = tempObject;
			else
				tail->next = tempObject;

			tail = tempObject;

			// signals the other thread to process the new file
			pthread_cond_signal( &listReady ) ;
			pthread_mutex_unlock( &listLock );

		}

		closedir( dir );

	}
	return NULL;
}

int main(int argc, char *argv[])
{


	char workingDir[PATHNAME_MAX];
	int err;
	pthread_t threadID;

	// open the current working directory and 
	// get initial directory status
	getcwd( workingDir, sizeof( workingDir ) );
	initDirStatus( workingDir );


	// create a thread to detect file change in the working directory
	err = pthread_create( &threadID, NULL, thread_sync,(void *) workingDir );

	if( err != 0)
	{
		perror("pthread_create");
		exit(1);
	}


	// wait for the new changed file
	struct fileObject *changedFile;
	for( ; ; )
	{
		pthread_mutex_lock( &listLock );

		while( NULL == head )
			pthread_cond_wait( &listReady, &listLock );


		changedFile = head;
		head = head->next;
		if ( NULL == head )
			tail = NULL;

		pthread_mutex_unlock( &listLock);

		printf("File %s: has been added!!\n", changedFile->name);

		free( changedFile );
	}

	pthread_join( threadID , NULL  );
	freeFileObjects( allFile );
}
