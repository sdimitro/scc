#include <stdio.h>
#include <stdlib.h>

#include "errormsg.h"
#include "util.h"

extern int yyparse(void);

void
parse(char *fn) 
{
	EM_reset(fn);
	if (yyparse() == 0)
		fprintf(stdout,"Parsing successful!\n");
	else
		fprintf(stderr,"Parsing failed\n");
}


int
main(int c, char *v[]) {
	if (c != 2) {
		fprintf(stderr,"usage: %s <filename>\n", v[0]);
		exit(EXIT_FAILURE);
	}

	parse(v[1]);

	return 0;
}
