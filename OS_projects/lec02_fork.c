#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

main(){
	int pid;
	int was=3;

	pid=fork();

	if(pid<0) {
		printf("Fork failed\n");
		exit(1);
	}else if(pid==0){
		sleep(2);
		printf("\nChild process: pid=%d was=%d \n", pid, was);
		//execl("/bin/ls", "ls", NULL);
		//printf("child process: after execl was=%d \n", was);
		exit(0);
	}else{
		was=4;
		printf("Parent process: pid is %d was=%d\n", pid, was);
		exit(0);
	}

}
