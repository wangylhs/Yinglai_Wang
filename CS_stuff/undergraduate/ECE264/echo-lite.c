#include <stdlib.h>
#include <stdio.h>


int main(int argc, char ** argv){
    int i=1;
    while(argc!=1 && i<argc && (int)argv[i]!=' '){
        printf("%s ", argv[i]);
        i++;
    }
    printf("\n");
    return EXIT_SUCCESS;
}