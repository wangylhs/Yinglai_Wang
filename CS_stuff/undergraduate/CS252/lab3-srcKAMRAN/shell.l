
/*
 *
 * CS-413 Spring 98
 * shell.l: lexical analyzer for shell
 * You have to extend it.
 *
 */

%{

#include <string.h>
#include <unistd.h>
#include "y.tab.h"

////////////  Start added code ///////////
extern char *shell;
char * read_line();

int mygetc(FILE * f) {
  static char *p;
  char ch;

  if (!isatty(0)) {
    // stdin is not a tty. Call real getc
    return getc(f);
  }

  // stdin is a tty. Call our read_line.

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

/////////// End added code ///////////
%}

%%

\n 	{
		return NEWLINE;
}
[ \t] 	{
		/* Discard spaces and tabs */
}
">" {
        return GREAT;
}
">>" {
        return GREATGREAT;
}
">>&" {
        return GREATGREATAMPERSAND;
}
"<" {
        return LESS;
}
"|" {
        return PIPE;
}
">&" {
    return GREATAMPERSAND;
}
"&" {
    return AMPERSAND;
}

["][^"]*["]    {
            yylval.string_val = strdup(yytext+1);
            if(yylval.string_val[yyleng-2] == '"')
            yylval.string_val[yyleng-2] = 0;
            return WORD;
        }

[\`][^\`]*[\`]      {
            char * string = strdup(yytext+1);
            string[strlen(string)-1] = '\n';
            string[strlen(string)] = '\0';
     
            int in, out, err, pid, ret;
           
            int fdpipe1[2];
            int fdpipe2[2];
            pipe(fdpipe1);
            pipe(fdpipe2);
     
            in = fdpipe1[0];
            out = fdpipe2[0];
           
            pid = fork();
            if(pid == 0)
            {
                    dup2(in, 0);
                    dup2(out, 1);
                    close(in);
                    close(out);
                    close(fdpipe1[1]);
                    close(fdpipe2[1]);
     
                    execl(shell, shell);
                    perror("subshell failed");
                    _exit(1);
            }
     
     
            char buf[1024]={0};
     
            close(fdpipe1[0]);
            close(fdpipe2[0]);
     
            write(fdpipe1[1], string, strlen(string));
            close(fdpipe1[1]);
           
            read(fdpipe2[1], buf, 1024);
            close(fdpipe2[1]);
     
            int len = strlen(buf);
    
            int i;
            for(i = len-1; i >= 0; i--)
            {
                    unput(buf[i]);
            }
     
}

[^ ^\\&<>|\t\n][^ ^\\&<>|\t\n]*  {
        //char* string = strdup(yytext);
        /* Assume that file names have only alpha chars */
        yylval.string_val = strdup(yytext);
        return WORD;
    }

.    {
        /* Invalid character in input */
        return NOTOKEN;
    }
(([\\][^])*([^ \\ & > < | \t \n])*)*  {
    yylval.string_val = strdup(yytext);
    return WORD;
    }


%%