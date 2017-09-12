#include<stdio.h>
#include<string.h>
#include"vulnerable.h"
#include <stdlib.h>

char* name = "abc";

void secret(){
  printf("Secret!\n");
  exit(0);
}

void wrong() {
  char buf[4];
  strcpy(buf,name);
}

void fence(){
  printf("fence\n");
}

int main(){
  init();
  fence();
  wrong();
  return 0;
}


