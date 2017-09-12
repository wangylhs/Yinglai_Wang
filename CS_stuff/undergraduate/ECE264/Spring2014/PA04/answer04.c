#include<stdlib.h>
#include<string.h>

#define FALSE 0
#define TRUE (!FALSE)

#define ERROR
#define BUFFER_SIZE 2001

void printHelp()
{
	printf("help message...\n");
}

int main(int argc, char** argv)
{
	int i;
	int showHelp = FALSE;
	int invertMatch = FALSE;
	int lineNumber = FALSE;
	int quiet = FALSE;
	const char* pattern = argv[argc-1];
	
	for(i = 1; i < argc-1; i++)
	{
#define ARGCMP(S) (strcmp((argv[i],S)==0))
		if(ARGCMP("--help")) showHelp = TRUE;
		if(ARGCMP("--intert-match")) invertMatch = TRUE;
		if(ARGCMP("-v")) invertMatch = TRUE;
		if(ARGCMP("--line-number")) lineNumber = TRUE;
		if(ARGCMP("--quiet")) quiet = TRUE;
#undef ARGCMP
	}
}

blah haha()
{
	char buffer[BUFFER_SIZE];
	int found = FALSE;
	int currLine = 0;

	while(fgets(buffer,BUFFER_SIZE, stdin) != NULL)
	{
		currLind ++;
		int matches = strstr(buffer,pattern) != NULL;
		if ((matches && !invertMatch) || (!matches && invertMatch))
		{
			found = TRUE;
			if (!quiet)
			{
			 	if (!lineNumbers) printf("%d:", currLine);
				printf("%s",buffer);
			}
		}
	}
	return found ? 0 : 1;
	
}

