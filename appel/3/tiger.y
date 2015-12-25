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

%token <sval> ID STRING
%token <ival> INT

%token 
  COMMA COLON SEMICOLON LPAREN RPAREN LBRACK RBRACK 
  LBRACE RBRACE DOT 
  PLUS MINUS TIMES DIVIDE EQ NEQ LT LE GT GE
  AND OR ASSIGN
  ARRAY IF THEN ELSE WHILE FOR TO DO LET IN END OF 
  BREAK NIL
  FUNCTION VAR TYPE 
  NUM SLITERAL

%start program

%%

program:	exp

exp:   ID

