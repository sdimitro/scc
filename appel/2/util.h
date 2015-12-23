#ifndef __UTIL_H
#define __UTIL_H

#include <stdbool.h>

void *xmalloc(size_t);
char *xstring(const char *);

struct blist {
	bool head;
	struct blist *tail;
};

struct blist *xblist(bool, struct blist *);

struct ilist {
	int i;
	struct ilist *tail;
};

struct ilist *xilist(int, struct ilist *);

#endif /* __UTIL_H */

