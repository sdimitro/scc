#include <stdlib.h>
#include <string.h>

#include "table.h"
#include "util.h"

struct table *
table_insert(char * id, int val, struct table *tail)
{
	struct table *t = xmalloc(sizeof(struct table));
	t->id = id;
	t->val = val;
	t->tail = tail;
	return t;
}

int
table_lookup(char *id, struct table *t)
{
	for (; t; t = t->tail)
		if (!strcmp(id, t->id)) {
			return t->val;
		}
	return -1;
}

struct setable *
setable_alloc(int rval, struct table *t)
{
	struct setable *s = xmalloc(sizeof(struct setable));
	s->rval = rval;
	s->t = t;
	return s;
}

