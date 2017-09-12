
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
#include <fcntl.h>
#include "command.h"
char *shell;
extern char **environ;
Command Command::_currentCommand;
SimpleCommand * Command::_currentSimpleCommand;
int yyparse(void);


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
	//expand out the arguement if needed
	int inExpression = 0;
	int totalCounter = 0;
	int changesMade = 0;
	char *str = strdup(argument);
	char *totalString = (char *) calloc((sizeof(char)*512)+1, sizeof(char));
	//check for tilde expansion
	if (argument[0] == '~') {
	  changesMade = 1;
	  if (strlen(argument) == 1) {
	    //expand to home dir
	    strcat(totalString, getenv("HOME"));
	  }else {
	   //longer than one
	   strcat(totalString, "/homes/");
	   strcat(totalString, argument + 1);
	  }
	}else {
	for (int i = 0; *(str + i) != '\0'; i++) {
	    if (str[i] == '$') {
	      changesMade = 1;
	      inExpression = 1;
	      i+=2;
	      int counter=  0;
	      while (*(str+i++) != '}') {
		counter++;
	      }
	      i--;
	      inExpression = 0;
	      char *enviormentVar = (char *) calloc((sizeof(char)*counter)+1,sizeof(char));
	      strncpy(enviormentVar, &str[i-counter], counter);
	      free(str);
	      char *value = getenv(enviormentVar);
	      int strLen = strlen(value);
	      strncpy(totalString + totalCounter, value, strLen);
	      totalCounter+=strLen;
	    }else if (!inExpression) {
	      if (str[i] != '\\') totalString[totalCounter++] = str[i];
	    }
	}
      }
	if (changesMade) {
	  _arguments[ _numberOfArguments ] = totalString;
	}else {
	_arguments[ _numberOfArguments ] = argument;
	}
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
    _inputFileCount = 0;
    _outputFileCount = 0;
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
    _inputFileCount = 0;
    _outputFileCount = 0;
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
	printf( "  Output       Input        Error        Background        Append\n" );
	printf( "  ------------ ------------ ------------ ------------ ------------\n" );
	printf( "  %-12s %-12s %-12s %-12s %-12s\n", _outFile?_outFile:"default",
           _inputFile?_inputFile:"default", _errFile?_errFile:"default",
           _background?"YES":"NO",_append?"YES":"NO");
	printf( "\n\n" );
	
}

