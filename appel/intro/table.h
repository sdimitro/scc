#ifndef __TABLE_H
#define __TABLE_H

struct table {
	char *id;
	int val;
	struct table *tail;
};

/* Empty table is represented as a NULL */
struct table *table_insert(char *, int, struct table *);
/* Lookup is faulty: -1 return for no value found */
int table_lookup(char *, struct table *);

struct setable {
	int rval;
	struct table *t;
};

struct setable *setable_alloc(int, struct table *t);

#endif /* __TABLE_H */

