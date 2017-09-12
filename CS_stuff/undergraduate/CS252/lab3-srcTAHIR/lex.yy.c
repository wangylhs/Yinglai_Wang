#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
# define U(x) x
# define NLSTATE yyprevious=YYNEWLINE
# define BEGIN yybgin = yysvec + 1 +
# define INITIAL 0
# define YYLERR yysvec
# define YYSTATE (yyestate-yysvec-1)
# define YYOPTIM 1
# ifndef YYLMAX 
# define YYLMAX BUFSIZ
# endif 
#ifndef __cplusplus
# define output(c) (void)putc(c,yyout)
#else
# define lex_output(c) (void)putc(c,yyout)
#endif

#if defined(__cplusplus) || defined(__STDC__)

#if defined(__cplusplus) && defined(__EXTERN_C__)
extern "C" {
#endif
	int yyback(int *, int);
	int yyinput(void);
	int yylook(void);
	void yyoutput(int);
	int yyracc(int);
	int yyreject(void);
	void yyunput(int);
	int yylex(void);
#ifdef YYLEX_E
	void yywoutput(wchar_t);
	wchar_t yywinput(void);
#endif
#ifndef yyless
	int yyless(int);
#endif
#ifndef yywrap
	int yywrap(void);
#endif
#ifdef LEXDEBUG
	void allprint(char);
	void sprint(char *);
#endif
#if defined(__cplusplus) && defined(__EXTERN_C__)
}
#endif

#ifdef __cplusplus
extern "C" {
#endif
	void exit(int);
#ifdef __cplusplus
}
#endif

#endif
# define unput(c) {yytchar= (c);if(yytchar=='\n')yylineno--;*yysptr++=yytchar;}
# define yymore() (yymorfg=1)
#ifndef __cplusplus
# define input() (((yytchar=yysptr>yysbuf?U(*--yysptr):getc(yyin))==10?(yylineno++,yytchar):yytchar)==EOF?0:yytchar)
#else
# define lex_input() (((yytchar=yysptr>yysbuf?U(*--yysptr):getc(yyin))==10?(yylineno++,yytchar):yytchar)==EOF?0:yytchar)
#endif
#define ECHO fprintf(yyout, "%s",yytext)
# define REJECT { nstr = yyreject(); goto yyfussy;}
int yyleng;
#define YYISARRAY
char yytext[YYLMAX];
int yymorfg;
extern char *yysptr, yysbuf[];
int yytchar;
FILE *yyin = {stdin}, *yyout = {stdout};
extern int yylineno;
struct yysvf { 
	struct yywork *yystoff;
	struct yysvf *yyother;
	int *yystops;};
struct yysvf *yyestate;
extern struct yysvf yysvec[], *yybgin;

# line 3 "shell.l"
/*
 *
 * CS-413 Spring 98
 * shell.l: lexical analyzer for shell
 * You have to extend it.
 *
 */

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

# define YYNEWLINE 10
int yylex(){
int nstr; extern int yyprevious;
#ifdef __cplusplus
/* to avoid CC and lint complaining yyfussy not being used ...*/
static int __lex_hack = 0;
if (__lex_hack) goto yyfussy;
#endif
while((nstr = yylook()) >= 0)
yyfussy: switch(nstr){
case 0:
if(yywrap()) return(0); break;
case 1:

# line 49 "shell.l"
{
	char * temp;
	while((temp = strchr(yytext,'\"'))!=NULL){
		strcpy(temp, temp+1);
	}
	yylval.string_val = strdup(yytext);
	return WORD;
}
break;
case 2:

# line 58 "shell.l"
	{
	return NEWLINE;
}
break;
case 3:

# line 62 "shell.l"
	{
	/* Discard spaces and tabs */
}
break;
case 4:

# line 66 "shell.l"
	{
	return GREAT;
}
break;
case 5:

# line 70 "shell.l"
	{
	return LESS;
}
break;
case 6:

# line 74 "shell.l"
	{
	return PIPE;
}
break;
case 7:

# line 78 "shell.l"
	{
	return BACKGROUND;
}
break;
case 8:

# line 82 "shell.l"
{
	return APPEND;
}
break;
case 9:

# line 86 "shell.l"
{
	return REDIRECT;
}
break;
case 10:

# line 90 "shell.l"
{
	return APPEND_REDIRECT;
}
break;
case 11:

# line 94 "shell.l"
{
	exit(0);
}
break;
case 12:

# line 98 "shell.l"
{
	/* Assume that file names have only alpha chars */
	char *temp = strdup(yytext);
	temp = tilda(temp);
	temp = escapeChar(temp);
	temp = variableExp(temp);
	yylval.string_val = strdup(temp);
	return WORD;
}
break;
case 13:

# line 108 "shell.l"
{
	/* Invalid character in input */
	return NOTOKEN;
}
break;
case -1:
break;
default:
(void)fprintf(yyout,"bad switch yylook %d",nstr);
} return(0); }
/* end of yylex */

