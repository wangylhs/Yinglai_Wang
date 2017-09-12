
/*
 * CS252: Shell project
 *
 * Template file.
 * You will need to add more code here to execute the command table.
 *
 * NOTE: You are responsible for fixing any bugs this code may have!
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include "command.h"
char* shell;
void printHistory();

extern "C" void intHandler( int sig )
{
	int status = 0;
    wait3(&status, WNOHANG, NULL);
}

char shellPath[1024];

SimpleCommand::SimpleCommand()
{
	// Creat available space for 5 arguments
	_numberOfAvailableArguments = 5;
	_numberOfArguments = 0;
	_arguments = (char **) malloc( (_numberOfAvailableArguments + 1) * sizeof( char * ) );
}

char *mycpy(char *d, const char *s)
{
    while(*d++ = *s++);
    return d - 1;
}

void
SimpleCommand::insertArgument( char * argument )
{
	if ( _numberOfAvailableArguments == _numberOfArguments + 1) {
		// Double the available space
		_numberOfAvailableArguments *= 2;
		_arguments = (char **) realloc( _arguments,
				  (_numberOfAvailableArguments + 1 )* sizeof( char * ) );
	}
	
    char *final = (char*)malloc(1024);
    _arguments[ _numberOfArguments ] = final;
    
    if (argument[0] == '~') {
		if (argument[1] == '/' || argument[1] == '\0') {
			final = mycpy(final, getenv("HOME"));
		} else {
			final = mycpy(final, "/homes/");
		}
		argument++;
    }
    while(*argument) {
        if (*argument == '$' && argument[1] == '{') {
            char *p = argument + 2;
            while(*p && *p != '}') {
                p++;
            }
            *p = '\0';
            final = mycpy(final, getenv(argument + 2));
            argument = p + 1;
        } else if (*argument == '\\') {
            *final++ = *++argument;
            argument++;
        } else {
            *final++ = *argument++;
        }
    }
    *final = '\0';

	// Add NULL argument at the end
	
	_arguments[ _numberOfArguments + 1] = NULL;
	
	_numberOfArguments++;
}

Command::Command()
{
	// Create available space for one simple command
	_numberOfAvailableSimpleCommands = 1;
	_simpleCommands = (SimpleCommand **)
		malloc( _numberOfSimpleCommands * sizeof( SimpleCommand * ) );

	_numberOfSimpleCommands = 0;
	_inputFile = 0;
    _outNum = 0;
	_outFile = 1;
	_errFile = 2;
	_background = 0;
}

void
Command::insertSimpleCommand( SimpleCommand * simpleCommand )
{
	if ( _numberOfAvailableSimpleCommands == _numberOfSimpleCommands ) {
		_numberOfAvailableSimpleCommands *= 2;
		_simpleCommands = (SimpleCommand **) realloc( _simpleCommands,
			 _numberOfAvailableSimpleCommands * sizeof( SimpleCommand * ) );
	}
	
	_simpleCommands[ _numberOfSimpleCommands ] = simpleCommand;
	_numberOfSimpleCommands++;
}

void
Command:: clear()
{
	for ( int i = 0; i < _numberOfSimpleCommands; i++ ) {
		for ( int j = 0; j < _simpleCommands[ i ]->_numberOfArguments; j ++ ) {
			free ( _simpleCommands[ i ]->_arguments[ j ] );
		}
		
		free ( _simpleCommands[ i ]->_arguments );
		free ( _simpleCommands[ i ] );
	}

	_numberOfSimpleCommands = 0;
	_inputFile = 0;
    _outNum = 0;
    _outFile = 1;
	_errFile = 2;
	_background = 0;
}

void
Command::print()
{
	printf("\n\n");
	printf("              COMMAND TABLE                \n");
	printf("\n");
	printf("  #   Simple Commands\n");
	printf("  --- ----------------------------------------------------------\n");
	
	for ( int i = 0; i < _numberOfSimpleCommands; i++ ) {
		printf("\n  %-3d ", i );
		for ( int j = 0; j < _simpleCommands[i]->_numberOfArguments; j++ ) {
			printf("\"%s\" \t", _simpleCommands[i]->_arguments[ j ] );
		}
	}

	printf( "\n\n" );
	printf( "  Output       Input        Error        Background\n" );
	printf( "  ------------ ------------ ------------ ------------\n" );
	/*printf( "  %-12s %-12s %-12s %-12s\n", _outFile?_outFile:"default",
		_inputFile?_inputFile:"default", _errFile?_errFile:"default",
		_background?"YES":"NO");*/
	printf("in=%d out=%d err=%d\n", _inputFile, _outFile, _errFile);
	printf( "\n\n" );
	
}

