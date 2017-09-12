
/*
 * CS-252 Spring 2013
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

%token 	NOTOKEN GREAT NEWLINE GREATGREAT GREATAMPERSAND GREATGREATAMPERSAND LESS PIPE AMPERSAND

%union	{
		char   *string_val;
	}

%{
//#define yylex yylex
#include <stdio.h>
#include <fcntl.h>
#include "command.h"
#include<unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <dirent.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXFILENAME 1024
void yyerror(const char * s);
int yylex();
void expandWildcard(char*, char*, const char*);
int cmpfunc(const void *, const void *);
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
	pipe_list io_modifier_list background_optional NEWLINE {
		////printf("   Yacc: Execute command\n");
		Command::_currentCommand.execute();
	}
	| NEWLINE {
		Command::_currentCommand.prompt();
	}
	| error NEWLINE { yyerrok; }
	;

pipe_list:
    pipe_list PIPE command_and_args
    | command_and_args
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
               //printf("   Yacc: insert argument \"%s\"\n", $1);
    if ($1!=NULL) {
        int i;
		for(i=0; $1[i]; i++) {
			if ($1[i]=='?' || $1[i]=='*') {
				break;
			}
		}
		
		if ($1[i])  {
			char suffix[1024];
			int start = Command::_currentSimpleCommand->_numberOfArguments;
			suffix[0] = 0;
			
			expandWildcard(suffix, suffix, $1);
			int end = Command::_currentSimpleCommand->_numberOfArguments;
			//printf("s: %d  e: %d\n", start, end);
			//printf("name: %s\n", (Command::_currentSimpleCommand->_arguments + start - 1)[0]);
			qsort(Command::_currentSimpleCommand->_arguments + start, end - start, sizeof(char*), cmpfunc);
		} else if ($1) {
        	Command::_currentSimpleCommand->insertArgument( $1 );
		}
    }
        
	}
	;

command_word:
	WORD {
               //printf("   Yacc: insert command \"%s\"\n", $1);
	       
	       Command::_currentSimpleCommand = new SimpleCommand();
	       Command::_currentSimpleCommand->insertArgument( $1 );
	}
	;
io_modifier_list:
	io_modifier_list io_modifier
	| /*empty*/
	;

io_modifier:
   GREATGREAT WORD {
   		//printf("   Yacc: append output \"%s\"\n", $2);
       Command::_currentCommand._outNum++;
       Command::_currentCommand._outFile = open($2, O_CREAT|O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		free($2);
	}
    | GREAT WORD {
        //printf("   Yacc: overwrite output \"%s\"\n", $2);
        Command::_currentCommand._outNum++;
        Command::_currentCommand._outFile = open($2, O_CREAT|O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		free($2);
    }
    | GREATGREATAMPERSAND WORD {
        //printf("   Yacc: append output and error \"%s\"\n", $2);
        Command::_currentCommand._outNum++;
        Command::_currentCommand._outFile = open($2, O_CREAT|O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        Command::_currentCommand._errFile = Command::_currentCommand._outFile;
		free($2);
    }
    | GREATAMPERSAND WORD {
        //printf("   Yacc: overwrite output and error \"%s\"\n", $2);
        Command::_currentCommand._errFile = open($2, O_CREAT|O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        Command::_currentCommand._outNum++;
        Command::_currentCommand._outFile = Command::_currentCommand._errFile;
		free($2);
    }
    | LESS WORD {
        //printf("   Yacc: take input \"%s\"\n", $2);
        Command::_currentCommand._inputFile = open($2, O_RDONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		free($2);
    }
	;

background_optional:
    AMPERSAND {
        //printf("    Yacc: keep the terminal live \n");
        Command::_currentCommand._background = 1;
    }
	| /*empty*/
	;

%%
int cmpfunc(const void *a, const void *b)
{
	return strcmp(*(const char**)a, *(const char**)b);
}

void expandWildcard(char *prefix, char *mid, const char *suffix)
{	
	DIR *d;
	if (*prefix) {
		d = opendir(prefix);
	} else if (suffix[0] == '/') {
		d = opendir("/");
		mid = mycpy(prefix, "/");
		suffix++;
	} else {
		d = opendir(".");
	}
	if(d==NULL) return;
    
	char exp[1024], *p = exp;
    const char *com = suffix;
    *p++ = '^';
    do {
        switch(*com) {
            case '*':
            	*p++ = '.'; *p++ = '*'; break;
            case '?':
            	*p++ = '.'; break;
            case '.':
            	*p++ = '\\'; *p++ = '.'; break;
            default:
            	*p++ = *com;
            break;
        }
        com++;
    } while(*com && *com!='/');
    *p++ = '$'; *p = '\0';
	
    regex_t preg;
	regmatch_t pmatch[1];
    if (regcomp(&preg, exp, REG_EXTENDED | REG_NOSUB)) {
        perror("Compile Exp Failed!");
        return ;
    }

    struct dirent64 *ent;
    
    // Now we need to check what entries match
    while ((ent = readdir64(d))!= NULL) {
        // Check if name matches
        if (!regexec(&preg, ent->d_name, 1, pmatch, 0)) {
            if(ent->d_name[0] != '.' || suffix[0] == '.') {
				char *newMid = mycpy(mid, ent->d_name);
				if (com[0]) {
					newMid = mycpy(newMid, "/");
				}
				if (com[0] && com[1]) {
					expandWildcard(prefix, newMid, com + 1);
				} else {
					Command::_currentSimpleCommand->insertArgument(prefix);
				}
				*mid = '\0';
            }
        }
    }
	regfree(&preg);
    closedir(d);
}


void yyerror(const char * s)
{
	fprintf(stderr,"%s", s);
}

#if 0
main()
{
	yyparse();
}
#endif