# line 114 "shell.l"

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


int yyvstop[] = {
0,

12,
0, 

12,
0, 

12,
13,
0, 

3,
13,
0, 

2,
0, 

12,
13,
0, 

7,
13,
0, 

5,
13,
0, 

4,
13,
0, 

12,
13,
0, 

12,
13,
0, 

6,
13,
0, 

12,
0, 

12,
0, 

12,
0, 

1,
12,
0, 

12,
0, 

9,
0, 

8,
0, 

12,
0, 

1,
0, 

10,
0, 

12,
0, 

11,
12,
0, 
0};
# define YYTYPE unsigned char
struct yywork { YYTYPE verify, advance; } yycrank[] = {
0,0,	0,0,	1,3,	0,0,	
0,0,	0,0,	3,13,	0,0,	
6,15,	0,0,	1,4,	1,5,	
0,0,	10,13,	3,0,	3,0,	
6,16,	6,0,	11,13,	14,0,	
22,0,	10,13,	10,0,	13,0,	
13,0,	0,0,	11,0,	11,0,	
0,0,	15,0,	17,0,	0,0,	
0,0,	0,0,	0,0,	1,6,	
2,6,	3,0,	0,0,	1,7,	
20,23,	6,17,	9,19,	3,0,	
22,22,	6,16,	13,0,	0,0,	
16,16,	11,0,	10,13,	0,0,	
13,0,	15,17,	17,17,	11,0,	
16,16,	16,0,	0,0,	18,15,	
18,0,	1,8,	2,8,	1,9,	
2,9,	3,0,	9,20,	3,0,	
0,0,	25,0,	25,0,	0,0,	
0,0,	0,0,	13,0,	0,0,	
13,0,	11,0,	0,0,	11,0,	
0,0,	16,22,	0,0,	0,0,	
18,17,	16,16,	0,0,	21,13,	
18,15,	0,0,	0,0,	0,0,	
25,0,	1,10,	2,10,	21,0,	
21,0,	3,14,	25,0,	6,18,	
0,0,	14,14,	1,11,	2,11,	
10,14,	0,0,	13,14,	0,0,	
24,13,	11,14,	0,0,	15,18,	
17,18,	0,0,	0,0,	0,0,	
24,0,	24,0,	21,0,	0,0,	
25,0,	0,0,	25,0,	0,0,	
21,0,	1,12,	2,12,	0,0,	
0,0,	3,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	11,21,	13,0,	24,0,	
0,0,	11,0,	18,18,	0,0,	
0,0,	24,0,	21,0,	0,0,	
21,0,	0,0,	0,0,	0,0,	
25,14,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	24,0,	
0,0,	24,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	21,14,	0,0,	
0,0,	0,0,	0,0,	0,0,	
25,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	21,24,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	24,14,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	21,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	24,25,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	24,0,	
0,0};
struct yysvf yysvec[] = {
0,	0,	0,
yycrank+-1,	0,		yyvstop+1,
yycrank+-2,	yysvec+1,	yyvstop+3,
yycrank+-5,	0,		yyvstop+5,
yycrank+0,	0,		yyvstop+8,
yycrank+0,	0,		yyvstop+11,
yycrank+-7,	0,		yyvstop+13,
yycrank+0,	0,		yyvstop+16,
yycrank+0,	0,		yyvstop+19,
yycrank+4,	0,		yyvstop+22,
yycrank+-12,	0,		yyvstop+25,
yycrank+-17,	0,		yyvstop+28,
yycrank+0,	0,		yyvstop+31,
yycrank+-14,	yysvec+3,	yyvstop+34,
yycrank+-9,	yysvec+10,	yyvstop+36,
yycrank+-19,	yysvec+6,	yyvstop+38,
yycrank+-47,	0,		0,	
yycrank+-20,	yysvec+6,	yyvstop+40,
yycrank+-50,	yysvec+6,	yyvstop+43,
yycrank+0,	0,		yyvstop+45,
yycrank+2,	0,		yyvstop+47,
yycrank+-86,	0,		yyvstop+49,
yycrank+-10,	yysvec+16,	yyvstop+51,
yycrank+0,	0,		yyvstop+53,
yycrank+-107,	0,		yyvstop+55,
yycrank+-60,	yysvec+3,	yyvstop+57,
0,	0,	0};
struct yywork *yytop = yycrank+231;
struct yysvf *yybgin = yysvec+1;
char yymatch[] = {
  0,   1,   1,   1,   1,   1,   1,   1, 
  1,   9,  10,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  9,   1,   1,   1,   1,   1,  38,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,  38,   1,  38,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,  38,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
0};
char yyextra[] = {
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0};
/*	Copyright (c) 1989 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#pragma ident	"@(#)ncform	6.12	97/12/08 SMI"

int yylineno =1;
# define YYU(x) x
# define NLSTATE yyprevious=YYNEWLINE
struct yysvf *yylstate [YYLMAX], **yylsp, **yyolsp;
char yysbuf[YYLMAX];
char *yysptr = yysbuf;
int *yyfnd;
extern struct yysvf *yyestate;
int yyprevious = YYNEWLINE;
#if defined(__cplusplus) || defined(__STDC__)
int yylook(void)
#else
yylook()
#endif
{
	register struct yysvf *yystate, **lsp;
	register struct yywork *yyt;
	struct yysvf *yyz;
	int yych, yyfirst;
	struct yywork *yyr;
# ifdef LEXDEBUG
	int debug;
# endif
	char *yylastch;
	/* start off machines */
