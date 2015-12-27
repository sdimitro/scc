L   [a-zA-Z_]
A   [a-zA-Z_0-9]

ES  (\\(['"\?\\abfnrtv]|[0-7]{1,3}|x[a-fA-F0-9]+))
WS  [ \t\v\n\f]

%{
#include <string.h>

#include "errormsg.h"
#include "util.h"

#include "y.tab.h"

int char_pos = 1;

int
yywrap(void)
{
	char_pos = 1;
	return 1;
}


void
adjust(void)
{
	EM_tok_pos = char_pos;
	char_pos += yyleng;
}

static void comment(void);

%}

%%

"/*"       {adjust(); comment();}
"//".*     {/* consume //-comment */}

"\n"       {adjust(); EM_newline(); continue;}
"array"    {adjust(); return ARRAY;}
"break"    {adjust(); return BREAK;}
"do"       {adjust(); return DO;}
"else"     {adjust(); return ELSE;}
"end"      {adjust(); return END;}
"for"      {adjust(); return FOR;}
"function" {adjust(); return FUNCTION;}
"if"       {adjust(); return IF;}
"in"       {adjust(); return IN;}
"let"      {adjust(); return LET;}
"nil"      {adjust(); return NIL;}
"of"       {adjust(); return OF;}
"then"     {adjust(); return THEN;}
"to"       {adjust(); return TO;}
"type"     {adjust(); return TYPE;}
"var"      {adjust(); return VAR;}
"while"    {adjust(); return WHILE;}

","	       {adjust(); return COMMA;}
":"	       {adjust(); return COLON;}
";"	       {adjust(); return SEMICOLON;}
"("	       {adjust(); return LPAREN;}
")"	       {adjust(); return RPAREN;}
"["	       {adjust(); return LBRACK;}
"]"	       {adjust(); return RBRACK;}
"{"	       {adjust(); return LBRACE;}
"}"	       {adjust(); return RBRACE;}
"."	       {adjust(); return DOT;}

"+"        {adjust(); return PLUS;}
"-"        {adjust(); return MINUS;}
"*"        {adjust(); return TIMES;}
"/"        {adjust(); return DIVIDE;}
"="        {adjust(); return EQ;}
"<>"       {adjust(); return NEQ;}
"<="       {adjust(); return LE;}
"<"        {adjust(); return LT;}
">="       {adjust(); return GE;}
">"        {adjust(); return GT;}
"&"        {adjust(); return AND;}
"|"        {adjust(); return OR;}
":="       {adjust(); return ASSIGN;}

{L}{A}*    {adjust(); yylval.sval = yytext; return ID;}

[0-9]+     {adjust(); yylval.ival = atoi(yytext); return NUM;}

(\"([^"\\\n]|{ES})*\"{WS}*)+ {adjust(); yylval.sval = yytext; return SLITERAL; }

{WS}+      {adjust(); if (strpbrk("\n", yytext)) {EM_newline();} continue;}
.	       {adjust(); EM_error(EM_tok_pos, "illegal token");}

%%

static void
comment(void)
{
	int c;

	while ((c = input()) != 0)
		if (c == '*') {
			while ((c = input()) == '*')
				;

			if (c == '/')
				return;

			if (c == 0)
				break;
		}

	yyerror("unterminated comment");
}
