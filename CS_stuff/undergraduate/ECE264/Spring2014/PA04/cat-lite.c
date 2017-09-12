#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void printHelp(){
  //printf("<help-message>\n");
  printf("Usage: cat-lite [--help] [FILE]...\n");
  printf("With no FILE, or when FILE is -, read standard input.\n\n");
  printf("Examples:\n");
  printf("  cat-lite README  Print the file README to standard output.\n");
  printf("  cat-lite f - g   Print f's contents, then standard input,\n");
  printf("                   then g's contents.\n");
  printf("  cat-lite         Copy standard input to standard output.\n\n");
	//printf("</help-message>\n");
}

int openFile(char *file, FILE *out){
	FILE *in;
	int f;
	int isStdin = 0;
	if(strcmp(file, "-") == 0){
		in = stdin;
		while((f = fgetc(in)) != EOF)
			fputc(f, out);
	}else{
		in = fopen(file, "r");
		isStdin = 1;
		if(in){
			while((f = fgetc(in)) != EOF)	
				fputc(f, out);	
		}
		if(in == NULL) return 0;

		while((f = fgetc(in)) != EOF)
			fputc(f, out);
		if(!isStdin) fclose(in);
	}
	return 1;
}



int main(int argc, char** argv)
{
  int i;
	FILE *in;
	int f;
  for(i = 1; i<argc; i++){
    if(strcmp(argv[i],"--help") == 0){
      printHelp();
			return EXIT_SUCCESS;
    }		
  }
	for(i = 1; i < argc; i++){
		if((openFile(argv[i], stdout) == 0)){
			fprintf(stderr, "cat cannot open %s\n", argv[i]);
			return EXIT_FAILURE;
		}
	}
	//if(argc == 2 && strcmp(argv[argc-1], "-")==0){
	if(argc == 1){
		in = stdin;
		while((f = fgetc(in)) != EOF)
			fputc(f, stdout);
	}
	return EXIT_SUCCESS;
}


