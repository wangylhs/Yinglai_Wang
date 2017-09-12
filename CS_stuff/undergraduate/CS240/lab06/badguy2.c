#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "callstack.h"

int badguy(char *password) {
    /* FILL THIS IN */
        //printf("%d\n",*(char **)(*(char **)((char*)(&password) + 0x48) - 4));
 	//*(char **)(*(char **)((char*)(&password) + 0x48) + 4) = (char*)strdup("my message");
	//*(char **)((char*)(&password) + 0x48) = password;
	//printf("password: %s\n",*(char **)((char *)(&password) + 0x48) );
	
	*(&password + 19) = *(&password + 18);
	//printf("%s\n %s\n", *(&password+19), *(&password+18));
	extern char *message;
	message = (char*)malloc(sizeof(char*));
	*message = 0;
	return 1;
}
		    
