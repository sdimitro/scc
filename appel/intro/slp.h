#ifndef __SLP_H
#define __SLP_H

enum binop {
	PLUS,
	MINUS,
	TIMES,
	DIV
};

enum stmt_type {
	COMPOUND,
	ASSIGN,
	PRINT
};

struct stmt {
	enum stmt_type type;

	union {
		struct {
			struct stmt *stm1, *stm2;
		} compound;

		struct {
			char *id;
			struct expr *exp;
		} assign;

		struct {
			struct expr_list *exps;
		} print;
	} u;
};

struct stmt *comp_stmt(struct stmt *, struct stmt *);
struct stmt *asgn_stmt(char *, struct expr *);
struct stmt *prnt_stmt(struct expr_list *);

enum expr_type {
	ID,
	NUM,
	OP,
	ESEQ
};

struct expr {
	enum expr_type type;

	union {
		char *id;
		int num;

		struct {
			struct expr *left;
			enum binop op;
			struct expr *right;
		} op;

		struct {
			struct stmt *stmt;
			struct expr *expr;
		} eseq;
	} u;
};

struct expr *id_expr(char *);
struct expr *num_expr(int);
struct expr *op_expr(struct expr *, enum binop, struct expr *);
struct expr *eseq_expr(struct stmt *, struct expr *);

enum expr_list_type {
	PAIR,
	LAST
};

struct expr_list {
	enum expr_list_type type;

	union {
		struct {
			struct expr *head;
			struct expr_list *tail;
		} pair;

		struct expr *last;
	} u;
};

struct expr_list *pair_elist(struct expr *, struct expr_list *);
struct expr_list *last_elist(struct expr *);

#endif /* __SLP_H */