void interrupt_handler(int sig) {
    printf("\n");
    Command::_currentCommand.prompt();
}
void
Command::execute()
{
    //check if exit

    
    //declare vars
    pid_t pid = 0;
    int tempInput = dup(0);
    int tempOutput = dup(1);
    int tempError = dup(2);
    int inputFileDescriptor = 0;
    int outputFileDescriptor = 0;
    int errorFileDescriptor = 0;
    int tempDescriptor = 0;
    int internalCommand = 0;
	// Don't do anything if there are no simple commands
	if ( _numberOfSimpleCommands == 0 ) {
		prompt();
		return;
	}else {
        if (strcmp(_simpleCommands[0]->_arguments[0], "exit") == 0) {
            printf("\nGood bye!!!\n");
            exit(1);
        }else if(strcmp("cd",_simpleCommands[0]->_arguments[0]) == 0) {
            if (_simpleCommands[0]->_arguments[1]) {
                if (chdir(_simpleCommands[0]->_arguments[1]) < 0) {
                    fprintf(stderr, "cd: No such file or directory\n");
                }
            }else {
                //home
                chdir(getenv("HOME"));
            }
            clear();
            prompt();
            return;
        }
    }

	// Print contents of Command data structure
	//print();
    
    //redirect input
    if (_inputFile) {
        inputFileDescriptor = open(_inputFile, O_RDONLY);
        if (inputFileDescriptor == -1) {
	    perror("The input file specified is invald.\n");
	    clear();
	    prompt();
	    return;
	}
    }else {
        inputFileDescriptor = dup(tempInput);
    }
    //redirect error
    if (_errFile) {
        if (_append == 0) {
            errorFileDescriptor = open(_errFile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
        }else if(_append == 1) {
            errorFileDescriptor = open(_errFile, O_WRONLY | O_CREAT | O_APPEND, 0777);
        }
        
        if (errorFileDescriptor == 1) {
            perror("Error creating file for error.");
            _exit(1);
        }
    }else {
        errorFileDescriptor = dup(tempError);
    }

    //redirect error
	dup2(errorFileDescriptor, 2);
	close(errorFileDescriptor);
    
    
    //check for ambiguous redirection
    if (_inputFileCount > 1) {
        printf("Ambiguous input redirect\n");
        return;
    }else if(_outputFileCount > 1) {
        printf("Ambiguous output redirect\n");
        return;
    }

    
    for (int i = 0; i < _numberOfSimpleCommands; i++) {
        internalCommand = 0;
        // For every simple command fork a new process
        dup2(inputFileDescriptor, 0);
        close(inputFileDescriptor);
        
        
        if (i == _numberOfSimpleCommands - 1) {
            //set output file
            //last command
            //redirect error and output
            if (_errFile == _outFile) {
                //same file
                if (_errFile && _outFile) {
                    outputFileDescriptor = dup(errorFileDescriptor);
                }else {//null
                    outputFileDescriptor = dup(tempOutput);
                }
                
            }else {//not the same file
                if (_outFile) {
                    if (_append == 0) {
                        outputFileDescriptor = open(_outFile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
                    }else if(_append == 1) {
                        outputFileDescriptor = open(_outFile, O_WRONLY | O_CREAT | O_APPEND, 0777);
                    }
                    if (outputFileDescriptor == 1) {
                        perror("Error creating file for output.");
                        _exit(2);
                    }
                }else if (!_outFile) {
                    outputFileDescriptor = dup(tempOutput);
                }
            
            }
        }else {
            //in the middle of command
           //create pipe
            int fdpipe[2];
            pipe(fdpipe);
            outputFileDescriptor = fdpipe[0];
            inputFileDescriptor = fdpipe[1];
        }
        
        //redirect output
        dup2(outputFileDescriptor, 1);
        close(outputFileDescriptor);
        if (strcmp(_simpleCommands[i]->_arguments[0], "setenv") == 0) {
            setenv(_simpleCommands[i]->_arguments[1], _simpleCommands[i]->_arguments[2], 1);
            continue;
        }else if (strcmp(_simpleCommands[i]->_arguments[0], "unsetenv") == 0) {
            unsetenv(_simpleCommands[i]->_arguments[1]);
            continue;
        }
        pid = fork();
        
        if (pid == 0) {
            //child
            //check built in commands
            if (strcmp(_simpleCommands[i]->_arguments[0], "printenv") == 0) {
                char **p = environ;
                for (; *p != NULL;) {
                    printf("%s\n", *p++);
                }
                exit(0);
            }else {
            execvp(_simpleCommands[i]->_arguments[0], _simpleCommands[i]->_arguments);
            perror("This is not a valid program.");//, _simpleCommands[i]->_arguments[0]);
            _exit(1);
        }
        }
        // Setup i/o redirection
        // and call exec
       }
    
    dup2(tempInput, 0);
    dup2(tempOutput, 1);
    dup2(tempError, 2);
    close(tempInput);
    close(tempOutput);
    close(tempError);
	// Clear to prepare for next command
        if (_currentCommand._background == 0) {
                //printf("waiting for background\n");
                waitpid(pid, NULL, 0);
    }
    
	clear();
	// Print new prompt
	prompt();
    return;

}


// Shell implementation

void
Command::prompt()
{
	if(isatty(0)) printf("myshell>");
	fflush(stdout);
}

void childHandler(int sig) {
 pid_t pid;
 int status = 0;
 pid = wait3(&status, WNOHANG, NULL);
 //if (pid != 0) printf("[%d] exited.\n", pid);
}
main(int argc, char *argv[])
{
    //set signal
    shell = argv[0];
    sigset(SIGCHLD, childHandler);
    sigignore(SIGINT);
	Command::_currentCommand.prompt();
	yyparse();
}

