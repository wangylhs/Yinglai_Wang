
const char * usage =
"                                                               \n"
"daytime-server:                                                \n"
"                                                               \n"
"Simple server program that shows how to use socket calls       \n"
"in the server side.                                            \n"
"                                                               \n"
"To use it in one window type:                                  \n"
"                                                               \n"
"   daytime-server <port>                                       \n"
"                                                               \n"
"Where 1024 < port < 65536.             \n"
"                                                               \n"
"In another window type:                                       \n"
"                                                               \n"
"   telnet <host> <port>                                        \n"
"                                                               \n"
"where <host> is the name of the machine where daytime-server  \n"
"is running. <port> is the port number you used when you run   \n"
"daytime-server.                                               \n"
"                                                               \n"
"Then type your name and return. You will get a greeting and   \n"
"the time of the day.                                          \n"
"                                                               \n";


#include <sys/types.h>
#include<sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include<iostream>
#include <fcntl.h>
using namespace std;
int QueueLength = 5;

// Processes time request
void processTimeRequest( int socket );
void threadRequest(int slaveSocket);
void killzombie(int i);
void Pool(int masterSocket);

pthread_mutex_t _mutex;
int
main( int argc, char ** argv )
{
	
  struct sigaction signalAction;
  signalAction.sa_handler=killzombie;
  sigemptyset(&signalAction.sa_mask);
  signalAction.sa_flags=SA_RESTART;
  int zombie=sigaction(SIGCHLD,&signalAction,NULL);
  if(zombie){
    perror("Zombie");
    exit(1);
}


  // Print usage if not enough arguments
  if ( argc < 2 ) {
    fprintf( stderr, "%s", usage );
    exit( -1 );
  }
  int _f=0,_t=0,_p=0;
  //check -f -p -t
  for(int i=0;i<argc;i++){
    if(strcmp(argv[i],"-f")==0)
      _f=1;
    else if(strcmp(argv[i],"-t")==0)
      _t=1;
    else if (strcmp(argv[i],"-p")==0)
      _p=1;
  }
  pthread_mutex_init(&_mutex,NULL);

  // Get the port from the arguments
  int port = atoi( argv[1] );
  
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

  if(_p){
    pthread_t thread[5];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
    for(int i=0;i<5;i++)
      pthread_create(&thread[i],&attr,(void*(*)(void*))Pool,(void*)masterSocket);
    pthread_join(thread[0],NULL);
  }
  else {
    while ( 1 ) {
      if(_f){

	  // Accept incoming connections
	  struct sockaddr_in clientIPAddress;
	  int alen = sizeof( clientIPAddress );
	  // pthread_mutex_lock(&_mutex);
	  int slaveSocket = accept( masterSocket,
				    (struct sockaddr *)&clientIPAddress,
				    (socklen_t*)&alen);
	  //pthread_mutex_unlock(&_mutex);
	
	  int ret=fork();
	  if(ret==0){
	    processTimeRequest(slaveSocket);
	    close(slaveSocket);
	    exit(EXIT_SUCCESS);
	  }
	  else if(ret<0){
	    perror("fork");
	    exit(0);
	}
	  close(slaveSocket);
      }
      else if(_t){
	
	// Accept incoming connections
	struct sockaddr_in clientIPAddress;
	int alen = sizeof( clientIPAddress );
	pthread_mutex_lock(&_mutex);
	int slaveSocket = accept( masterSocket,
				  (struct sockaddr *)&clientIPAddress,
				  (socklen_t*)&alen);
	pthread_mutex_unlock(&_mutex);
	if ( slaveSocket < 0 ) {
	  perror( "accept _t" );
	  exit( -1 );
	}
	pthread_t thread;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
	int ret=pthread_create(&thread,&attr,(void*(*)(void*))threadRequest,(void*)slaveSocket);
	if(ret<0)
	  perror("thread");
	//	int check= pthread_join(thread,NULL);
	pthread_detach(thread);
	//close(slaveSocket);
      }
      else{
	// Accept incoming connections
	struct sockaddr_in clientIPAddress;
	int alen = sizeof( clientIPAddress );
	pthread_mutex_lock(&_mutex);
	int slaveSocket = accept( masterSocket,
				  (struct sockaddr *)&clientIPAddress,
				  (socklen_t*)&alen);
	pthread_mutex_unlock(&_mutex);
	if ( slaveSocket < 0 ) {
	  perror( "accept without" );
	  exit( -1 );
	}
	processTimeRequest(slaveSocket);
	close(slaveSocket);
      }
    }
  }
}
void threadRequest(int slaveSocket){
  processTimeRequest(slaveSocket);
  close(slaveSocket);
}
void Pool(int masterSocket){
  while(1){
    struct sockaddr_in clientIPAddress;
    int alen = sizeof( clientIPAddress );
    pthread_mutex_lock(&_mutex);
    int slaveSocket = accept( masterSocket,
			      (struct sockaddr *)&clientIPAddress,
			      (socklen_t*)&alen);
    pthread_mutex_unlock(&_mutex);
    if( slaveSocket == -1)
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
void killzombie(int i){
  if(i==SIGCHLD)
    while(waitpid(-1,NULL,WNOHANG)>0);
}
void
processTimeRequest( int fd )
{
  // Buffer used to store the name received from the client
  const int MaxName = 1024;
  char name[ MaxName + 1 ];
  int nameLength = 0;
  int n;

  // Send prompt
  //const char * prompt = "\nType your name:";
  //write( fd, prompt, strlen( prompt ) );

  // Currently character read
  unsigned char newChar;

  // Last character read
  unsigned char lastChar = 0;
  int gotGet=0;
  int gotDoc=0;
  //
  // The client should send <name><cr><lf>
  // Read the name of the client character by character until a
  // <CR><LF> is found.
  //
  char cwd[256]={0};
  getcwd(cwd,sizeof(cwd));
  if(cwd==NULL)
      fprintf(stderr,"The directory is wrong!\n");
  while ( nameLength < MaxName &&
	  ( n = read( fd, &newChar, sizeof(newChar) ) ) > 0 ) {
    if(newChar==' '){
      if(gotGet==0)
	gotGet=1;
      else if(gotDoc==0){
	gotDoc=1;
	name[nameLength]=0;
      }
    }
    else if ( lastChar == '\015' && newChar == '\012' ) {
      // Discard previous <CR> from name
      nameLength--;
      break;
    }
    
    name[ nameLength ] = newChar;
    nameLength++;

    lastChar = newChar;
  }

  // Add null character at the end of the string
  name[ nameLength ] = 0;
  //get the docpath
  char * docpath;
  for(int i=0;i<nameLength;i++)
    {
      if(name[i]==' '){
	docpath=name+i+1;
	int j=0;
	for(j=0;docpath[j]!=' ';j++);
	*(docpath+j)=0;
      }
    }
  strcpy(name,docpath);
  //printf("docptah is %s||%s\n",docpath,name);
  //get icons and htdocs
  char *icons=strstr(name,"/icons");
  char *htdocs=strstr(name,"/htdocs");
  char *script=strstr(name,"/cgi-bin");
  char *argument=strstr(name,"?");

  if(icons){
    strcat(cwd,"/http-root-dir");
    strcat(cwd,name);
  }
  else if(htdocs){
    strcat(cwd,"/http-root-dir");
    strcat(cwd,name);
  }
  else if(script){
    strcat(cwd,"/http-root-dir");
    strcat(cwd,name);
  }
  else{
    strcat(cwd,"/http-root-dir/htdocs");
    if(strcmp(name,"/")==0)
      strcat(cwd,"/index.html");
    else
      strcat(cwd,name);
  }
    
  if(argument){
    argument++;
    char temp[256];
    int l1=strlen(cwd);
    int l2=strlen(argument);
    for(int i=0;i<(l1-l2-1);i++)
      temp[i]=cwd[i];
    temp[l1-l2-1]=0;
    strcpy(cwd,temp);
  }
  //fprintf(stderr,"%s\n",cwd);
  //get realpath
  char real[nameLength];
  realpath(cwd,real);
  //get contentType
  char *contentType;
  contentType=(char*)malloc(sizeof(char)*256);
  if(strstr(cwd,".html")!=0)
    strcpy(contentType,"text/html");
  else if(strstr(cwd,".gif"))
    strcpy(contentType,"image/gif");
  else
    strcpy(contentType,"text/plain");
  int fp;
  //fp=open(cwd,O_RDONLY);
  FILE * ifp=fopen(cwd,"r");
  const char *crlf="\r\n";
  const char*serverType="CS 290 lab3";
  const char*notFound="File not Found";
  if(ifp==NULL){
    write(fd,"HTTP/1.0",strlen("HTTP/1.0"));
    write(fd," ",1);
    write(fd,"404",3);
    write(fd,"File",4);
    write(fd,"Not",3);
    write(fd,"Found",5);
    write(fd,crlf,2);
    write(fd,"Server:",7);
    write(fd, " ", 1);
    write(fd, serverType, strlen(serverType));
    write(fd, crlf, 2);
    write(fd, "Content-type:", 13);
    write(fd, " ", 1);
    write(fd, contentType, strlen(contentType));
    write(fd, crlf, 2);
    write(fd, crlf, 2);
    write(fd, notFound, strlen(notFound));
  }
  else{
    write(fd,"HTTP/1.0",strlen("HTTP/1.0"));
    write(fd," ",1);
    write(fd,"200",3);
    write(fd," ",1);
    write(fd,"Document",strlen("Document"));
    write(fd,"follows",strlen("follows"));
    write(fd,crlf,2);
    write(fd,"Server:",7);
    write(fd," ",1);
    write(fd,serverType,strlen(serverType));
    write(fd,crlf,strlen(crlf));
    if(!script){
      write(fd,"Content-type:",13);
      write(fd," ",1);
      write(fd,contentType,strlen(contentType));
      write(fd,crlf,2);
      write(fd,crlf,2);
    }
    int count;
    //char buffer;
    char *buffer;
    char *shabi[3];
    shabi[0] = strdup(real);
    if(argument){
      setenv("QUERY_STRING",argument,1);
      //printf("%s\n",getenv("QUERY_STRING"));
      shabi[1]=argument;
      shabi[2]=NULL;
    }
    else
      shabi[1]=NULL;
    if(script){
      setenv("REQUEST_METHOD","GET",1);
      int tempout=dup(1);
      dup2(fd,1);
      int ret=fork();
      //fprintf(stderr,"haha\n");
      if(ret==0){
	execv(shabi[0],shabi);
	perror("fork");
	_exit(1);
      }
      else if(ret<0)
	perror("fork in script");
      else
	waitpid(ret,NULL,NULL);
      dup2(tempout,1);
      close(tempout);
      
    setenv("QUERY_STRING","",1);

    }
    else {
      // while(count=read(fp,&buffer,1))
      //	if(write(fd,&buffer,1)!=count)
      //	  perror("write");
      //close(fp);
      fseek(ifp,0,SEEK_END);
      long int size=ftell(ifp);
      rewind(ifp);
      buffer=(char*)malloc(sizeof(char)*size);
      fread(buffer,1,size,ifp);
      write(fd,buffer,size);
      //printf("%d\n",size);
    }
    //fprintf(stderr,"here~~~\n");
    fclose(ifp);
    free(buffer);
  }
}
