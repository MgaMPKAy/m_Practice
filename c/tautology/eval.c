#include <stdio.h>
#include <string.h>
#include "types.h"
#include "eval.h"

bool get_bit(int n, int decimal)
{
	return (decimal & (1 << n));
}

int eval_single(struct expression *expr, int bitmap)
{
	if (expr == NULL) return -1;

	int rval = 0;
	int rval2 = 0;
	switch (expr->type) {
	case VarExp:
		rval = get_bit(expr->u.var_id, bitmap);
		if (rval != 0 && rval != 1) {
			return -1;
		} else {
			return rval;
		}
		break;
	case NotExp:
		rval = eval_single(expr->u.left, bitmap);
		if (rval != 0 && rval != 1) {
			return -1;
		} else {
			return rval;
		}
		break;
	case AndExp:
		rval = eval_single(expr->u.left, bitmap);
		rval2 = eval_single(expr->u.right, bitmap);
		if ((rval != 0 && rval != 1) || (rval2 != 0 && rval2 !=1)) {
			return -1;
		} else {
			return rval && rval2;
		}
		break;
	case OrExp:
		rval = eval_single(expr->u.left, bitmap);
		rval2 = eval_single(expr->u.right, bitmap);
		if ((rval != 0 && rval != 1) || (rval2 != 0 && rval2 !=1)) {
			return -1;
		} else {
			return rval || rval2;
		}
		break;
	default:
		return -1;
	}
}

int eval_all(struct expression *expr)
{
	int bitmap = 0;
	int count = symbol_table->count;
	int pre = eval_single(expr, 0);
	int max = 1 << count;
	int next;

	for (bitmap = 1; bitmap < max; bitmap++) {
		next = eval_single(expr, bitmap);
		if (next != pre) {
			return 2;
		}
		pre = next;
	}
	return pre;
}

void print_truth_table(struct expression *expr)
{
	int count  = symbol_table->count;
	char *(*name) = *(symbol_table->name);
	int bitmap = 0;
	int result = 0;
	int len    = 0;

	for (int i = 0; i < count; i++) {
		printf("%s ", name[i]);
	}
	printf("result\n");
	printf("%s",   "-----------------------------------------------");
	printf("%s\n", "-----------------------------------------------");

	for (; bitmap < (1<<count); bitmap++) {
		for (int i = 0; i < count; i++) {
			len = strlen(name[i]);
			for(int j = 0; j < len / 2; j++) {
				printf("%c",' ');
			}
			printf("%c", get_bit(i, bitmap) ? 'T' : 'F');

			for(int j = 0; j < len / 2; j++) {
				printf("%c",' ');
			}
		}
		printf(" | ");
		result = eval_single(expr, bitmap);
		printf("  %c\n", result ? 'T' : 'F');
	}
}
