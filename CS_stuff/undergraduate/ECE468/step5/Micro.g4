grammar Micro;
//a:'a';

/* Program */
program
:'PROGRAM' id 'BEGIN' pgm_body 'END'
;
id
: IDENTIFIER
;
pgm_body
: decl func_declarations
;
decl
: (string_decl | var_decl )*
;

/* Global String Declaration */

string_decl
: 'STRING' id ':=' str ';'
;
str
: STRINGLITERAL
;


/* Variable Declaration */

var_decl
: var_type id_list ';'
;
var_type
: 'FLOAT'
| 'INT'
;
any_type
: var_type
| 'VOID'
;
id_list
: id (',' id)*
;

/* Function Paramater List */
param_decl_list
: param_decl (',' param_decl)*
;
param_decl
: var_type id
;

/* Function Declarations */
func_declarations
: (func_decl)*
;
func_decl
: 'FUNCTION' any_type id '('(param_decl_list)?')' 'BEGIN' func_body 'END'
;

func_body
: decl stmt_list
;

/* Statement List */
stmt_list
: (stmt)*
;
stmt
: base_stmt
| if_stmt
| do_while_stmt
;
base_stmt
: assign_stmt
| read_stmt
| write_stmt
| return_stmt
;

/* Basic Statements */
assign_stmt
: assign_expr ';'
;
assign_expr
: id ':=' expr
;
read_stmt
: 'READ' '(' id_list ')'';'
;
write_stmt
: 'WRITE' '(' id_list ')'';'
;
return_stmt
: 'RETURN' expr ';'
;

/* Expressions */
expr
: factor (addop factor)*;
factor
: postfix_expr (mulop postfix_expr)*
;
postfix_expr
: primary
| call_expr
;
call_expr
: id '(' (expr_list)? ')'
;
expr_list
: expr (',' expr)*
;
primary
: '('expr')'
| id
| INTLITERAL
| FLOATLITERAL
;
addop
: '+'
| '-'
;
mulop
: '*'
| '/'
;

/* Complex Statements and Condition */
if_stmt
: 'IF' '(' cond ')' decl stmt_list else_part 'ENDIF'
;
else_part
: ('ELSIF' '(' cond ')' decl stmt_list else_part)*
;
cond
: expr compop expr
| 'TRUE'
| 'FALSE'
;
compop
: '<'
| '>'
| '='
| '!='
| '<='
| '>='
;

/* ECE 468 students use this version of do_while_stmt */
do_while_stmt
: 'DO' decl stmt_list 'WHILE' '(' cond ')' ';'
;

IDENTIFIER
: [A-Za-z][A-Za-z0-9]*
;

INTLITERAL
: [0-9]+
;

FLOATLITERAL
: [0-9]*'.'[0-9]+
;

STRINGLITERAL
: '"'.*?'"'
;

COMMENT
: [-][-].*?'\n' ->skip
;

WS
:[ \t\n\r]+ -> skip
;


Operators: ':='| '+'| '-'| '*'| '/'| '='| '!='| '<'| '>'|'('| ')'| ';'| '|'| '<='| '>=' ;

Keywords :  'PROGRAM' |  'BEGIN'|  'END'|  'FUNCTION'|
'READ'|'WRITE'|  'IF'|  'ELSIF'|  'ENDIF'|  'DO'|
'WHILE'|  'CONTINUE'|'BREAK'|  'RETURN'|  'INT'|  'VOID'|  'STRING'|
'FLOAT'|  'TRUE'|'FALSE' ;
