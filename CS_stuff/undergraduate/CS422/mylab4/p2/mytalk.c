#include "p2.h"

int main(int argc, char** argv){
    //check argument
    if(argc!=2){
        fprintf(stderr,"Usage: %s <my-port-number>\n", argv[0]);
        exit(1);
    }
    sideflag = 2;
    int n;
	chatting = 0;
    struct sockaddr_in servaddr;        //server address
    //struct sockaddr_in cliaddr;
    struct sigaction handler;           //IO/POLL signal handling action
    struct sigaction handler2;          //ALRM signal handling action
    int port;                           //server port number
    port = atoi(argv[1]);
    //create socket
    sock=socket(AF_INET,SOCK_DGRAM,0);
    int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    //set up server address structure
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(port);
    //bind to the local address
    if(bind(sock,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0){
        perror("bind() failed");
        exit(1);
    }
    /* Set signal handler for SIGIO */
    handler.sa_handler = iohandler;
    handler2.sa_handler = alrmhandler;
    /* Create mask that mask all signals */
    if (sigfillset(&handler.sa_mask) < 0)
    perror("sigfillset() failed");
    if (sigfillset(&handler2.sa_mask) < 0)
    perror("sigfillset() failed");
    /* No flags */
    handler.sa_flags = 0;
    if (sigaction(SIGALRM, &handler2, 0) < 0)
    perror("sigaction() failed for SIGALRM");
    if (sigaction(SIGPOLL, &handler, 0) < 0)
    perror("sigaction() failed for SIGPOLL");
    if (sigaction(SIGIO, &handler, 0) < 0)
    perror("sigaction() failed for SIGIO");
    
    /* We must own the socket to receive the SIGIO message */
    if (fcntl(sock, F_SETOWN, getpid()) < 0)
    perror("Unable to set process owner to us");
    
    /* Arrange for nonblocking I/O and SIGIO delivery */
    if (fcntl(sock, F_SETFL, O_NONBLOCK | O_ASYNC) < 0)
    perror("Unable to put client sock into non-blocking/async mode");
    /* processing user input */
    int m,k;
	memset(str,0,200);
    char temp[100];
    /* get input from stdin */
    char c;
    int i;
    struct termios term1, term2;
    // remember original terminal setting
    tcgetattr(0, &term1);
    term2 = term1;
    // set to noncanonical mode and disable automatic echoing, i.e.,
    // keyboard characters are immediately returned and not echo'ed
    // to stdout
    term2.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &term2);
    // this code is for illustration purposes and must be adapted to
    // to fit one's app code
    i = 0;
    fprintf(stdout,">");
    while(1) {				// user types chat message
        c = getchar();
        if(c>=0 && c<=127)
            str[i] = c;			// store typed characters in a[];
        else continue;
        if(c == 3){
            exit(1);
        }
        if(c == 10){
            str[i]='\0';
            // when enter is pressed, send message according to the input
            /* check if this is the initiate command or not, chatting=0 means this is the initiation */
            if(chatting==0){
                timeoutflag = 1;
                chatting = 1;
                /* check if user want to quit */
                if(str[0]=='q' && str[1]=='\0'){
                    fprintf(stdout, "terminated by user.\n");
                    exit(0);
                }
                /* store ip and port into variables */
                for(m=0; m<strlen(str); m++){
                    if(str[m]==32){
                        tarIP[m]='\0';
                        break;
                    }
                    tarIP[m] = str[m];
                }
                k=0;
                while(m<strlen(str)){
                    temp[k] = str[m];
                    k++;
                    m++;
                }
                temp[k]='\0';
                tarport = atoi(temp);
                /* reset used strings */
                memset(str,0,200);
                memset(temp,0,100);
                memset(tarIP,0,100);
                /* try to start communicate with target IP and port number */
                sendrequest(argv[1]);
                
                memset(str,0,200);
                i=0;
                fprintf(stdout,"\n>");
                continue;
            }else{
                
                /* if input is empty */
                if(i==0) fprintf(stdout,"\n>");
                /* if input is c, accept chat request. sideflag=2 means this is the server side */
                if(str[0]=='c'&&str[1]=='\0'){
                    chatting = 1;
                    if(sideflag==2){
                        sendto(sock, "ok", strlen("ok"), 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
                    }else{
                        n=sendto(sock, "ok", strlen("ok"), 0, (struct sockaddr *)&target, sizeof(target));
                    }
                }
                /* if input is n, deny request */
                else if(str[0]=='n'&&str[1]=='\0'){
                    
                    if(sideflag==2){
                        sendto(sock, "ko", strlen("ko"), 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
                    }else{
                        sendto(sock, "ko", strlen("ko"), 0, (struct sockaddr *)&target, sizeof(target));
                    }
                }
                else{
                    /* otherwise, already in an active chat, send input message */
                    if(sideflag==2){
                        sendto(sock, str, strlen(str), 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));

                    }else{
                        sendto(sock, str, strlen(str), 0, (struct sockaddr *)&target, sizeof(target));
                    }
                }
            }
            fprintf(stdout,"\n>");
            /* clear buffer */
            memset(str,0,200);
            i=0;
            continue;
        }
        if ((c == 127) || (c == 8)) {	// if typed character is DEL or BS
            i = i - 1;			// then emulate backspace and print
            str[i] = '\0';			// corrected input on a new line
            fprintf(stdout,"\n>%s",str);
            continue;
        }else
        fputc(c, stdout);   // manual echo to stdout
        i++;
    }
    tcsetattr(0, TCSANOW, &term1);	// return terminal to default mode
}
