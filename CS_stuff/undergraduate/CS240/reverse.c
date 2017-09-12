#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* reverse_str(char* str){
	//add declarations here
	int length = 0;
	char a;
	int i;
	char *n = str;
	//implementation goes here
	while(*str!='\0'){
		str++;
		length++;
	}
	printf("%d\n",length);
	for(i=0; i<length/2; i++){
		a = n[i];
		n[i] = n[length-i-1];
		n[length-i-1] = a;
	}
	//return goes here
	return n;
	
}

int main(int argc, char *argv[]) {
	char *buff = (char*)malloc(sizeof(char)*10);
	char *b = reverse_str(gets(buff));
	while(*b!='\0'){
		printf("%c",*b);
		b++;
	}
}