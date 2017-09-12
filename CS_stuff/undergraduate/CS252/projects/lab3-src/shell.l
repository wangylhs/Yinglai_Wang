
/*
 *
 * CS-252 Fall 2013
 * shell.l: lexical analyzer for shell
 * You have to extend it.
 *
 */

%{

	#include <string.h>
	#include <unistd.h>
	#include <stdio.h>
    #include <sys/wait.h>
	#include "y.tab.h"
    extern char *shell;
	char *read_line();
    char redirectBuf[4096] = {0};
    char *redirectPtr = redirectBuf;
    extern char *shellPath;
	int mygetc(FILE *fin) {
        static char *line = NULL;
        
        if (*redirectPtr) {
            return *redirectPtr++;
        }
        
		if (!isatty(0)) {
			return getc(fin);
		}
		
		if (!line || !*line) {
			line = read_line();
		}

		return *line++;
	}
	
	#undef getc
	#define getc(f) mygetc(f)
%}

%%

\n 	{
		return NEWLINE;
	}

[ \t] 	{
		/* Discard spaces and tabs */
     	}	

">" 	{
		return GREAT;
	}
">>"	{
		return GREATGREAT;
	}
"&"		{
		return AMPERSAND;
	}
"|"		{
		return PIPE;
	}
">>&"	{
		return GREATGREATAMPERSAND;
	}
">&"	{
		return GREATAMPERSAND;
	}
"<"		{
		return LESS;
	}

\"[^"]*\" {
        yylval.string_val = strdup(yytext + 1);
        yylval.string_val[yyleng-2] = 0;
        return WORD;
    }





([^ \t\n><\&\|]|\\.)+  {
		/* Assume that file names have only alpha chars */
		yylval.string_val = strdup(yytext);
		return WORD;
	}

.	{
		/* Invalid character in input */
		return NOTOKEN;
	}

%%