# ifdef LEXDEBUG
	debug = 0;
# endif
	yyfirst=1;
	if (!yymorfg)
		yylastch = yytext;
	else {
		yymorfg=0;
		yylastch = yytext+yyleng;
		}
	for(;;){
		lsp = yylstate;
		yyestate = yystate = yybgin;
		if (yyprevious==YYNEWLINE) yystate++;
		for (;;){
# ifdef LEXDEBUG
			if(debug)fprintf(yyout,"state %d\n",yystate-yysvec-1);
# endif
			yyt = yystate->yystoff;
			if(yyt == yycrank && !yyfirst){  /* may not be any transitions */
				yyz = yystate->yyother;
				if(yyz == 0)break;
				if(yyz->yystoff == yycrank)break;
				}
#ifndef __cplusplus
			*yylastch++ = yych = input();
#else
			*yylastch++ = yych = lex_input();
#endif
#ifdef YYISARRAY
			if(yylastch > &yytext[YYLMAX]) {
				fprintf(yyout,"Input string too long, limit %d\n",YYLMAX);
				exit(1);
			}
#else
			if (yylastch >= &yytext[ yytextsz ]) {
				int	x = yylastch - yytext;

				yytextsz += YYTEXTSZINC;
				if (yytext == yy_tbuf) {
				    yytext = (char *) malloc(yytextsz);
				    memcpy(yytext, yy_tbuf, sizeof (yy_tbuf));
				}
				else
				    yytext = (char *) realloc(yytext, yytextsz);
				if (!yytext) {
				    fprintf(yyout,
					"Cannot realloc yytext\n");
				    exit(1);
				}
				yylastch = yytext + x;
			}
#endif
			yyfirst=0;
		tryagain:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"char ");
				allprint(yych);
				putchar('\n');
				}
