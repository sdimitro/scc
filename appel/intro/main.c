#include <stdio.h>
#include <stdlib.h>

#include "prog1.h"
#include "slp.h"
#include "table.h"

int maxargs(struct stmt *);

static int
exp_maxargs(struct expr *e)
{
	int retval;

	/* Used in OP and ESEQ */
	int x, y;

	retval = 0;

	switch(e->type) {
	case ID:
	case NUM:
		break;

	case OP:
		x = exp_maxargs(e->u.op.left);
		y = exp_maxargs(e->u.op.right);
		retval = (x > y) ? x : y;
		break;

	case ESEQ:
		x = maxargs(e->u.eseq.stmt);
		y = exp_maxargs(e->u.eseq.expr);
		retval = (x > y) ? x : y;
		break;

	default:
		fprintf(stderr, "error: exp_maxargs() - impossible\n");
		break;
	}

	return retval;
}

int
maxargs(struct stmt *s)
{
	int cmax, temp;

	/* used in ASSIGN */
	int x, y;

	/* used in PRINT */
	struct expr_list *elist;
	int temp2 = 0;

	cmax = temp = 0;

	switch(s->type) {
	case COMPOUND:
		x = maxargs(s->u.compound.stm1);
		y = maxargs(s->u.compound.stm2);
		temp = (x > y) ? x : y;
		break;

	case ASSIGN:
		temp = exp_maxargs(s->u.assign.exp);
		break;

	case PRINT:
		elist = s->u.print.exps;

		while (elist->type != LAST) {
			temp2 = exp_maxargs(elist->u.pair.head);
			elist = elist->u.pair.tail;

			if (temp2 > temp) temp = temp2;
			cmax++;
		}

		temp2 = exp_maxargs(elist->u.last);
		if (temp2 > temp) temp = temp2;
		cmax++;

		break;

	default:
		fprintf(stderr, "error: maxargs() - impossible\n");
		break;
	}

	return (temp > cmax) ? temp : cmax;
}

static struct table *interp_stmt(struct stmt *, struct table *);

static int
interp_binop(int l, enum binop bop, int r)
{
	int result = -1;

	switch(bop) {
	case PLUS:
		result = l + r;
		break;

	case MINUS:
		result = l - r;
		break;

	case TIMES:
		result = l * r;
		break;

	case DIV:
		result = l / r;
		break;

	default:
		fprintf(stderr, "error: interp_binop() - impossible\n");
		break;
	}

	return result;
}

static struct setable *
interp_expr(struct expr *e, struct table *t)
{
	struct setable *seret = NULL;

	/* used for OP */
	int x, y;

	switch(e->type) {
	case ID:
		seret = setable_alloc(table_lookup(e->u.id, t), t);
		break;

	case NUM:
		seret = setable_alloc(e->u.num, t);
		break;

	case OP:
		seret = interp_expr(e->u.op.left, t);
		t = seret->t;
		x = seret->rval;
		free(seret);

		seret = interp_expr(e->u.op.right, t);
		t = seret->t;
		y = seret->rval;
		free(seret);

		seret = setable_alloc(interp_binop(x, e->u.op.op, y), t);
		break;

	case ESEQ:
		t = interp_stmt(e->u.eseq.stmt, t);
		seret = interp_expr(e->u.eseq.expr, t);
		break;

	default:
		fprintf(stderr, "error: interp_expr() - impossible\n");
		break;
	}

	return seret;
}

static struct table *
interp_stmt(struct stmt *s, struct table *t)
{
	struct setable *seret = NULL;
	struct expr_list *elist = NULL;

	switch(s->type) {
	case COMPOUND:
		t = interp_stmt(s->u.compound.stm1, t);
		t = interp_stmt(s->u.compound.stm2, t);
		break;

	case ASSIGN:
		seret = interp_expr(s->u.assign.exp, t);
		t = table_insert(s->u.assign.id, seret->rval, seret->t);
		free(seret);
		break;

	case PRINT:
		elist = s->u.print.exps;

		while (elist->type != LAST) {
			seret = interp_expr(elist->u.pair.head, t);

			t = seret->t;
			printf(" %d", seret->rval);

			elist = elist->u.pair.tail;
		}

		seret = interp_expr(elist->u.last, t);
		t = seret->t;
		printf(" %d\n", seret->rval);
		free(seret);
		break;

	default:
		fprintf(stderr, "error: interp_stmt() - impossible\n");
		break;
	}

	return t;
}

void
interp(struct stmt *s)
{
	interp_stmt(s, NULL);
}


int
main(void)
{
	struct stmt *init_s = prog();
	printf("maxargs(prog()) -> %d\n", maxargs(init_s));
	interp(init_s);
	return 0;
}

