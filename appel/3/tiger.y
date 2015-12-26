%{
#include <stdio.h>

#include "errormsg.h"
#include "util.h"

int yylex(void);

void
yyerror(char *s)
{
	EM_error(EM_tok_pos, "%s", s);
}
%}


%union {
	int pos;
	int ival;
	char *sval;
}

%token <sval> ID SLITERAL
%token <ival> NUM

%token 
  COMMA COLON SEMICOLON LPAREN RPAREN LBRACK RBRACK 
  LBRACE RBRACE DOT 
  PLUS MINUS TIMES DIVIDE EQ NEQ LT LE GT GE
  AND OR ASSIGN
  ARRAY IF THEN ELSE WHILE FOR TO DO LET IN END OF 
  BREAK NIL
  FUNCTION VAR TYPE 

%start program

%%

program
	: expr
	;

asgnlist
	: ID EQ expr
	| ID EQ expr COMMA asgnlist
	;

decs
	: dec
	| decs dec
	;

dec
	: tydec
	| vardec
	;

expr
	: lvalue
	| NIL
	| NUM
	| SLITERAL
	/* Array creation */
	| ID LBRACK expr RBRACK OF expr
	| ID LBRACE tidlist RBRACE
	/* Record Assignment */
	| ID LBRACE RBRACE
	| ID LBRACE asgnlist RBRACE
	/* Standard Assignment */
	| lvalue ASSIGN expr
	/* LET - IN - END */
	| LET decs IN END
	| LET decs IN exprseq END
	;

exprseq
	: expr
	| exprseq SEMICOLON expr /* parens around them ? */
	;

lvalue
	: ID
	| lvalue DOT ID
	| lvalue LBRACK expr RBRACK
	;

tidlist
	: ID COLON expr
	| ID COLON expr COMMA tidlist
	;

ty
	: ID
	/* Record creation */
	| LBRACE tyfields RBRACE
	| LBRACE RBRACE
	| ARRAY OF ID
	;

tydec
	: TYPE ID EQ ty
	;

tyfields
	: ID COLON ID
	| ID COLON ID COMMA tyfields
	;

vardec
	: VAR ID ASSIGN expr
	| VAR ID COLON ID ASSIGN expr
	;

