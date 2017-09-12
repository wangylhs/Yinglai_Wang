
/*
 *
 * CS-413 Spring 98
 * shell.l: lexical analyzer for shell
 * You have to extend it.
 *
 */

%{

#include <string.h>
#include "y.tab.h"

	char* tilda(char*);
	char* escapeChar(char*); 
	char* variableExp(char*);
	char * read_line();

	int mygetc(FILE * f) {
		static char *p;
		char ch;

		if (!isatty(0)) {
			//stdin is not a tty. Call real getc
			return getc(f);
		}

		//stdin is a tty. Call our read_line.

		if (p==NULL || *p == 0) {
			char * s = read_line();
			p = s;
		}

		ch = *p;
		p++;

		return ch;
	}

#undef getc
#define getc(f) mygetc(f)

%}

%%

\".*\" {
	char * temp;
	while((temp = strchr(yytext,'\"'))!=NULL){
		strcpy(temp, temp+1);
	}
	yylval.string_val = strdup(yytext);
	return WORD;
}

\n 	{
	return NEWLINE;
}

[ \t] 	{
	/* Discard spaces and tabs */
}	

">" 	{
	return GREAT;
}

"<"		{
	return LESS;
}

"|"		{
	return PIPE;
}

"&"		{
	return BACKGROUND;
}

">>"	{
	return APPEND;
}

">&"	{
	return REDIRECT;
}

">>&"	{
	return APPEND_REDIRECT;
}

"exit"	{
	exit(0);
}

([^ \t\n&<>\|]*(\\.)*)* {
	/* Assume that file names have only alpha chars */
	char *temp = strdup(yytext);
	temp = tilda(temp);
	temp = escapeChar(temp);
	temp = variableExp(temp);
	yylval.string_val = strdup(temp);
	return WORD;
}

.	{
	/* Invalid character in input */
	return NOTOKEN;
}

%%

char* tilda(char *str){
	char *t = strchr(str, '~');
	if(t!=0){
		char *env = strdup(getenv("HOME"));

		if(*(t+1)=='\0' || *(t+1)=='/'){
			*t=0;
			char *path = (char*)malloc(sizeof(char)*strlen(env)+strlen(t+1));
			strcpy(path, env);
			strcat(path, t+1);
			free(str);
			return strdup(path);
		}else{
			*t=0;
			char *home = strrchr(env,'/');
			*(home+1) = '\0';
			char *path = (char*)malloc(sizeof(char)*strlen(env)+strlen(t+1));
			strcpy(path, env);
			strcat(path,t+1);
			free(str);
			return strdup(path);
		}
	}
	return strdup(str);
}

char* escapeChar(char *str){
	int len = strlen(str);
	int i;
	for(i=0; i<len; i++){
		if(str[i]=='\\'){
			if(str[i+1]=='\\'){
				i++;
				continue;
			}
			strcpy(str+i, str+i+1);
			len--;
		}
	}

	str[len] = '\0';
	return strdup(str);
}

char* variableExp(char *str){
	char * start = strchr(str,'$');
	char * end = strchr(str,'}');

	if(start==NULL || end==NULL)
		return strdup(str);

	*start = '\0';
	*end = '\0';

	char * env = getenv(start+2);
	char * temp = (char *)malloc(sizeof(char)*(strlen(env)+strlen(str)+strlen(end+1)));

	strcpy(temp,str);
	strcat(temp,env);
	strcat(temp,end+1);

	temp = variableExp(temp);
	return strdup(temp);
}


