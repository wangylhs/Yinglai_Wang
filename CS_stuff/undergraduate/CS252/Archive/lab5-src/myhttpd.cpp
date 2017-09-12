
const char * usage ="myhttpd [-f|-t|-p] [<port>]\n";

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <pthread.h>
#include <errno.h>

int QueueLength = 5;

// Processes time request
void processTimeRequest( int socket );

void killZombie(int id){
	while(waitpid(-1,NULL,WNOHANG)>0);
	return;
}
void processThread(int slaveSocket);


void threadPool(int masterSocket);

int main( int argc, char ** argv ) {

	//kill zombie processes
	struct sigaction sig;

	sig.sa_handler = killZombie;
	sig.sa_flags = SA_RESTART;
	sigaction(SIGCHLD, &sig, NULL); //killing zombie


	int port = 5555;
	int flag = 0;
	// Print usage if not enough arguments
	if( argc < 2 ){
		port = 5555;
	}

	else if(argc==2){
		if(!strcmp(argv[1],"-t")){
			flag=1;
		}
		else if(!strcmp(argv[1],"-p")){
			flag=2;
		}
		else if(!strcmp(argv[1],"-f")){
			flag=3;
		}
		else{
			port = atoi(argv[1]);
		}
	}
	else if(argc==3){
		if(!strcmp(argv[1],"-t")){
			flag=1;
		}
		else if(!strcmp(argv[1],"-p")){
			flag=2;
		}
		else if(!strcmp(argv[1],"-f")){
			flag=3;
		}
		port = atoi(argv[2]);
	}

	else{
		fprintf(stderr,"%s",usage);
	}

	if(port >= 65536 || port <= 1024){
		fprintf(stderr, "Invalid Port: Make sure it is larger than 1024 and less than 65536\n");
		exit(0);
	}


	// Set the IP address and port for this server
	struct sockaddr_in serverIPAddress;
	memset( &serverIPAddress, 0, sizeof(serverIPAddress) );
	serverIPAddress.sin_family = AF_INET;
	serverIPAddress.sin_addr.s_addr = INADDR_ANY;
	serverIPAddress.sin_port = htons((u_short) port);

	// Allocate a socket
	int masterSocket =  socket(PF_INET, SOCK_STREAM, 0);
	if ( masterSocket < 0) {
		perror("socket");
		exit( -1 );
	}

	// Set socket options to reuse port. Otherwise we will
	// have to wait about 2 minutes before reusing the sae port number
	int optval = 1;
	int err = setsockopt(masterSocket, SOL_SOCKET, SO_REUSEADDR,
			(char *) &optval, sizeof( int ) );

	// Bind the socket to the IP address and port
	int error = bind( masterSocket,
			(struct sockaddr *)&serverIPAddress,
			sizeof(serverIPAddress) );
	if ( error ) {
		perror("bind");
		exit( -1 );
	}

	// Put socket in listening mode and set the
	// size of the queue of unprocessed connections
	error = listen( masterSocket, QueueLength);
	if ( error ) {
		perror("listen");
		exit( -1 );
	}

	if(flag==2){
		//fprintf(stderr, "Thread Pool!\n");
		pthread_t threads[5];
		pthread_attr_t attr;

		pthread_attr_init(&attr);
		pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

		for(int i=0; i<5; i++)
			pthread_create(&threads[i], &attr, (void * (*)(void *))threadPool, (void *)masterSocket);
	}


	while ( 1 ) {

		if(flag==1){
			//fprintf(stderr, "Thread!\n");
			struct sockaddr_in clientIPAddress;
			int alen = sizeof( clientIPAddress );
			int slaveSocket = accept( masterSocket,
					(struct sockaddr *)&clientIPAddress,
					(socklen_t*)&alen);

			if ( slaveSocket < 0 ) {
				perror( "accept" );
				exit( -1 );
			}
			pthread_t thread;
			pthread_attr_t attr;

			pthread_attr_init(&attr);
			pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

			pthread_create(&thread, &attr, (void * (*)(void *))processThread, (void *)slaveSocket);
		}

		else if(flag==3){
			int ret = fork();

			if(ret==0){
				//fprintf(stderr, "Forking!\n");
				// Accept incoming connections
				struct sockaddr_in clientIPAddress;
				int alen = sizeof( clientIPAddress );
				int slaveSocket = accept( masterSocket,
						(struct sockaddr *)&clientIPAddress,
						(socklen_t*)&alen);

				if ( slaveSocket < 0 ) {
					perror( "accept" );
					exit( -1 );
				}

				// Process request.
				processTimeRequest( slaveSocket );

				// Close socket
				close( slaveSocket );

				exit(0);
			}
		}

		else{
				// Accept incoming connections
				struct sockaddr_in clientIPAddress;
				int alen = sizeof( clientIPAddress );
				int slaveSocket = accept( masterSocket,
						(struct sockaddr *)&clientIPAddress,
						(socklen_t*)&alen);

				if ( slaveSocket < 0 ) {
					perror( "accept" );
					exit( -1 );
				}

				// Process request.
				processTimeRequest( slaveSocket );

				// Close socket
				close( slaveSocket );
		}

	}
}

