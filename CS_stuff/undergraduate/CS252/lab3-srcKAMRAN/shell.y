
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

%token	<string_val> WORD, SHELLWORD

%token 	NOTOKEN, GREAT, NEWLINE, AMPERSAND, GREATAMPERSAND, PIPE, LESS, GREATGREATAMPERSAND, GREATGREAT

%union	{
		char   *string_val;
	}

%{
extern "C" int yylex();
void sortArrayStrings(char **, int);
#define yylex yylex
#include <stdio.h>
#include "command.h"
#include <string.h>
#include <dirent.h>
#include<unistd.h>
#include <sys/types.h>
#include <regexpr.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <pwd.h>
#define MAXFILENAME 1024
int maxEntries = 20;
int nEntries = 0;
int found = 0, wilds = 0;
char ** array;

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
	pipe_list io_modifier_list background_optional subshell NEWLINE {
		//printf("   Yacc: Execute command\n");
		Command::_currentCommand.execute();
	}
	| NEWLINE 
	| error NEWLINE { yyerrok; }
	;

subshell:
	SHELLWORD {
		Command::_currentCommand._subShellCommand = strdup($1);
	}
	|
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
	  char *arg = $1;
        char *temparg;
        
        if(strchr(arg,'\\')==NULL) {
            temparg=strdup(arg);
        }
        else {
            temparg = (char*)malloc(strlen(arg));
            int j=0;
            int k=0;
            while(arg[j]){
                if(arg[j] != '\\'){
                    temparg[k] = arg[j];
                    k++;
                }else if(arg[j] == '\\' && arg[j+1] == '\\'){
                    temparg[k] = '\\';
                    k++;
                    j++;
                }
                j++;
            }
        }
        
        expandWildcard(NULL,temparg);
        
        if(!found) {
            array[0] = strdup(temparg);
            nEntries++;
        }
        
        if(wilds) sortArrayStrings();
        
        for(int i=0;i<nEntries;i++) {
            Command::_currentSimpleCommand->insertArgument(strdup(array[i]));
        }
        free(array);
        nEntries=0;
        maxEntries=20;
        array=NULL;
        found = 0;
        wilds = 0;
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
io_modifier_list iomodifier_opt
| /*empty*/
;

iomodifier_opt:
GREAT WORD {
    //printf("   Yacc: insert output \"%s\"\n", $2);
    Command::_currentCommand._outputFileCount++;
    Command::_currentCommand._outFile = $2;
}
| GREATAMPERSAND WORD{
    //printf("   Yacc: insert output \"%s\"\n", $2);
    Command::_currentCommand._outputFileCount++;
    Command::_currentCommand._outFile = $2;
    Command::_currentCommand._errFile = $2;
}
| GREATGREAT WORD {
    //printf("   Yacc: insert output \"%s\"\n", $2);
    Command::_currentCommand._outputFileCount++;
    Command::_currentCommand._outFile = $2;
    Command::_currentCommand._append = 1;
}
| GREATGREATAMPERSAND WORD{
	//printf("   Yacc: insert output \"%s\"\n", $2);
    Command::_currentCommand._outputFileCount++;
    Command::_currentCommand._outFile = $2;
    Command::_currentCommand._errFile = $2;
    Command::_currentCommand._append = 1;
}
| LESS WORD {
    //printf("   Yacc: insert output \"%s\"\n", $2);
    Command::_currentCommand._inputFileCount++;
    Command::_currentCommand._inputFile = $2;
    
}
;


pipe_list:
pipe_list PIPE command_and_args
| command_and_args
;


background_optional:
AMPERSAND {
    //printf("   Yacc: Run in background\n");
    Command::_currentCommand._background = 1;
}
| /*empty*/
;
%%

void
yyerror(const char * s)
{
	fprintf(stderr,"%s", s);
}

void expandWildcard(char *prefix, char *suffix) {
    if(array==NULL) {
        array = (char**) malloc(maxEntries*sizeof(char*));
    }
    if(suffix[0] == 0) {
        //Suffix is empty, put prefix in argument
        found = 1;
        if(nEntries==maxEntries) {
            maxEntries*=2;
            array=(char**)realloc(array,maxEntries*sizeof(char*));
        }
        array[nEntries] = strdup(prefix);
        nEntries++;
        return;
    }
    
    if(strchr(suffix, '*') || strchr(suffix, '?'))
        wilds = 1;
    
    //Obtain the next component in suffix. also advance suffix
    char *s = strchr(suffix,'/');
    char component[MAXFILENAME];
    if(s!=NULL) {
        if(s-suffix!=0) {
            //Copy upto the first /
            strncpy(component,suffix, s-suffix);
            component[strlen(suffix)-strlen(s)]=0;
        }
        else {
            component[0]='\0';
        }
        suffix = s + 1;
    }
    else { // Last part of path. Copy whole thing.
        strcpy(component, suffix);
        suffix = suffix + strlen(suffix);
    }
    
    //printf("%s\n",component);
    //Now we need to expand the component
    char newPrefix[MAXFILENAME];
    
    //component doesnot have wildcards
    if(strchr(component,'*')==NULL && strchr(component,'?')==NULL) {
        if(prefix==NULL && component[0] != '\0')
            sprintf(newPrefix,"%s",component);
        else if(component[0]!='\0')
            sprintf(newPrefix,"%s/%s",prefix,component);
        
        if(component[0]!='\0')
            expandWildcard(newPrefix,suffix);
        else
            expandWildcard(strdup(""),suffix);
        return;
    }
    
    //Component has wildcards
    //Convert to regular expression
    char * reg = (char*)malloc(2*strlen(component)+10);
    char * a = component;
    char * r = reg;
    *r = '^'; r++; // match beginning of line
    while (*a) {
        if (*a == '*') { *r='.'; r++; *r='*'; r++; }
        else if (*a == '?') { *r='.'; r++;}
        else if (*a == '.') { *r='\\'; r++; *r='.'; r++;}
        else { *r=*a; r++;}
        a++;
    }
    *r='$'; r++; *r=0;
    
    //compile the regular expression
    char *expbuf = compile(reg,0,0);
    if(expbuf==NULL) {
        perror("compile");
        return;
    }
    
    char *dir;
    if(prefix==NULL) {
        dir=strdup(".");
    }
    else if(!strcmp("",prefix)) {
        dir = strdup("/");
    }
    else {
        dir = prefix;
    }
    
    DIR *d = opendir(dir);
    if(d==NULL) return;
    
     struct dirent64 *ent;
    
    // Now we need to check what entries match
    while ((ent = readdir64(d))!= NULL) {
        // Check if name matches
        if (advance(ent->d_name, expbuf) ) {
            // Entry matches. Add name of entry
            // that matches to the prefix and
            // call expandWildcard(..) recursively
            
            if(ent->d_name[0] == '.') {
                if(component[0] == '.') {
                    if(prefix == NULL) {
                        sprintf(newPrefix,"%s",ent->d_name);
                    }
                    else {
                        sprintf(newPrefix,"%s/%s",prefix,ent->d_name);
                    }
                    expandWildcard(newPrefix,suffix);
                }
            }
            else {
                if(prefix == NULL) {
                    sprintf(newPrefix,"%s",ent->d_name);
                }
                else {
                    sprintf(newPrefix,"%s/%s",prefix,ent->d_name);
                }
                expandWildcard(newPrefix,suffix);
            }
            
        }
    }
    closedir(d);
    return;
}


void sortArrayStrings(){
    int i = 0;
    for(; i < nEntries-1; i++){
        int j=0;
        for(; j<nEntries-1; j++){
            char* one = array[j];
            char* two = array[j+1];
            if(strcmp(one, two) > 0) {
                char* three = array[j];
                array[j] = two;
                array[j+1] = three;
            }
        }
    }
}

#if 0
main()
{
	yyparse();
}
#endif
