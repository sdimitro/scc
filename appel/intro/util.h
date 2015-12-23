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

#endif /* __UTIL_H */

