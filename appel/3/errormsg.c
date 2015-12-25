#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "util.h"
#include "errormsg.h"

extern FILE *yyin;

static struct ilist *line_pos = NULL;
static char *filename = "";
static int line_num = 1;

int EM_tok_pos = 0;
bool errors_exist = false;

void
EM_newline(void)
{
	line_num++;
	line_pos = xilist(EM_tok_pos, line_pos);
}

void
EM_error(int pos, char *message, ...)
{
	va_list ap;
	struct ilist *lines = line_pos; 
	int num = line_num;
	
	errors_exist = true;
	while (lines && lines->i >= pos) {
		lines = lines->tail;
		num--;
	}
	
	if (filename) fprintf(stderr, "%s:", filename);
	if (lines) fprintf(stderr,"%d.%d: ", num, pos - lines->i);

	va_start(ap,message);
	vfprintf(stderr, message, ap);
	va_end(ap);
	fprintf(stderr,"\n");
}

void
EM_reset(char *fn)
{
	errors_exist = false;
	filename = fn;
	line_num = 1;
	line_pos = xilist(0, NULL);

	yyin = fopen(fn, "r");
	if (!yyin) {
		EM_error(0,"cannot open!");
		exit(EXIT_FAILURE);
	}
}

