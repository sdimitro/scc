#include <stdio.h>
#include <stdlib.h>

#include "errormsg.h"
#include "tokens.h"
#include "util.h"

union YYSTYPE yylval;

int yylex(void); /* prototype for the lexing function */

char *token_names[] = {
	"ID",
	"STRING",
	"INT",
	"COMMA",
	"COLON",
	"SEMICOLON",
	"LPAREN",
	"RPAREN",
	"LBRACK",
	"RBRACK",
	"LBRACE",
	"RBRACE",
	"DOT",
	"PLUS",
	"MINUS",
	"TIMES",
	"DIVIDE",
	"EQ",
	"NEQ",
	"LT",
	"LE",
	"GT",
	"GE",
	"AND",
	"OR",
	"ASSIGN",
	"ARRAY",
	"IF",
	"THEN",
	"ELSE",
	"WHILE",
	"FOR",
	"TO",
	"DO",
	"LET",
	"IN",
	"END",
	"OF",
	"BREAK",
	"NIL",
	"FUNCTION",
	"VAR",
	"TYPE"
};


char *
token_name(int tok)
{
	return (tok < 257 || tok > 299) ?
		"BAD_TOKEN" : token_names[tok - 257];
}

int
main(int c, char *v[])
{
	char *fname;
	int tok;

	if (c != 2) {
		fprintf(stderr,"usage: %s <filename>\n", v[0]);
		exit(1);
	}

	fname = v[1];
	EM_reset(fname);

	for(;;) {
		tok = yylex();

		if (tok == 0)
			break;

		switch(tok) {
		case ID:
		case STRING:
			printf("%10s %4d %s\n", token_name(tok),
			       EM_tok_pos, yylval.sval);
			break;

		case INT:
			printf("%10s %4d %d\n", token_name(tok),
			       EM_tok_pos, yylval.ival);
			break;

		default:
			printf("%10s %4d\n", token_name(tok),
			       EM_tok_pos);
		}
	}
	return 0;
}

