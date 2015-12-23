#include <stdlib.h>

#include "prog1.h"
#include "slp.h"
#include "util.h"

struct stmt *
prog(void)
{
	return comp_stmt(
			asgn_stmt(
				"a",
				op_expr(
					num_expr(5),
					PLUS,
					num_expr(3))),
			comp_stmt(
				asgn_stmt(
					"b",
					eseq_expr(
						prnt_stmt(
							pair_elist(
								id_expr("a"),
								last_elist(
									op_expr(
										id_expr("a"),
										MINUS, 
										num_expr(1))))),
					op_expr(
						num_expr(10),
						TIMES,
						id_expr("a")))),
				prnt_stmt(
					last_elist(
						id_expr("b")))));
}
