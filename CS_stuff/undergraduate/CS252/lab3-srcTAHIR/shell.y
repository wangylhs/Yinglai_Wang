
/*
 * CS-413 Spring 98
 * shell.y: parser for shell
 *
 * This parser compiles the following grammar:
 *
 *	cmd [arg]* [> filename]
 *
 * you must extend it to understand the complete shell grammar
 *
 */

%token	<string_val> WORD

%token 	NOTOKEN, GREAT, NEWLINE, LESS, PIPE, BACKGROUND, APPEND, REDIRECT, APPEND_REDIRECT

%union	{
		char   *string_val;
	}

%{
extern "C" int yylex();
#define yylex yylex
#define MAXFILENAME 1024
#include <stdio.h>
#include "command.h"
#include <unistd.h>
#include <regexpr.h>
#include <dirent.h>
int x;
%}

%%

goal:
	commands
	;

commands:
	command
	| commands command
	;

command: simple_command
        ;

simple_command:
	pipe_list iomodifier_list background_opt NEWLINE {
		//printf("   Yacc: Execute command\n");
		Command::_currentCommand.execute();
	}
	| NEWLINE
	| error NEWLINE { yyerrok; }
	;

command_and_args:
	command_word arg_list {
		Command::_currentCommand.
			insertSimpleCommand( Command::_currentSimpleCommand );
	}
	;

arg_list:
	arg_list argument
	| /* can be empty */
	;

argument:
	WORD {
              // printf("   Yacc: insert argument \"%s\"\n", $1);
			x = 0;
			expandwild((char *) "\0", $1);
			if (!x)
				Command::_currentSimpleCommand->insertArgument( $1 );
	}
	;

command_word:
	WORD {
               //printf("   Yacc: insert command \"%s\"\n", $1);

	       Command::_currentSimpleCommand = new SimpleCommand();
	       Command::_currentSimpleCommand->insertArgument( $1 );
	}
	;

pipe_list:
	pipe_list PIPE command_and_args
	| command_and_args
	;

iomodifier_list:
	iomodifier_list iomodifier_opt
	|
	;

iomodifier_opt:
	GREAT WORD {
		//printf("   Yacc: insert output \"%s\"\n", $2);
		Command::_currentCommand._outFile = $2;
		Command::_currentCommand._out++;
	}
	| /* can be empty */

	APPEND WORD {
		//printf("   Yacc: append output \"%s\"\n", $2);
		Command::_currentCommand._outFile = $2;
		Command::_currentCommand._append = 1;
		Command::_currentCommand._out++;
	}
	|

	REDIRECT WORD {
		//printf("   Yacc: redirect output \"%s\"\n", $2);
		Command::_currentCommand._outFile = $2;
		Command::_currentCommand._errFile = $2;
		Command::_currentCommand._out++;
	}
	|

	LESS WORD {
		//printf("   Yacc: insert input \"%s\"\n", $2);
		Command::_currentCommand._inputFile = $2;
		Command::_currentCommand._in++;
	}
	|

	APPEND_REDIRECT WORD {
		//printf("   Yacc: redirect stderr output \"%s\"\n", $2);
		Command::_currentCommand._outFile = $2;
		Command::_currentCommand._errFile = $2;
		Command::_currentCommand._append = 1;
		Command::_currentCommand._out++;
	}
	;

background_opt:
	BACKGROUND {
		//printf("Command running in background");
		Command::_currentCommand._background = 1;
	}
	|
	;

%%

int
compare(const void *a, const void *b){
	const char ** s1 = (const char**)a;
	const char ** s2 = (const char**)b;
	return strcmp(*s1,*s2);
}

void
expandwild(char *prefix, char *suffix){
	if (suffix[0]==0) {
	// suffix is empty. Put prefix in argument.
		x++;
		Command::_currentSimpleCommand->insertArgument(strdup(prefix+1));
		qsort(Command::_currentSimpleCommand->_arguments+1, Command::_currentSimpleCommand->_numberOfArguments-1, sizeof(char*), compare);
		return;
	}
	// Obtain the next component in the suffix
	// Also advance suffix.
	char * s = strchr(suffix, '/');
	char *component = (char*)calloc(MAXFILENAME, sizeof(char));
	if (s!=NULL){ // Copy up to the first "/"
		strncpy(component,suffix, s-suffix);
		suffix = s + 1;
	}
	else { // Last part of path. Copy whole thing.
		strcpy(component, suffix);
		suffix = suffix + strlen(suffix);
	}
	// Now we need to expand the component
	char *newPrefix = (char*)calloc(MAXFILENAME, sizeof(char));
	
	if (strchr(component,'*')==NULL && strchr(component,'?')==NULL) {
		// component does not have wildcards
		sprintf(newPrefix,"%s/%s", prefix, component);
		expandwild(newPrefix, suffix);
		return;
	}
	// Component has wildcards
	// Convert component to regular expression
	char * reg = (char*)malloc(2*strlen(component)+10);
	char * a = component;
	char * r = reg;
	*r = '^';
	r++; // match beginning of line
	while (*a) {
		if (*a == '*') { *r='.'; r++; *r='*'; r++; }
		else if (*a == '?') { *r='.'; r++;}
		else if (*a == '.') { *r='\\'; r++; *r='.'; r++;}
		else { *r=*a; r++;}
		a++;
	}
	*r='$';
	r++;
	*r=0;// match end of line and add null char
	char * expbuf = compile(reg, 0, 0);
	if (expbuf==NULL) {
		perror("compile");
		return;
	}
	char * dir;
	// If prefix is empty then list current directory
	if (prefix[0]=='\0' )
		dir = (char *) "."; 
	else
		dir=prefix;
	DIR * d = opendir(dir);
	if (d==NULL)
		return;
	// Now we need to check what entries match
	struct dirent *ent;
	while ((ent = readdir(d))!= NULL) {
		// Check if name matches
		if (advance(ent->d_name, expbuf) ) {
			// Entry matches. Add name of entry
			// that matches to the prefix and
			// call expandWildcard(..) recursively
			if(ent->d_name[0]!='.'){
				sprintf(newPrefix,"%s/%s", prefix, ent->d_name);
				expandwild(newPrefix,suffix);
			}
			else if(ent->d_name[0]=='.' && component[0]=='.'){
				sprintf(newPrefix,"%s/%s", prefix, ent->d_name);
				expandwild(newPrefix,suffix);
			}
		}
	}
	closedir(d);
}

void
yyerror(const char * s)
{
	fprintf(stderr,"%s", s);
}

#if 0
main()
{
	yyparse();
}
#endif