void
Command::execute()
{
    
	// Don't do anything if there are no simple commands
	if (_outNum > 1) {
        fprintf(stderr,"Ambiguous output redirect\n");
        clear();
        prompt();
        return;
    }
    
    if (!strcmp(_simpleCommands[0]->_arguments[0], "exit")) {
        //if (isatty(0)) {
          //  printf("\n\nGood bye!\n\n");
        //}
        exit(0);
    }

	// Print contents of Command data structure
	//print();

	// Add execution here
	// For every simple command fork a new process
	// Setup i/o redirection
	// and call exec
    int oldIn = dup(0);
    int oldOut = dup(1);
    int oldErr = dup(2);
	if (_inputFile != 0) {
		dup2(_inputFile, 0);
	}
	if (_errFile != 2) {
		dup2(_errFile, 2);
	}
    int p[2];
	int ret;

	for(int i=0; i<_numberOfSimpleCommands; i++) {
        if (!strcmp(_simpleCommands[i]->_arguments[0], "setenv")) {
            setenv(_simpleCommands[i]->_arguments[1], _simpleCommands[i]->_arguments[2], 1);
            continue;
        } else if (!strcmp(_simpleCommands[i]->_arguments[0], "unsetenv")) {
            unsetenv(_simpleCommands[i]->_arguments[1]);
            continue;
        } else if(!strcmp(_simpleCommands[i]->_arguments[0], "history")){
            printHistory();
            continue;
        }else if (!strcmp(_simpleCommands[i]->_arguments[0], "cd")) {
            if (!_simpleCommands[0]->_arguments[1]) {
                chdir(getenv("HOME"));
            } else if (chdir(_simpleCommands[0]->_arguments[1]) < 0) {
                fprintf(stderr, "cd: %s: No such file or directory\n", _simpleCommands[i]->_arguments[1]);
            }
            continue;
        }
        
		pipe(p);
		if (i != _numberOfSimpleCommands - 1) {
			dup2(p[1], 1);
		} else {
			if (_outFile != 1) {
				dup2(_outFile, 1);
				close(_outFile);
			} else {
				dup2(oldOut, 1);
			}
		}
		close(p[1]);
        
		ret = fork();
		if (ret==0) {
			close(p[0]);
			close(oldIn); close(oldOut); close(oldErr);
            if (!strcmp(_simpleCommands[i]->_arguments[0], "printenv")) {
                char **p = environ;
                while(*p) {
                    printf("%s\n", *p++);
                }
            } else {
                execvp(_simpleCommands[i]->_arguments[0], _simpleCommands[i]->_arguments);
                perror("Execvp failed!");
            }
			exit(0);
		}
		dup2(p[0], 0);
		close(p[0]);
	}
	
	dup2(oldIn, 0);
	close(oldIn);
    if (_inputFile!=0) {
		close(_inputFile);
	}
	
    dup2(oldOut, 1);
	close(oldOut);
	if (_outFile!=1) {
    	close(_outFile);
	}
	
    dup2(oldErr, 2);
	close(oldErr);
	if (_errFile!=2) {
    	close(_errFile);
	}

	if (!_background) {
		waitpid(ret, 0, 0);
        //printf("Wait!\n");
    }

    // Clear to prepare for next command
    clear();
	
    // Print new prompt
    prompt();
}

// Shell implementation

void
Command::prompt()
{
	if (isatty(0)) {
        printf("myshell>");
    }
	fflush(stdout);
}

Command Command::_currentCommand;
SimpleCommand * Command::_currentSimpleCommand;

int yyparse(void);

int main(int argc, char **args)
{
    if (args[0][0]=='/') {
        mycpy(shellPath, args[0]);
    } else {
        char *p = mycpy(shellPath, getenv("PWD"));
        *p++ = '/';
        mycpy(p, args[0]);
    }
    shell = args[0];
    //sigignore(SIGINT);
    sigset( SIGCHLD, intHandler );
	Command::_currentCommand.prompt();
	yyparse();
}

