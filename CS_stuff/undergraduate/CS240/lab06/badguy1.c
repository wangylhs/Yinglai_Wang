#include <stdio.h>
#include "callstack.h"

int badguy(char *password) {
    /* FILL THIS IN */
	int i=19;
	while(i>=-2){
		printf("%p: %x\n", (&password+i), (unsigned int)*(&password+i));
		i--;
	}	
	return 0;
}
