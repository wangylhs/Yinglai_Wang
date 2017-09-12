
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

%token 	NOTOKEN, GREAT, NEWLINE, AMPERSAND, GREATAMPERSAND, PIPE, LESS, GREATGREATAMPERSAND, GREATGREAT

%union	{
		char   *string_val;
	}

%{
extern "C" int yylex();
#define yylex yylex
#include <stdio.h>
#include "command.h"
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
               //printf("   Yacc: insert argument \"%s\"\n", $1);
	       Command::_currentSimpleCommand->insertArgument( $1 );\
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
    Command:_outputFileCount++;
    Command::_currentCommand._outFile = $2;
}
| GREATAMPERSAND WORD{
    //printf("   Yacc: insert output \"%s\"\n", $2);
    Command:_outputFileCount++;
    Command::_currentCommand._outFile = $2;
    Command::_currentCommand._errFile = $2;
}
| GREATGREAT WORD {
    //printf("   Yacc: insert output \"%s\"\n", $2);
    Command:_outputFileCount++;
    Command::_currentCommand._outFile = $2;
    Command::_currentCommand._append = 1;
}
| GREATGREATAMPERSAND WORD{
	//printf("   Yacc: insert output \"%s\"\n", $2);
    Command:_outputFileCount++;
    Command::_currentCommand._outFile = $2;
    Command::_currentCommand._errFile = $2;
    Command::_currentCommand._append = 1;
}
| LESS WORD {
    //printf("   Yacc: insert output \"%s\"\n", $2);
    Command:_inputFileCount++;
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

#if 0
main()
{
	yyparse();
}
#endif
