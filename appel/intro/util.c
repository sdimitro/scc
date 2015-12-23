#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

void *
xmalloc(size_t size)
{
	void *p = malloc(size);
	if (!p) {
	   fprintf(stderr,"error: xmalloc(%zu) - ran out of memory!\n",
		       size);
	   exit(EXIT_FAILURE);
	}
	return p;
}

char *
xstring(const char *s)
{
	size_t len = strlen(s) + 1;
	char *p = xmalloc(sizeof(char) * len);
	strncpy(p, s, len);
	return p;
}

struct blist *
xblist(bool head, struct blist *tail)
{
	struct blist *l = xmalloc(sizeof(struct blist));
	l->head = head;
	l->tail = tail;
	return l;
}

