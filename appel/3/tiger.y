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
	/* ============== */
	| LET decs IN END
	| LET decs IN exprseq END
	;

exprseq
	: expr
	: exprseq SEMICOLON expr /* parens around them ? */
	;

lvalue
	: ID
	| lvalue DOT ID
	| lvalue LBRACK expr RBRACK
	;

ty
	: ID
	| btype
	| ARRAY OF ID
	;

tydec
	: TYPE ID EQ ty
	;

vardec
	: VAR ID ASSIGN expr
	| VAR ID COLON ID ASSIGN expr
	;