void threadPool(int masterSocket){
	while ( 1 ) {

		// Accept incoming connections
		struct sockaddr_in clientIPAddress;
		int alen = sizeof( clientIPAddress );
		int slaveSocket = accept( masterSocket,
				(struct sockaddr *)&clientIPAddress,
				(socklen_t*)&alen);

		if( slaveSocket == -1 && errno == EINTR)
			continue;

		if ( slaveSocket < 0 ) {
			perror( "accept" );
			exit( -1 );
		}

		// Process request.
		processTimeRequest( slaveSocket );

		// Close socket
		close( slaveSocket );
	}

}


void processThread(int slaveSocket){
	processTimeRequest( slaveSocket );
	close (slaveSocket);
}


void
processTimeRequest( int fd )
{
	const int size = 1024;
	char url[size];
	int n;
	int len=0;
	char ch1=0, ch2=0;

	int docFound=0;
	int getFound=0;

	char path[size];

	if(getcwd(path, size)==NULL){
		fprintf(stderr, "Directory not Found!\n");
	}

	while(n=read(fd, &ch1, sizeof(ch1))){
		if(ch1==' '){
			if(getFound==0){
				getFound=1;
			}
			else if(docFound==0){
				docFound=1;
				url[len]=0;
			}
		}

		else if(ch1=='\n' && ch2=='\r'){
			break;
		}

		else if(getFound && !docFound){
			url[len] = ch1;
			len++;
		}

		ch2 = ch1;
	}

	//	fprintf(stderr, "URL: %s\n", url);

	char * icons = strstr(url, "icons/");
	char * cgi = strstr(url, "cgi-bin/");

	if(icons || cgi){
		strcat(path, "/http-root-dir");
		strcat(path, url);
	}
	else{
		strcat(path, "/http-root-dir/htdocs");
		if(strcmp(url,"/")==0){
			strcat(path, "/index.html");
		}
		else{
			strcat(path,url);
		}
	}

	fprintf(stderr, "path: %s\n", path);


	char * contentType = (char *)malloc(sizeof(char*));

	if(strstr(path, ".html")!=0){
		strcpy(contentType,"text/html");
	}

	else if(strstr(path, ".gif")!=0){
		strcpy(contentType,"image/gif");
	}
	else{
		strcpy(contentType, "text/plain");
	}

	FILE *fp = fopen(path,"r");

	const char *end = "\r\n";

	const char *server = "SERVER: 252";
	char *content = (char*)malloc(size*sizeof(char*));
	strcpy(content, "Content-type: ");

	strcat(content, contentType);

	fprintf(stderr, "%s\n", content);

	if(fp==NULL){
		write(fd, "HTTP/1.0 404 File Not Found", strlen("HTTP/1.0 404 File Not Found"));
		write(fd, end, strlen(end));
		write(fd, server, strlen(server));
		write(fd, end, strlen(end));
		write(fd, content, strlen(content));
		write(fd, end, strlen(end));
		write(fd, end, strlen(end));
		write(fd, "404 File Not Found", strlen("404 File Not Found"));
	}
	else{
		write(fd, "HTTP/1.0 200 Document follows", strlen("HTTP:1.0 200 Document follows"));
		write(fd, end, strlen(end));
		write(fd, server, strlen(server));
		write(fd, end, strlen(end));
		write(fd, content, strlen(content));
		write(fd, end, strlen(end));
		write(fd, end, strlen(end));
		char ch = fgetc(fp);
		while(!feof(fp)){
			write(fd, &ch, 1);
			ch = fgetc(fp);
		}
	}

}

