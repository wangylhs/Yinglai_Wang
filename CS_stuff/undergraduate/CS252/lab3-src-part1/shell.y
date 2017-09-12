
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
#include "command.h"
void yyerror(const char * s);
int yylex();

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
		printf("   Yacc: Execute command\n");
		Command::_currentCommand.execute();
	}
	| NEWLINE 
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
               printf("   Yacc: insert argument \"%s\"\n", $1);

	       Command::_currentSimpleCommand->insertArgument( $1 );\
	}
	;

command_word:
	WORD {
               printf("   Yacc: insert command \"%s\"\n", $1);
	       
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
    printf("   Yacc: append output \"%s\"\n", $2);
    Command::_currentCommand._outFile = $2;
    }
    | GREAT WORD {
    printf("   Yacc: insert output \"%s\"\n", $2);
    Command::_currentCommand._outFile = $2;
    }
    | GREATGREATAMPERSAND WORD {
    printf("   Yacc: append output and error \"%s\"\n", $2);
    Command::_currentCommand._outFile = $2;
    Command::_currentCommand._errFile = $2;
    }
    | GREATAMPERSAND WORD {
    printf("   Yacc: insert output and error \"%s\"\n", $2);
    Command::_currentCommand._errFile = $2;
    Command::_currentCommand._outFile = $2;
    }
    | LESS WORD {
    printf("   Yacc: take input \"%s\"\n", $2);
    Command::_currentCommand._inputFile = $2;
    }
	;

background_optional:
    AMPERSAND {
        printf("    Yacc: keep the terminal live \n");
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

#if 0
main()
{
	yyparse();
}
#endif
