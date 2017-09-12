#include<stdlib.h>
#include<stdio.h>
#include<string.h>


void printHelp(){
  printf("Usage: grep-lite [OPTION]... PATTERN\nSearch for PATTERN in standard input. PATTERN is a\nstring. grep-lite will search standard input line by\nline, and (by default) print out those lines which\ncontain pattern as a substring.\n\n  -v, --invert-match     print non-matching lines\n  -n, --line-number      print line number with output\n  -q, --quiet            suppress all output\n\nExit status is 0 if any line is selected, 1 otherwise;\nif any error occurs, then the exit status is 2.\n\n");
}



int main(int argc, char** argv)
{
	int i;
	int showHelp = 0;
	int invertMatch = 0;
	int lineNumber = 0;
	int quiet = 0;
	char* pattern = argv[argc-1];	
	for(i = 1; i < argc-1; i++)
	{
#define ARGCMP(S) (strcmp(argv[i],S)==0)
		if(ARGCMP("--help")) showHelp = 1;
		else if(ARGCMP("--invert-match")) invertMatch = 1;
		else if(ARGCMP("-v")) invertMatch = 1;
		else if(ARGCMP("--line-number")) lineNumber = 1;
		else if(ARGCMP("-n")) lineNumber = 1;
		else if(ARGCMP("-q")) quiet = 1;
		else if(ARGCMP("--quiet")) quiet = 1;
		/*else{
			fprintf(stderr, "error!\n");
			return 0;		
		}*/
#undef ARGCMP
	}
	if(showHelp || strcmp(pattern, "--help") == 0){
		printHelp();
		return EXIT_SUCCESS;
	}
	if(argc == 1){
		fprintf(stderr, "error!\n");
		return 0;
	}		



	int BUFFER_SIZE = 2048;
	char buffer[BUFFER_SIZE];
	int found = 0;
	int currLine = 0;

	while(fgets(buffer,BUFFER_SIZE, stdin) != NULL)
	{
		currLine ++;
		int matches = (strstr(buffer,pattern) != NULL);
		if ((matches && !invertMatch) || (!matches && invertMatch))
		{
			found = 1;
			if (!quiet)
			{
			 	if (lineNumber) printf("%d:", currLine);
				printf("%s",buffer);
			}
		}
	}
	return found ? 0 : 1;



}
