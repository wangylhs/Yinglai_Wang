
/*
 * CS354: Shell project
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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "command.h"

extern char ** environ;

SimpleCommand::SimpleCommand()
{
	// Creat available space for 5 arguments
	_numberOfAvailableArguments = 5;
	_numberOfArguments = 0;
	_arguments = (char **) malloc( _numberOfAvailableArguments * sizeof( char * ) );
}

	void
SimpleCommand::insertArgument( char * argument )
{
	if ( _numberOfAvailableArguments == _numberOfArguments  + 1 ) {
		// Double the available space
		_numberOfAvailableArguments *= 2;
		_arguments = (char **) realloc( _arguments,
				_numberOfAvailableArguments * sizeof( char * ) );
	}

	_arguments[ _numberOfArguments ] = argument;

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
	_outFile = 0;
	_inputFile = 0;
	_errFile = 0;
	_background = 0;
	_append = 0;
	_in = 0;
	_out = 0;
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

	if ( _outFile ) {
		free( _outFile );
	}

	if ( _inputFile ) {
		free( _inputFile );
	}

	if ( _errFile ) {
		free( _errFile );
	}

	_numberOfSimpleCommands = 0;
	_outFile = 0;
	_inputFile = 0;
	_errFile = 0;
	_background = 0;
	_append = 0;
	_in = 0;
	_out = 0;
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
		printf("  %-3d ", i );
		for ( int j = 0; j < _simpleCommands[i]->_numberOfArguments; j++ ) {
			printf("\"%s\" \t", _simpleCommands[i]->_arguments[ j ] );
		}
	}

	printf( "\n\n" );
	printf( "  Output       Input        Error        Background\n" );
	printf( "  ------------ ------------ ------------ ------------\n" );
	printf( "  %-12s %-12s %-12s %-12s\n", _outFile?_outFile:"default",
			_inputFile?_inputFile:"default", _errFile?_errFile:"default",
			_background?"YES":"NO");
	printf( "\n\n" );

}

	void
Command::execute()
{

	if(_in>1){
		printf("Ambiguous output redirect\n");
		clear();
		prompt();
		return;
	}

	if(_out>1){
		printf("Ambiguous output redirect\n");
		clear();
		prompt();
		return;
	}

	// Don't do anything if there are no simple commands
	if ( _numberOfSimpleCommands == 0 ) {
		prompt();
		return;
	}

	// Print contents of Command data structure
	//print();

	// Add execution here
	// For every simple command fork a new process
	// Setup i/o redirection
	// and call exec

	//save in/out
	int tmpin=dup(0);
	int tmpout=dup(1);
	int tmperr=dup(2);
	//set the initial input
	int fdin;
	if (_inputFile) {
		fdin = open(_inputFile, O_CREAT|O_RDONLY, 0664);
	}else {
		// Use default input
		fdin=dup(tmpin);
	}

	int ret;
	int fdout;
	int fderr;

	if(_errFile){
		if(_append){
			fdout=open(_errFile, O_CREAT|O_WRONLY|O_APPEND,0664);
			fderr=open(_errFile, O_CREAT|O_WRONLY|O_APPEND,0664);
		}else {
			fdout=open(_errFile, O_CREAT|O_WRONLY|O_TRUNC,0664);
			fderr=open(_errFile, O_CREAT|O_WRONLY|O_TRUNC,0664);
		}
	}else{
		fderr=dup(tmperr);
	}


	int i;
	for(i = 0; i < _numberOfSimpleCommands; i++) {
		//redirect input
		dup2(fdin, 0);
		//setup output
		if (i == _numberOfSimpleCommands-1){
			close(fdin);
			// Last simple command
			if(_outFile){
				if(_append)
				{
					fdout=open(_outFile, O_CREAT|O_WRONLY|O_APPEND,0664);
				}else{
					fdout=open(_outFile, O_CREAT|O_WRONLY|O_TRUNC,0664);
				}
			}
			else {
				// Use default output
				fdout=dup(tmpout);
			}
		}
		else {
			// Not last
			//simple command
			//create pipe
			int fdpipe[2];
			pipe(fdpipe);
			fdout=fdpipe[0];
			fdin=fdpipe[1];
		}// if/else
		// Redirect output
		dup2(fdout,1);
		close(fdout);
		dup2(fderr,2);
		close(fderr);
		// Create child process
		if(strcmp(_simpleCommands[i]->_arguments[0], "setenv")==0){
			setenv(_simpleCommands[i]->_arguments[1],_simpleCommands[i]->_arguments[2],1);
		}else if(strcmp(_simpleCommands[i]->_arguments[0], "unsetenv")==0){
			unsetenv(_simpleCommands[i]->_arguments[1]);
		}else if(strcmp(_simpleCommands[i]->_arguments[0],"cd")==0){
			if(_simpleCommands[i]->_arguments[1]==NULL){
				chdir(getenv("HOME"));
			}else{
				char *path = strdup(_simpleCommands[i]->_arguments[1]);
				int err = chdir(path);
				if(err==-1){
					perror(NULL);
				}
			}
		}

		else{
			ret=fork();
			if(ret==0) {
				if(strcmp(_simpleCommands[i]->_arguments[0],"printenv")==0){
					int j=0;
					while(environ[j]!=NULL){
						printf("%s\n", environ[j]);
						j++;
					}
					exit(0);
				}else{
					execvp(_simpleCommands[i]->_arguments[0], _simpleCommands[i]->_arguments);
					perror("execvp");
					exit(1);
				}
			}
		}
	} // for
	//restore in/out defaults
	dup2(tmpin,0);
	dup2(tmpout,1);
	dup2(tmperr,2);
	close(tmpin);
	close(tmpout);
	close(tmperr);
	if (!_background) {
		// Wait for last command
		waitpid(ret, NULL, NULL);
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
	if(isatty(0))
		printf("tshell>");
	fflush(stdout);
}

Command Command::_currentCommand;
SimpleCommand * Command::_currentSimpleCommand;

int yyparse(void);

void killZombie(int p){
	pid_t pid = wait3(0,0,NULL);
	while(waitpid(-1,NULL,WNOHANG)>0);
}


main()
{
	struct sigaction sig;
	sig.sa_handler = killZombie;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_RESTART;

	if(sigaction(SIGCHLD,&sig, NULL)){
		perror("SIG");
		exit(-1);
	}

	sigignore(SIGINT);
	Command::_currentCommand.prompt();
	yyparse();
}

