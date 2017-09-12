#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

void help(){
    printf("Usage: cat-lite [--help] [FILE]...\n");
    printf("With no FILE, or when FILE is -, read standard input.\n\n");
    printf("Examples:\n");
    printf("  cat-lite README  Print the file README to standard output.\n");
    printf("  cat-lite f - g   Print f's contents, then standard input,\n");
    printf("                   then g's contents.\n");
    printf("  cat-lite         Copy standard input to standard output.\n\n");
}


int open(char *name, FILE *fp){
    FILE *fin;
    int f, isStdin;
    isStdin = 0;
    if(strcmp(name, "-")==0){
        fin = stdin;
        while ((f=fgetc(fin))!=EOF) {
            fputc(f, fp);
        }
    }else{
        fin = fopen(name, "r");
        isStdin = 1;
        if(fin){
            while ((f=fgetc(fin))!=EOF) {
                fputc(f, fp);
            }
        }
        if(fin==NULL) return FALSE;
        while((f=fgetc(fin))!=EOF){
            fputc(f, fp);
        }
        if(!isStdin){
            fclose(fin);
        }
    }
    return TRUE;
}

int main(int argc, char** argv){
    int i;
    FILE *fin;
    int f;
    if(argc==1) {
        fin = stdin;
        while ((f=getc(fin))!=EOF) {
            fputc(f, stdout);
        }
    }
    for (i=1; i<argc; i++) {
        if(strcmp(argv[i], "--help")==0){
            help();
            return EXIT_SUCCESS;
        }
        if(open(argv[i], stdout)==FALSE){
            fprintf(stderr,"cat cannot open %s\n", argv[i]);
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}








