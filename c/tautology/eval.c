#include <stdio.h>
#include "token.h"
#include "expression.h"

bool get_bit(int n, int decimal)
{
	return (decimal & (1 << (n - 1)));
}

bool eval_single(struct expression *expr, int bitmap)
{
	switch (expr->type) {
	case VarExp:
		return get_bit(expr->u.varID, bitmap);
		break;
	case OpExp:
		switch (expr->u.op) {
		case OpNot:
			return ! eval_single(expr->u.left, bitmap);
		case OpAnd:
			return eval_single(expr->u.left, bitmap)
				&& eval_single(expr->u.right, bitmap);
		case OpOr:
		default:
			return eval_single(expr->u.left, bitmap)
				|| eval_single(expr->u.right, bitmap);
			break;
		}
		break;
	default:
		break;
	}
	return -1;
}

int eval_all(struct expression *expr, struct symbol_table *sym_table)
{
	int bitmap = 0;
	int count = sym_table->count;
	int pre = eval_single(expr, 0);
	int next;
	for (; bitmap < (1<<count); bitmap++) {
		next = eval_single(expr, bitmap);
		if (next != pre) {
			return -1;
		}
		pre = next;
	}
	return pre;
}
