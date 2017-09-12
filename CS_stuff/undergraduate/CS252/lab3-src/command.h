
#ifndef command_h
#define command_h
//extern char **environ;
// Command Data Structure

char *mycpy(char *, const char *);

struct SimpleCommand {
	// Available space for arguments currently preallocated
	int _numberOfAvailableArguments;

	// Number of arguments
	int _numberOfArguments;
	char ** _arguments;
	
	SimpleCommand();
	void insertArgument( char * argument );
};

struct Command {
	int _numberOfAvailableSimpleCommands;
	int _numberOfSimpleCommands;
	SimpleCommand ** _simpleCommands;
    int _outNum;
	int _outFile;
	int _inputFile;
	int _errFile;
	int _background;
	void prompt();
	void print();
    void addOutfile();
	void execute();
	void clear();
	
	Command();
	void insertSimpleCommand( SimpleCommand * simpleCommand );

	static Command _currentCommand;
	static SimpleCommand *_currentSimpleCommand;
};

#endif
