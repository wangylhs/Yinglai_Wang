grammar Micro;

program: token*;

token: INTLITERAL | FLOATLITERAL | STRINGLITERAL | COMMENT | OPERATOR | KEYWORD | SPACE | IDENTIFIER;


INTLITERAL: [0-9]+;

FLOATLITERAL: [0-9]*'.'[0-9]+;

STRINGLITERAL: '"'.*?'"';

COMMENT: [-][-].*?'\n' -> skip;

KEYWORD:   'PROGRAM' | 'BEGIN' | 'END' | 'FUNCTION' | 'READ' | 'WRITE' | 'IF' | 'ELSE' | 'ENDIF' | 'WHILE' | 'ENDWHILE' | 'CONTINUE' | 'BREAK' | 'RETURN' | 'INT' | 'VOID' | 'STRING' | 'FLOAT';

OPERATOR:  ':=' | '+' | '-' | '*' | '/' | '=' | '!=' | '<' | '>' | '(' | ')' | ';' | ',' | '<=' | '>=';

SPACE: [ \t\n\r]+ -> skip;

IDENTIFIER: [a-zA-Z][a-zA-Z0-9]*;