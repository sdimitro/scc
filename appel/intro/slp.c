#include <stdlib.h>

#include "util.h"
#include "slp.h"

struct stmt *
comp_stmt(struct stmt *s1, struct stmt *s2)
{
	struct stmt *s = xmalloc(sizeof(struct stmt));
	s->type = COMPOUND;
	s->u.compound.stm1 = s1;
	s->u.compound.stm2 = s2;
	return s;
}


struct stmt *
asgn_stmt(char *id, struct expr *exp)
{
	struct stmt *s = xmalloc(sizeof(struct stmt));
	s->type = ASSIGN;
	s->u.assign.id = id;
	s->u.assign.exp = exp;
	return s;
}

struct stmt *
prnt_stmt(struct expr_list *exps)
{
	struct stmt *s = xmalloc(sizeof(struct stmt));
	s->type = PRINT;
	s->u.print.exps = exps;
	return s;
}

struct expr *
id_expr(char *id)
{
	struct expr * e = xmalloc(sizeof(struct expr));
	e->type = ID;
	e->u.id = id;
	return e;
}

struct expr *
num_expr(int num)
{
	struct expr *e = xmalloc(sizeof(struct expr));
	e->type = NUM;
	e->u.num = num;
	return e;
}

struct expr *
op_expr(struct expr *l, enum binop op, struct expr *r)
{
	struct expr *e = xmalloc(sizeof(struct expr));
	e->type = OP;
	e->u.op.left = l;
	e->u.op.op = op;
	e->u.op.right = r;
	return e;
}

struct expr *
eseq_expr(struct stmt *stmt, struct expr *expr)
{
	struct expr *e = xmalloc(sizeof(struct expr));
	e->type = ESEQ;
	e->u.eseq.stmt = stmt;
	e->u.eseq.expr = expr;
	return e;
}

struct expr_list *
pair_elist(struct expr *h, struct expr_list *t)
{
	struct expr_list *e = xmalloc(sizeof(struct expr_list));
	e->type = PAIR;
	e->u.pair.head = h;
	e->u.pair.tail = t;
	return e;
}

struct expr_list *
last_elist(struct expr * l)
{
	struct expr_list *e = xmalloc(sizeof(struct expr_list));
	e->type = LAST;
	e->u.last = l;
	return e;
}

