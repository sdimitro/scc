%{
#include <string.h>

#include "errormsg.h"
#include "tokens.h"
#include "util.h"

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

%}

%%
" "	 {adjust(); continue;}
\n	 {adjust(); EM_newline(); continue;}
","	 {adjust(); return COMMA;}
for  	 {adjust(); return FOR;}
[0-9]+	 {adjust(); yylval.ival = atoi(yytext); return INT;}
.	 {adjust(); EM_error(EM_tok_pos, "illegal token");}