# endif
			yyr = yyt;
			if ( (uintptr_t)yyt > (uintptr_t)yycrank){
				yyt = yyr + yych;
				if (yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					if(lsp > &yylstate[YYLMAX]) {
						fprintf(yyout,"Input string too long, limit %d\n",YYLMAX);
						exit(1);
					}
					goto contin;
					}
				}
# ifdef YYOPTIM
			else if((uintptr_t)yyt < (uintptr_t)yycrank) {	/* r < yycrank */
				yyt = yyr = yycrank+(yycrank-yyt);
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"compressed state\n");
# endif
				yyt = yyt + yych;
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					if(lsp > &yylstate[YYLMAX]) {
						fprintf(yyout,"Input string too long, limit %d\n",YYLMAX);
						exit(1);
					}
					goto contin;
					}
				yyt = yyr + YYU(yymatch[yych]);
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"try fall back character ");
					allprint(YYU(yymatch[yych]));
					putchar('\n');
					}
# endif
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transition */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					if(lsp > &yylstate[YYLMAX]) {
						fprintf(yyout,"Input string too long, limit %d\n",YYLMAX);
						exit(1);
					}
					goto contin;
					}
				}
			if ((yystate = yystate->yyother) && (yyt= yystate->yystoff) != yycrank){
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"fall back to state %d\n",yystate-yysvec-1);
# endif
				goto tryagain;
				}
# endif
			else
				{unput(*--yylastch);break;}
		contin:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"state %d char ",yystate-yysvec-1);
				allprint(yych);
				putchar('\n');
				}
# endif
			;
			}
# ifdef LEXDEBUG
		if(debug){
			fprintf(yyout,"stopped at %d with ",*(lsp-1)-yysvec-1);
			allprint(yych);
			putchar('\n');
			}
# endif
		while (lsp-- > yylstate){
			*yylastch-- = 0;
			if (*lsp != 0 && (yyfnd= (*lsp)->yystops) && *yyfnd > 0){
				yyolsp = lsp;
				if(yyextra[*yyfnd]){		/* must backup */
					while(yyback((*lsp)->yystops,-*yyfnd) != 1 && lsp > yylstate){
						lsp--;
						unput(*yylastch--);
						}
					}
				yyprevious = YYU(*yylastch);
				yylsp = lsp;
				yyleng = yylastch-yytext+1;
				yytext[yyleng] = 0;
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"\nmatch ");
					sprint(yytext);
					fprintf(yyout," action %d\n",*yyfnd);
					}
# endif
				return(*yyfnd++);
				}
			unput(*yylastch);
			}
		if (yytext[0] == 0  /* && feof(yyin) */)
			{
			yysptr=yysbuf;
			return(0);
			}
#ifndef __cplusplus
		yyprevious = yytext[0] = input();
		if (yyprevious>0)
			output(yyprevious);
#else
		yyprevious = yytext[0] = lex_input();
		if (yyprevious>0)
			lex_output(yyprevious);
#endif
		yylastch=yytext;
# ifdef LEXDEBUG
		if(debug)putchar('\n');
# endif
		}
	}
#if defined(__cplusplus) || defined(__STDC__)
int yyback(int *p, int m)
#else
yyback(p, m)
	int *p;
#endif
{
	if (p==0) return(0);
	while (*p) {
		if (*p++ == m)
			return(1);
	}
	return(0);
}
	/* the following are only used in the lex library */
#if defined(__cplusplus) || defined(__STDC__)
int yyinput(void)
#else
yyinput()
#endif
{
#ifndef __cplusplus
	return(input());
#else
	return(lex_input());
#endif
	}
#if defined(__cplusplus) || defined(__STDC__)
void yyoutput(int c)
#else
yyoutput(c)
  int c; 
#endif
{
#ifndef __cplusplus
	output(c);
#else
	lex_output(c);
#endif
	}
#if defined(__cplusplus) || defined(__STDC__)
void yyunput(int c)
#else
yyunput(c)
   int c; 
#endif
{
	unput(c);
	}
